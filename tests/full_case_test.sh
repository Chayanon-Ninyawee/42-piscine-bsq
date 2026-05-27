#!/bin/bash

set -e

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
TEST_DIR="$ROOT_DIR/tests"
STRIKE_DIR="$TEST_DIR/malloc_strike"

make -C "$ROOT_DIR"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
CYAN='\033[0;36m'
BOLD='\033[1m'
RESET='\033[0m'

USE_VALGRIND=0
USE_MALLOC_STRIKE=0
USE_BIG_MAP=0
VERBOSE=0

for arg in "$@"; do
	case "$arg" in
		-v) VERBOSE=1 ;;
		--valgrind) USE_VALGRIND=1 ;;
		--malloc-strike)
			USE_MALLOC_STRIKE=1
			make -C "$STRIKE_DIR"
			;;
		--big-map) USE_BIG_MAP=1 ;;
	esac
done

PASS=0
FAIL=0
MISSING=0
FAILED_TESTS=()

# ----------------------------
# helpers
# ----------------------------

run_cmd()
{
	tmp=$(mktemp)
	set +e
	"$@" > "$tmp" 2>&1
	status=$?
	set -e
	out=$(cat "$tmp")
	rm -f "$tmp"
	echo "$out"
	return $status
}

run_file()
{
	"$ROOT_DIR/bsq" "$1"
}

run_stdin_file()
{
	"$ROOT_DIR/bsq" < "$1"
}

run_pipe_file()
{
	cat "$1" | "$ROOT_DIR/bsq"
}

run_multi_file()
{
	"$ROOT_DIR/bsq" "$@"
}

run_stream_file()
{
	python3 -c '
import random
import sys
import time

data = open(sys.argv[1], "rb").read()
i = 0

while i < len(data):
	n = random.randint(1, 13)

	sys.stdout.buffer.write(data[i:i+n])
	sys.stdout.flush()

	i += n
	time.sleep(0.0001)
' "$1" | "$ROOT_DIR/bsq"
}

run_valgrind()
{
	mapfile="$1"

	run_cmd valgrind \
		--leak-check=full \
		--show-leak-kinds=all \
		--errors-for-leak-kinds=definite,possible \
		--error-exitcode=2 \
		"$ROOT_DIR/bsq" "$mapfile"
}

run_malloc_strike()
{
	mapfile="$1"
	i=1

	while true; do
		out=$(run_cmd env \
			MALLOC_STRIKE=$i \
			LD_PRELOAD="$STRIKE_DIR/malloc_strike.so" \
			"$ROOT_DIR/bsq" "$mapfile")

		status=$?

		if [ $status -ne 0 ]; then
			echo "Malloc strike failed at #$i"
			echo "$out"
			return 1
		fi

		echo "$out" | grep -q "NO_FAIL" && break
		i=$((i + 1))
	done

	return 0
}

print_verbose()
{
	mapfile="$1"
	expected="$2"
	got="$3"

	echo ""
	echo "── INPUT ──"
	cat "$mapfile"
	echo "── EXPECTED ──"
	echo "$expected"
	echo "── GOT ──"
	echo "$got"
	echo ""
}

# ----------------------------
# big map mode only
# ----------------------------

if [ $USE_BIG_MAP -eq 1 ]; then
	echo ""
	echo -e "${BOLD}════════ BIG MAP STRESS TESTS (RANDOMIZED + 100K FINALE) ════════${RESET}"
	
	BASES=(10000 25000 50000 75000 100000)
	DENSITY=20
	
	for base in "${BASES[@]}"; do
		if [ $base -eq 100000 ]; then
			size_x=100000
			size_y=100000
			echo -e "${YELLOW}${BOLD}👑 THE GRAND FINALE: Processing exact 100k x 100k matrix...${RESET}"
		else
			rand_x=$(( RANDOM % 1000 ))
			rand_y=$(( RANDOM % 1000 ))
			size_x=$(( base + rand_x ))
			size_y=$(( base + rand_y ))
		fi
		
		echo -e "${CYAN}🚀 Piping valid ${size_x}x${size_y} map directly into BSQ stdin...${RESET}"
		
		set +e
		bsq_out=$(python3 "$TEST_DIR/map_generator.py" "$size_x" "$size_y" "$DENSITY" | "$ROOT_DIR/bsq" 2>&1)
		status=$?
		set -e
		
		if [ $status -ne 0 ] || echo "$bsq_out" | grep -q "map error"; then
			echo -e "${RED}❌ Big Map ${size_x}x${size_y} FAILED.${RESET}"
			if echo "$bsq_out" | grep -q "map error"; then
				echo -e "${RED}   ↳ Reason: Program unexpectedly printed 'map error' on a valid stream!${RESET}"
			else
				echo -e "${RED}   ↳ Reason: Program crashed or exited with code $status${RESET}"
			fi
		else
			echo -e "${GREEN}✅ Big Map ${size_x}x${size_y} PASSED successfully via pipe.${RESET}"
		fi
		echo ""
	done
	exit 0
fi

# ----------------------------
# test loop
# ----------------------------

