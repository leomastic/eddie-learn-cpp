# Day30 verification tests

Run `python3 tests/run_tests.py` from this directory or its parent. The script
compiles all five solutions with C++17 and warnings enabled, checks the
published samples and boundary cases, compares each optimized solution with
an independent brute-force reference on 100 deterministic random cases, and
runs one full-size stress input per problem.

The random seed for problem `p` is `30030 + p`. The brute-force references are
implemented only in the test script; they are not included by the submission
programs. If GNU `/usr/bin/time` is available, the script also reports the
peak resident memory of each stress run. Use `--skip-stress` to run the sample,
boundary, and randomized checks only.

The stress cases use `N = 200,000` (and `M = 200,000` for Problem 3). The
script prints compiler version, the number of cases checked, each stress
result/runtime, and peak memory when available. It exits unsuccessfully on a
compile error, nonzero program exit, timeout, or incorrect output.
