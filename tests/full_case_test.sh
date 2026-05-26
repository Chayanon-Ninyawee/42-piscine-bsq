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
VERBOSE=0

for arg in "$@"
do
	case "$arg" in
		-v)
			VERBOSE=1
			;;
		--valgrind)
			USE_VALGRIND=1
			;;
		--malloc-strike)
			USE_MALLOC_STRIKE=1
			;;
	esac
done

if [ $USE_MALLOC_STRIKE -eq 1 ]; then
	make -C "$STRIKE_DIR"
fi

PASS=0
FAIL=0
MISSING=0
FAILED_TESTS=()

run_command()
{
	tmpfile=$(mktemp)

	set +e
	"$@" > "$tmpfile" 2>&1
	status=$?
	set -e

	output=$(cat "$tmpfile")
	rm -f "$tmpfile"

	echo "$output"

	return $status
}

run_valgrind_test()
{
	mapfile="$1"

	output=$(
		run_command \
			valgrind \
				--leak-check=full \
				--show-leak-kinds=all \
				--errors-for-leak-kinds=definite,possible \
				--error-exitcode=2 \
				"$ROOT_DIR/bsq" "$mapfile"
	)

	status=$?

	if [ $status -ne 0 ]; then
		echo ""
		echo -e "${RED}Valgrind failed${RESET}"
		echo "$output"
		return 1
	fi

	return 0
}

run_malloc_strike_test()
{
	mapfile="$1"
	i=1

	while true
	do
		output=$(
			run_command \
				env \
					MALLOC_STRIKE=$i \
					LD_PRELOAD="$STRIKE_DIR/malloc_strike.so" \
					"$ROOT_DIR/bsq" "$mapfile"
		)

		status=$?

		if [ $status -ne 0 ]; then
			echo ""
			echo -e \
				"${RED}Malloc strike failed at allocation #$i${RESET}"
			echo "$output"
			return 1
		fi

		echo "$output" | grep -q "NO_FAIL" && break

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
	echo -e \
		"${CYAN}  ── INPUT MAP ──────────────────────${RESET}"
	cat "$mapfile" | sed 's/^/  /'

	echo -e \
		"${CYAN}  ── EXPECTED ───────────────────────${RESET}"
	echo "$expected" | sed 's/^/  /'

	echo -e \
		"${CYAN}  ── GOT ────────────────────────────${RESET}"
	echo "$got" | sed 's/^/  /'

	echo -e \
		"${CYAN}  ───────────────────────────────────${RESET}"
	echo ""
}

for mapfile in "$TEST_DIR"/resource/maps/*.map; do
	base=$(basename "$mapfile")
	answerfile="$TEST_DIR/resource/solution/$base"

	if [ ! -f "$answerfile" ]; then
		MISSING=$((MISSING + 1))
		echo -e "${YELLOW}⚠️  NO SOLUTION: $base${RESET}"
		continue
	fi

	got=$("$ROOT_DIR/bsq" "$mapfile")
	expected=$(cat "$answerfile")

	if [ "$got" != "$expected" ]; then
		FAIL=$((FAIL + 1))
		FAILED_TESTS+=("$base")

		echo -e "${RED}❌ FAIL: $base${RESET}"

		if [ $VERBOSE -eq 1 ]; then
			print_verbose "$mapfile" "$expected" "$got"
		fi

		continue
	fi

	if [ $USE_VALGRIND -eq 1 ]; then
		echo -e "${CYAN}🔍 VALGRIND: $base${RESET}"

		if ! run_valgrind_test "$mapfile"; then
			FAIL=$((FAIL + 1))
			FAILED_TESTS+=("$base")
			echo -e "${RED}❌ VALGRIND FAIL: $base${RESET}"
			continue
		fi
	fi

	if [ $USE_MALLOC_STRIKE -eq 1 ]; then
		echo -e "${CYAN}🧪 MALLOC STRIKE: $base${RESET}"

		if ! run_malloc_strike_test "$mapfile"; then
			FAIL=$((FAIL + 1))
			FAILED_TESTS+=("$base")
			echo -e "${RED}❌ MALLOC FAIL: $base${RESET}"
			continue
		fi
	fi

	PASS=$((PASS + 1))
	echo -e "${GREEN}✅ PASS: $base${RESET}"

	if [ $VERBOSE -eq 1 ]; then
		print_verbose "$mapfile" "$expected" "$got"
	fi
done

if [ $VERBOSE -eq 0 ] && [ ${#FAILED_TESTS[@]} -gt 0 ]; then
	echo ""
	echo -e "${BOLD}══════════ FAILURES ══════════${RESET}"

	for base in "${FAILED_TESTS[@]}"; do
		mapfile="$TEST_DIR/resource/maps/$base"
		answerfile="$TEST_DIR/resource/solution/$base"

		echo ""
		echo -e "${RED}${BOLD}❌ FAIL: $base${RESET}"

		echo -e \
			"${CYAN}  ── INPUT MAP ──────────────────────${RESET}"
		cat "$mapfile" | sed 's/^/  /'

		echo -e \
			"${CYAN}  ── EXPECTED ───────────────────────${RESET}"
		cat "$answerfile" | sed 's/^/  /'

		echo -e \
			"${CYAN}  ── GOT ────────────────────────────${RESET}"
		"$ROOT_DIR/bsq" "$mapfile" | sed 's/^/  /'

		echo -e \
			"${CYAN}  ── DIFF ───────────────────────────${RESET}"
		diff <(cat "$answerfile") \
			<("$ROOT_DIR/bsq" "$mapfile") \
			| sed 's/^/  /'

		echo -e \
			"${CYAN}  ───────────────────────────────────${RESET}"
	done
fi

TOTAL=$((PASS + FAIL + MISSING))

echo ""
echo -e "${BOLD}══════════ RESULTS ═══════════${RESET}"
echo -e "${GREEN}${BOLD}  ✅ PASSED:  $PASS${RESET}"
echo -e "${RED}${BOLD}  ❌ FAILED:  $FAIL${RESET}"

if [ $MISSING -gt 0 ]; then
	echo -e "${YELLOW}${BOLD}  ⚠️  MISSING: $MISSING${RESET}"
fi

echo -e "${BOLD}  📊 TOTAL:   $TOTAL${RESET}"
echo -e "${BOLD}══════════════════════════════${RESET}"