for mapfile in "$TEST_DIR"/resource/maps/*.map; do
	base=$(basename "$mapfile")
	answerfile="$TEST_DIR/resource/solution/$base"

	[ -f "$mapfile" ] || continue

	if [ ! -f "$answerfile" ]; then
		echo "NO SOLUTION: $base"
		continue
	fi

	expected=$(cat "$answerfile")

	# ----------------------------
	# consistency checks
	# ----------------------------

	out1=$(run_file "$mapfile")
	out2=$(run_stdin_file "$mapfile")
	out3=$(run_pipe_file "$mapfile")

	if [ "$out1" != "$out2" ] || [ "$out1" != "$out3" ]; then
		echo "❌ STDIN mismatch: $base"
		FAIL=$((FAIL + 1))
		continue
	fi

	got="$out1"

	if [ "$got" != "$expected" ]; then
		echo "❌ FAIL: $base"
		FAIL=$((FAIL + 1))
		FAILED_TESTS+=("$base")
		continue
	fi

	# ----------------------------
	# valgrind mode
	# ----------------------------

	if [ $USE_VALGRIND -eq 1 ]; then
		echo "VALGRIND: $base"
		if ! run_valgrind "$mapfile"; then
			echo "❌ VALGRIND FAIL: $base"
			FAIL=$((FAIL + 1))
			continue
		fi
	fi

	# ----------------------------
	# malloc strike mode
	# ----------------------------

	if [ $USE_MALLOC_STRIKE -eq 1 ]; then
		echo "MALLOC STRIKE: $base"
		if ! run_malloc_strike "$mapfile"; then
			echo "❌ MALLOC FAIL: $base"
			FAIL=$((FAIL + 1))
			continue
		fi
	fi

	PASS=$((PASS + 1))
	echo "✅ PASS: $base"

	if [ $VERBOSE -eq 1 ]; then
		print_verbose "$mapfile" "$expected" "$got"
	fi
done

# ----------------------------
# multi-file test
# ----------------------------

echo ""
echo "════════ MULTI FILE TEST ════════"

multi_cases=(
	"01_valid_simple.map 02_valid_minimal_empty.map"
	"01_valid_simple.map 03_valid_minimal_obstacle.map"
	"02_valid_minimal_empty.map 03_valid_minimal_obstacle.map"
	"01_valid_simple.map invalid_bad_header.map"
	"invalid_bad_header.map 01_valid_simple.map"
	"invalid_bad_header.map invalid_bad_chars.map"
	"01_valid_simple.map 02_valid_minimal_empty.map invalid_bad_chars.map"
)

for case in "${multi_cases[@]}"; do
	files=()

	for name in $case; do
		files+=("$TEST_DIR/resource/maps/$name")
	done

	echo ""
	echo -e "${CYAN}🧪 CASE:${RESET} $case"

	multi_out=$(run_multi_file "${files[@]}")

	expected_out=""
	for i in "${!files[@]}"; do
		f="${files[$i]}"

		expected_out+=$(run_file "$f")

		if [ "$i" -lt $((${#files[@]} - 1)) ]; then
			expected_out+=$'\n\n'
		fi
	done

	# normalize trailing newline differences
	multi_out=$(printf "%s" "$multi_out")
	expected_out=$(printf "%s" "$expected_out")

	if [ "$multi_out" = "$expected_out" ]; then
		echo -e "${GREEN}✅ MULTI FILE PASS${RESET}"
	else
		echo -e "${RED}❌ MULTI FILE FAIL${RESET}"

		echo ""
		echo -e "${CYAN}──── EXPECTED ────${RESET}"
		printf "%s\n" "$expected_out"

		echo ""
		echo -e "${CYAN}──── GOT ────${RESET}"
		printf "%s\n" "$multi_out"

		echo ""
		echo -e "${CYAN}──── DIFF ────${RESET}"
		diff \
			<(printf "%s\n" "$expected_out") \
			<(printf "%s\n" "$multi_out") \
			| sed 's/^/  /'

		FAIL=$((FAIL + 1))
	fi
done

# ----------------------------
# stdin test
# ----------------------------

echo ""
echo "════════ STDIN TEST ════════"

for mapfile in "$TEST_DIR"/resource/maps/*.map; do
	[ -f "$mapfile" ] || continue

	name=$(basename "$mapfile")

	echo ""
	echo -e "${CYAN}🧪 STDIN CASE:${RESET} $name"

	arg_out=$(run_file "$mapfile")
	stdin_out=$(run_stdin_file "$mapfile")
	pipe_out=$(run_pipe_file "$mapfile")
	stream_out=$(run_stream_file "$mapfile")

	# normalize trailing newlines
	arg_out=$(printf "%s" "$arg_out")
	stdin_out=$(printf "%s" "$stdin_out")
	pipe_out=$(printf "%s" "$pipe_out")
	stream_out=$(printf "%s" "$stream_out")

	ok=1

	check_diff()
	{
		label="$1"
		got="$2"

		echo -e "${RED}❌ $label FAIL${RESET}"

		echo ""
		echo -e "${CYAN}──── EXPECTED ────${RESET}"
		printf "%s\n" "$arg_out"

		echo ""
		echo -e "${CYAN}──── GOT ────${RESET}"
		printf "%s\n" "$got"

		echo ""
		echo -e "${CYAN}──── DIFF ────${RESET}"
		diff \
			<(printf "%s\n" "$arg_out") \
			<(printf "%s\n" "$got") \
			| sed 's/^/  /'
	}

	if [ "$arg_out" != "$stdin_out" ]; then
		ok=0
		check_diff "REDIRECT STDIN" "$stdin_out"
	fi

	if [ "$arg_out" != "$pipe_out" ]; then
		ok=0
		check_diff "PIPE STDIN" "$pipe_out"
	fi

	if [ "$arg_out" != "$stream_out" ]; then
		ok=0
		check_diff "STREAM STDIN" "$stream_out"
	fi

	if [ $ok -eq 1 ]; then
		echo -e "${GREEN}✅ STDIN PASS${RESET}"
	else
		FAIL=$((FAIL + 1))
	fi
done

# ----------------------------
# summary
# ----------------------------

TOTAL=$((PASS + FAIL + MISSING))

echo ""
echo "════════ RESULTS ════════"
echo "PASS: $PASS"
echo "FAIL: $FAIL"
echo "MISSING: $MISSING"
echo "TOTAL: $TOTAL"
