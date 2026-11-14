#!/usr/bin/env bash
set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
build_dir="$(mktemp -d)"
trap 'rm -rf "$build_dir"' EXIT

for problem in PARKING SENSORS WAREHOUSE STABLE TEAMS; do
    c++ -std=c++17 -O2 -Wall -Wextra -Wpedantic \
        "$root/$problem.cpp" -o "$build_dir/$problem"
done

passed=0
check() {
    local problem="$1"
    local expected="$2"
    local input="$3"
    local actual

    actual="$(printf '%s' "$input" | "$build_dir/$problem")"
    if [[ "$actual" != "$expected" ]]; then
        printf 'FAIL %s: expected <%s>, got <%s>\n' "$problem" "$expected" "$actual" >&2
        exit 1
    fi
    ((passed += 1))
}

check PARKING 28000 $'4\n30\n31\n45\n46\n'
check PARKING 35000 $'1\n300\n'
check SENSORS '2 1 2' $'6\n1 1 2 2 3 3\n'
check SENSORS '5 5 0' $'4\n5 5 5 5\n'
check WAREHOUSE $'2 2\n4 3\n9 1\n10 2\n-1 0' $'8 5\n2 2 4 4 4 9 10 10\n1 4 5 10 11\n'
check STABLE 3 $'5 2\n8 2 4 5 3\n'
check STABLE 3 $'5 0\n-4 -4 -4 1 1\n'
check STABLE 5 $'5 20\n-10 0 7 9 10\n'
check TEAMS 4 $'5 8\n1 2 3 4 5\n'
check TEAMS 10 $'5 12\n4 4 4 4 4\n'
check TEAMS 0 $'4 3\n1 2 3 4\n'

printf 'PASS: %d regression checks\n' "$passed"
