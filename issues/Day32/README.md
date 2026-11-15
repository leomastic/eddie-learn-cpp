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
4, and 5, and to compile and test those solutions. The conversation does not
establish whether that work took place during the timed exam or afterward.
Confirm the timing and record whether help was used during the 150-minute
attempt; do not describe the attempt as unaided if this assistance occurred
during it.

### Expected score before post-exam tests

5hr

## Solutions

The descriptions below document the current source files, not a claim about
when each implementation was written.

### Problem 1 — Digit-weighted checksum

Source: [`problem1.cpp`](./problem1.cpp)

- **Approach:** Convert the integer to a decimal string. Multiply each digit by
  its 1-based position from the left and add the products. Print the checksum
  and whether it is divisible by `k`.
- **Correctness:** The loop visits every decimal digit once and applies the
  position weight used by the checksum definition. The divisibility test then
  directly implements the validity condition.
- **Complexity:** For `d` digits, O(d) time and O(d) additional space for the
  string.
- **Subtasks:** The source is linear in the number of digits, so it should fit
  any reasonable stated integer limit, assuming the input fits `int` and `k`
  is nonzero. The Problem 1 limits and subtask definitions are not included in
  the available record, so exact subtask claims need checking against the exam
  statement.
- **Tests:** No sample or boundary-test result for this problem is recorded
  here.

### Problem 2 — Longest substring with at most K distinct characters

Source: [`problem2.cpp`](./problem2.cpp)

- **Approach:** Try each starting index and extend the substring one character
  at a time, keeping a set of its distinct characters. Stop extending once
  the set contains more than `k` characters. Save a new answer only when its
  length is strictly greater than the best seen so far.
- **Correctness:** Every possible start is considered, and every valid
  extension from that start is checked. Once the number of distinct characters
  exceeds `k`, a longer extension cannot become valid again. Since equal
  lengths do not replace the saved answer and starts are visited left to
  right, ties retain the earliest starting position.
- **Complexity:** O(n² log σ) worst-case time, where `σ` is the number of
  distinct characters in the input; O(σ) auxiliary space for the set.
- **Subtasks:** The quadratic search is suitable only for small input sizes.
  The Problem 2 limits and subtask definitions are not included in the
  available record, so the exact subtasks passed cannot be confirmed.
- **Tests:** No sample or boundary-test result for this problem is recorded
  here.

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
| 1 | Not recorded | Not recorded | None recorded |
| 2 | Not recorded | Not recorded | None recorded |
| 3 | Passed | Passed | None recorded |
| 4 | Passed | Passed | None recorded |
| 5 | Passed | Passed | None recorded |

“None recorded” means no failure appears in the available test history; it
does not mean unrecorded tests were run.

## Exam work and post-exam work

### Work completed during the 150-minute exam

The timing of the code work in the available conversation cannot be matched
to the exam window. The files for Problems 1 and 2 were already present when
this conversation inspected them. Problems 3, 4, and 5 were implemented or
revised with AI assistance during this conversation. Confirm which of those
activities occurred inside the timed attempt and list them here; do not
attribute work to the exam solely from the current source files.

### Post-exam improvements and checks

This conversation includes implementation or revision of Problems 3, 4, and
5 and compilation/sample or boundary checks for those solutions. Whether
these were post-exam actions or part of the timed attempt is not established.
Once confirmed, move each activity into the appropriate section above.

