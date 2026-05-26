#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
CYAN='\033[0;36m'
BOLD='\033[1m'
RESET='\033[0m'

# Usage: ./run_tests.sh [-v]
VERBOSE=0
if [ "$1" = "-v" ]; then
    VERBOSE=1
fi

PASS=0
FAIL=0
MISSING=0
FAILED_TESTS=()

for mapfile in tests/resource/maps/*.map; do
    base=$(basename "$mapfile")
    answerfile="tests/resource/solution/$base"

    if [ ! -f "$answerfile" ]; then
        MISSING=$((MISSING + 1))
        echo -e "${YELLOW}⚠️  NO SOLUTION: $base${RESET}"
        continue
    fi

    got=$(./bsq "$mapfile")
    expected=$(cat "$answerfile")

    if [ "$got" = "$expected" ]; then
        PASS=$((PASS + 1))
        echo -e "${GREEN}✅ PASS: $base${RESET}"
        if [ $VERBOSE -eq 1 ]; then
            echo ""
            echo -e "${CYAN}  ── INPUT MAP ──────────────────────${RESET}"
            cat "$mapfile" | sed 's/^/  /'
            echo -e "${CYAN}  ── EXPECTED ───────────────────────${RESET}"
            echo "$expected" | sed 's/^/  /'
            echo -e "${CYAN}  ── GOT ────────────────────────────${RESET}"
            echo "$got" | sed 's/^/  /'
            echo -e "${CYAN}  ───────────────────────────────────${RESET}"
            echo ""
        fi
    else
        FAIL=$((FAIL + 1))
        FAILED_TESTS+=("$base")
        echo -e "${RED}❌ FAIL: $base${RESET}"
        if [ $VERBOSE -eq 1 ]; then
            echo ""
            echo -e "${CYAN}  ── INPUT MAP ──────────────────────${RESET}"
            cat "$mapfile" | sed 's/^/  /'
            echo -e "${CYAN}  ── EXPECTED ───────────────────────${RESET}"
            echo "$expected" | sed 's/^/  /'
            echo -e "${CYAN}  ── GOT ────────────────────────────${RESET}"
            echo "$got" | sed 's/^/  /'
            echo -e "${CYAN}  ── DIFF ───────────────────────────${RESET}"
            diff <(echo "$expected") <(echo "$got") | sed 's/^/  /'
            echo -e "${CYAN}  ───────────────────────────────────${RESET}"
            echo ""
        fi
    fi
done

# Print failure summary if not verbose (details shown at end)
if [ $VERBOSE -eq 0 ] && [ ${#FAILED_TESTS[@]} -gt 0 ]; then
    echo ""
    echo -e "${BOLD}══════════ FAILURES ══════════${RESET}"
    for base in "${FAILED_TESTS[@]}"; do
        mapfile="tests/resource/maps/$base"
        answerfile="tests/resource/solution/$base"
        echo ""
        echo -e "${RED}${BOLD}❌ FAIL: $base${RESET}"
        echo -e "${CYAN}  ── INPUT MAP ──────────────────────${RESET}"
        cat "$mapfile" | sed 's/^/  /'
        echo -e "${CYAN}  ── EXPECTED ───────────────────────${RESET}"
        cat "$answerfile" | sed 's/^/  /'
        echo -e "${CYAN}  ── GOT ────────────────────────────${RESET}"
        ./bsq "$mapfile" | sed 's/^/  /'
        echo -e "${CYAN}  ── DIFF ───────────────────────────${RESET}"
        diff <(cat "$answerfile") <(./bsq "$mapfile") | sed 's/^/  /'
        echo -e "${CYAN}  ───────────────────────────────────${RESET}"
    done
fi

# Final summary
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
