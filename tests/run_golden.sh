#!/bin/sh
# Runs each exercise binary against tests/<name>.in and diffs the
# output against tests/<name>.out. Invoked by `make test`. Exercises
# without golden files (because their output isn't meant to be
# deterministic, or because they're exercised only by unit_tests.c)
# are skipped.

BUILD=${BUILD:-build}
DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
STATUS=0

for name in ex1_02 ex1_04 ex1_06 ex1_13 ex1_24 ex2_01 ex2_02 ex3_01; do
    bin="$BUILD/$name"
    in="$DIR/$name.in"
    out="$DIR/$name.out"

    if [ ! -x "$bin" ]; then
        echo "SKIP $name (binary not built)"
        continue
    fi
    if [ ! -f "$in" ] || [ ! -f "$out" ]; then
        echo "SKIP $name (no golden files)"
        continue
    fi

    tmp="$BUILD/.golden_$name.out"
    "$bin" <"$in" >"$tmp" 2>/dev/null

    if diff -u "$out" "$tmp" >/dev/null 2>&1; then
        echo "PASS $name"
    else
        echo "FAIL $name"
        diff -u "$out" "$tmp"
        STATUS=1
    fi
    rm -f "$tmp"
done

exit $STATUS
