# Day 31 — Provincial HSG Mock 01

Five standalone C++17 solutions for the parking-fee, sensor-statistics,
warehouse-query, stable-period, and three-student-team questions.

## Session record

- Start time: not recorded.
- End time: not recorded.
- Time budget: 150 minutes.
- Expected score by question: not recorded; fill in from your own estimate.
- Actual tests run: see **Verification** below.
- Unresolved cases: none found in the included regression checks. Original
  statement constraints and sample cases were not available in the workspace,
  so confirm the inferred input/output details against the official sheet.

## Approaches and complexity

| Question | File | Approach | Time | Extra space |
|---|---|---|---:|---:|
| 1 — PARKING | [PARKING.cpp](./PARKING.cpp) | Round excess parking time up to started 15-minute blocks, cap each fee, and accumulate in 64 bits. | `O(N)` | `O(1)` |
| 2 — SENSORS | [SENSORS.cpp](./SENSORS.cpp) | Sort; select the lower median; run-length count the mode, keeping the smallest on ties; count values above the median. | `O(N log N)` | `O(N)` |
| 3 — WAREHOUSE | [WAREHOUSE.cpp](./WAREHOUSE.cpp) | Sort once; use lower/upper bounds per query to find and count the least sufficient weight. | `O(N log N + Q log N)` | `O(N)` |
| 4 — STABLE | [STABLE.cpp](./STABLE.cpp) | Sliding window with monotonic deques for its minimum and maximum. | `O(N)` | `O(N)` |
| 5 — TEAMS | [TEAMS.cpp](./TEAMS.cpp) | Sort and use two pointers for each fixed first student, counting valid triples in bulk. | `O(N^2)` | `O(N)` |

Build all five targets from this directory:

```sh
cmake -S . -B build
cmake --build build
```

Run the regression checks:

```sh
bash tests/run_tests.sh
```

## Verification

Ran `bash tests/run_tests.sh`: **PASS (11 regression checks)**. The script
compiles every solution with C++17 and warning flags, then checks fixed boundary
cases for every problem. The checks cover started-block rounding and the fee
cap; even lower-median and tied-mode behavior; duplicate warehouse weights and
a query beyond the maximum; stable windows with repeated and negative values;
and duplicate skills, distinct positions, and the maximum team count.

Also ran CMake configure and build for all five targets: **PASS**.

## Independent reflections

The requested first-person answers for Questions 19 and 20 are drafts in
[SELF_CHECK.md](./SELF_CHECK.md), because the actual blocker and per-question
time breakdown were not recorded. Edit them to truthfully describe your own
experience before submitting.
