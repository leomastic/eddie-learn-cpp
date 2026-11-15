# Day 32 Exam Notes

## Exam record

The exam duration was 150 minutes. The actual start and end times and the time
spent on each problem were not provided, so they are left for the student to
complete rather than estimated.

| Record | Actual time |
|---|---|
| Exam start | [Fill in from your own record] |
| Exam end | [Fill in from your own record] |
| Total time spent | [Fill in from your own record] |

| Problem | Time spent |
|---|---|
| Problem 1 | [Fill in] |
| Problem 2 | [Fill in] |
| Problem 3 | [Fill in] |
| Problem 4 | [Fill in] |
| Problem 5 | [Fill in] |

### Help used

AI assistance was used in this conversation to implement or revise Problems 3,
4, and 5 and, after the review described below, to fix Problems 1 and 2. The
timing of the work on Problems 3–5 relative to the exam is not established.
The changes to Problems 1 and 2 in this turn are post-review improvements.
Confirm whether any AI assistance was used during the 150-minute attempt;
do not describe that attempt as unaided if it was.

### Expected score before post-exam tests

Not recorded. The 15/20 score below is a technical assessment reported after
testing, not a recorded pre-test expected score.

## Solutions

The descriptions below document the current source files, not a claim about
when each implementation was written.

### Problem 1 — Digit-weighted checksum

Source: [`problem1.cpp`](./problem1.cpp)

- **Approach:** Read the lock code as a string so values through 10^18 are not
  limited by 32-bit integer storage. Multiply each digit by its 1-based
  position from the left, add the products, and print the checksum and whether
  it is divisible by `k`.
- **Correctness:** The loop visits every decimal digit once and applies the
  position weight used by the checksum definition. The divisibility test then
  directly implements the validity condition.
- **Complexity:** For `d` digits, O(d) time and O(d) space for the input string.
- **Subtasks:** The review report awarded 1/4 to the original version because
  its `int` input could not handle the stated upper bound of 10^18. The current
  string-based version avoids that overflow and has O(d) runtime.
- **Tests:** `1000000000000 1` produced `1 VALID`. The maximum checksum input
  `999999999999999999 1539` produced `1539 VALID`; `1000000000000000000 2`
  produced `1 INVALID`. These focused checks were run after the review.

### Problem 2 — Longest substring with at most K distinct characters

Source: [`problem2.cpp`](./problem2.cpp)

- **Approach:** Use a sliding window and a frequency array for the lowercase
  English alphabet. Expand the right edge, and move the left edge forward
  until the window contains at most `k` distinct characters.
- **Correctness:** After shrinking, the current window is valid. Every right
  endpoint is considered, and the left endpoint moves forward as needed to
  restore validity. Recording only strictly longer windows preserves the
  earliest start among equal maximum lengths.
- **Complexity:** O(n) time because each pointer moves at most `n` times, and
  O(26) auxiliary space.
- **Subtasks:** The review report awarded 2/4 to the original quadratic
  version. The current linear sliding-window version is suitable for the
  reported `n = 200,000` limit.
- **Tests:** `aabbaa` with `k=1` produced length 2, start 1, and `abac` with
  `k=2` produced length 3, start 1, confirming the earliest-start tie rule.
  `K=0` produced `0 0`. A 200,000-character all-`a` string with `k=1`
  produced length 200,000, start 1. These focused checks were run after the
  review.

### Problem 3 — Prime factor queries

Source: [`problem3.cpp`](./problem3.cpp)

- **Approach:** Sieve up to the largest queried `R`, incrementing the
  distinct-prime-factor count of each multiple of every prime. Build a prefix
  count for each `K` from 0 through 7. Answer a range query by subtracting the
  prefix count at `L - 1` from the one at `R`.
- **Correctness:** Each prime visits all and only its multiples, so every
  integer's count is incremented once for each distinct prime divisor,
  regardless of the divisor's exponent. Prefix subtraction counts exactly
  the matching values in the inclusive interval.
- **Complexity:** O(M log log M + 8M + Q) time and O(8M) space, where `M` is
  the largest queried `R`.
