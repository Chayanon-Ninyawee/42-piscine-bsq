#!/bin/sh

set -e

ROOT_DIR="$(dirname "$0")/.."
TEST_DIR="$ROOT_DIR/tests"

make -C "$ROOT_DIR"
make -C "$TEST_DIR/malloc_strike"

i=1

while true
do
	echo "=== MALLOC STRIKE $i ==="

	output=$(
		MALLOC_STRIKE=$i \
		LD_PRELOAD="$TEST_DIR/malloc_strike/malloc_strike.so" \
		"$ROOT_DIR/bsq" "$TEST_DIR/resource/maps/01_valid_simple.map" \
		2>&1
	)

	echo "$output"

	echo "$output" | grep -q "NO_FAIL" && break

	i=$((i + 1))
	echo ""
done

echo "Finished malloc strike test"