- **Subtasks:** The sieve and prefix sums support the stated full constraints
  (`R <= 1,000,000`, `Q <= 100,000`).
- **Tests:** The provided sample produced `1, 7, 2, 6`. Additional checks
  covered `1` with `K=0` and `K=1`, `30` with `K=2` and `K=3`, and the full
  range through 1,000,000 with `K=7`; the outputs matched the expected
  boundary behavior. No failed test is recorded.

### Problem 4 — Energy range analysis

Source: [`problem4.cpp`](./problem4.cpp)

- **Approach:** Build 64-bit prefix sums. For each query, compute the total as
  `prefix[R] - prefix[L - 1]`, then compare that total with `T`.
- **Correctness:** The prefix difference cancels all values before `L` and
  leaves exactly the inclusive sum from `L` through `R`. The comparison
  implements the required “at least `T`” condition.
- **Complexity:** O(N + Q) time and O(N) space.
- **Subtasks:** The linear preprocessing and constant-time queries support
  the stated full constraints. `long long` is needed because a range sum can
  reach magnitude 2 × 10^14.
- **Tests:** The provided sample produced `1 YES`, `3 YES`, `9 YES`, and
  `10 YES`. Additional checks included negative values, totals at the
  threshold, and a total of -1,000,000,000. No failed test is recorded.

### Problem 5 — Divisible pair counter

Source: [`problem5.cpp`](./problem5.cpp)

- **Approach:** Process IDs from left to right. For each ID, use its remainder
  modulo `M` to look up how many previous IDs have the complementary
  remainder. Add that count to the answer, then record the current remainder.
- **Correctness:** A pair's remainders sum to a multiple of `M` exactly when
  they are complementary modulo `M`. Counting only previously seen positions
  counts each `i < j` pair once, including pairs whose IDs are equal.
- **Complexity:** O(N + M) time and O(M) space.
- **Subtasks:** This approach supports the stated full constraints. The answer
  uses 64-bit storage because as many as N(N - 1)/2 pairs can be valid.
- **Tests:** The two provided samples produced `4` and `6`. An additional
  check used repeated IDs of 10^18 with `M=3` and produced `4`; `M=1` was
  covered by the second sample. No failed test is recorded.

## Test record

| Problem | Sample test | Additional test | Failed tests recorded |
|---|---|---|---|
| 1 | Review example checked after fix | Maximum bound checked after fix | Original `int` version failed for large input |
| 2 | Not recorded | 200,000-character cases checked after fix | Original quadratic version timed out at maximum size in review |
| 3 | Passed | Passed | None recorded |
| 4 | Passed | Passed | None recorded |
| 5 | Passed | Passed | None recorded |

The review report states it compiled the original code with C++17, ran 500
random small tests, and tested selected large inputs. Those reported results
are attributed to the reviewer; they were not all independently rerun during
the current changes. The focused checks in the post-review sections were run
separately.

## Review-reported technical assessment

The supplied review reported **15/20** for the pre-fix code: Problem 1 1/4,
Problem 2 2/4, and Problems 3–5 4/4 each. The report attributed the lost
points to Problem 1's 32-bit input and Problem 2's quadratic runtime. This is
a reviewer-reported technical assessment, not a verified independent score
for a timed exam attempt. The review also stated that the independent
150-minute result could not be verified.

## Exam work and post-exam work

### Work completed during the 150-minute exam

You reported that you did not complete all five problems within the
150-minute exam. The actual work performed during that attempt cannot be
reconstructed from the available records. Problems 1 and 2 had pre-existing
source files when this conversation began, but their existence does not
establish when they were written. The reviewer reported that the independent
timed result was not verifiable. Do not treat 15/20 as an independently
achieved exam score.

### Post-exam improvements and checks

Problems 3–5 were implemented or revised with AI assistance in this
conversation and compiled/tested with samples or focused boundary checks.
After the technical review, Problems 1 and 2 were also revised with AI
assistance: Problem 1 now reads the lock code as a string, and Problem 2 now
uses a sliding window. These Problem 1 and 2 changes and their focused checks
are post-review improvements, not work completed during the original exam.
