# Day30 — Two Pointers & Sliding Window

Five independent C++17 programs practice maintaining a useful range while its
endpoints move. Each problem has its own executable target: `problem1` through
`problem5`. The optimized submissions contain no brute-force reference code.

## Core ideas

A **contiguous segment** contains every position between its endpoints. A
**sliding window** is such a segment `[left, right]` whose maintained state is
updated as either endpoint moves. The right endpoint visits each element once;
the left endpoint also visits each element at most once. Thus a nested shrinking
loop can still be linear overall: there are at most `N` right moves and `N` left
moves, not `N` left scans for every right endpoint.

For sum-based windows, nonnegative values make shrinking monotonic: removing a
value never increases the sum. Problem 1's positive-value condition is enough,
and zero values are safe too. Negative values break that argument because
removing one can increase the sum.

For a fixed-size window of length `K`, calculate the first sum once, then
subtract the departing value and add the arriving value at each shift. For
category constraints, maintain a frequency table and update the distinct count
only when a frequency crosses zero. For two sorted arrays, compare current
values and advance the pointer at the smaller value. For range minima and
maxima, monotonic deques keep only indexes that can still be extremal.

## Manual traces

### Problem 1: longest affordable streak

For `a = [2,1,3,2,4]`, budget `S = 5`, the following table records the state
after adding each right endpoint. `left moves` lists each removed value, so the
trace includes more than six pointer movements.

| `right` | added | sum before shrinking | values removed | `left` after | remaining sum | best length |
|---:|---:|---:|---|---:|---:|---:|
| 0 | 2 | 2 | — | 0 | 2 | 1 |
| 1 | 1 | 3 | — | 0 | 3 | 2 |
| 2 | 3 | 6 | 2 | 1 | 4 | 2 |
| 3 | 2 | 6 | 1, 3 | 3 | 2 | 2 |
| 4 | 4 | 6 | 2 | 4 | 4 | 2 |

After shrinking, the active sum is at most 5. At `right=3`, removing the
initial `2` leaves 6, so one more value must be removed before the window is
valid.

### Problem 2: at most two badge categories

For `[1,2,1,3,2]`, `K=2`, the longest length is 3. At `right=3`, adding `3`
creates three distinct categories. Removing the first `1` does not remove its
category because another `1` remains, so the next removal (`2`) leaves the
valid window `[1,3]`. At `right=4`, adding `2` again creates three categories;
removing the remaining `1` leaves `[3,2]`. The longest window remains the
earlier `[1,2,1]` of length 3. The current window's frequency table always
describes exactly the indexes from `left` through `right`.

### Problem 3: closest pair across sorted teams

For sorted `A=[1,5,9]` and `B=[3,6,12]`:

| `i`, `j` | values | difference | move |
|---|---|---:|---|
| 0, 0 | 1, 3 | 2 | advance `i` |
| 1, 0 | 5, 3 | 2 | advance `j` |
| 1, 1 | 5, 6 | 1 | advance `i` |
| 2, 1 | 9, 6 | 3 | advance `j` |
| 2, 2 | 9, 12 | 3 | advance `i`; scan ends |

The minimum difference is 1.

### Problem 4: shortest sufficient segment

For `[2,3,1,2,4,3]`, `T=7`, every right extension and each shrinking step is
shown. The right pointer moves six times and `left` advances five times.

| `right` | added | sum before shrinking | qualifying lengths examined | `left` after | remaining sum | best |
|---:|---:|---:|---|---:|---:|---:|
| 0 | 2 | 2 | — | 0 | 2 | — |
| 1 | 3 | 5 | — | 0 | 5 | — |
| 2 | 1 | 6 | — | 0 | 6 | — |
| 3 | 2 | 8 | 4 | 1 | 6 | 4 |
| 4 | 4 | 10 | 4, 3 | 3 | 6 | 3 |
| 5 | 3 | 9 | 3, 2 | 5 | 3 | 2 |

The loop keeps shrinking for as long as the sum reaches `T`; stopping after
the first qualifying window would miss shorter windows ending at the same
right endpoint.

## Problems, invariants, and complexity

### Problem 1 — Longest Affordable Streak

**Algorithm.** Add each new day's positive time to a `long long` running sum.
While the sum exceeds `S`, subtract the leftmost day's time and move `left`.
Record the largest remaining window length. `best` starts at zero, so a
single value above the budget correctly yields zero.

**Invariant and correctness.** After shrinking, the current window sum is at
most `S`. Because all times are positive, any start before `left` includes
values that made an earlier window too expensive; removing values from the
left is the only way to restore affordability. Thus for each right endpoint
the maintained window is the longest affordable one, and maximizing its
length gives the answer.

**Complexity.** `O(N)` time and `O(N)` storage for the input (`O(1)` auxiliary
space).

**Sample output:** `3`.

**Boundary checks:** One value with `S=0`, one value that fits, every value
over budget, a zero budget, and a budget large enough for the entire array.

### Problem 2 — Distinct Badge Window

**Algorithm.** Use a frequency vector for IDs in `[1,10^6]`. Add a category
when `right` advances; increase `distinct` only on a zero-to-one frequency
transition. While `distinct>K`, remove values at `left`, decreasing `distinct`
on a one-to-zero transition. Keep the longest valid window. `K=0` naturally
returns zero.

**Invariant and correctness.** The vector counts exactly the categories in
`[left,right]`, and after shrinking `distinct<=K`. For a given right endpoint,
the earliest left that restores the constraint gives the longest valid window
ending there. The maximum across endpoints is therefore the desired length.

**Complexity.** `O(N+V)` time and `O(N+V)` storage, with `V=1,000,000` for the
frequency table and input.

**Sample output:** `4`.

**Boundary checks:** `K=0`, all equal IDs, all distinct IDs, and a category
that disappears from the window and later reappears.

### Problem 3 — Closest Pair Across Teams

**Algorithm.** Sort both score arrays. Compare `A[i]` with `B[j]`, update
the smallest absolute difference, then advance the pointer at the smaller
score (advance `j` when equal).

**Correctness.** If `A[i]<B[j]`, pairing `A[i]` with any later `B` value cannot
improve on the current difference because those `B` values are no smaller.
Thus no optimal pair is lost by advancing `i`. The symmetric argument applies
when `B[j]<A[i]`. A pair is checked at each step until one array is exhausted.

**Complexity.** `O(N log N + M log M)` time including sorting, and `O(N+M)`
storage for the arrays.

**Sample output:** `2`.

**Boundary checks:** Equal scores, singleton arrays, duplicates, and scores
at opposite ends of the allowed range.

### Problem 4 — Shortest Sufficient Segment

**Algorithm.** Add each positive value to the running sum. While the sum is
at least `T`, record the current length, remove the leftmost value, and move
`left`. Print zero if no qualifying window was found.

**Invariant and correctness.** At the end of each right iteration, the sum is
less than `T` (or `left` has passed the current right after testing a
single-value window). Every qualifying window ending at that right endpoint
was visited while shrinking, including its shortest qualifying version.
Positive values mean extending the left edge only decreases the sum. Comparing
all recorded lengths yields the minimum; the sentinel maps no solution to 0.

**Complexity.** `O(N)` time and `O(N)` input storage (`O(1)` auxiliary space).

**Sample output:** `2`.

**Boundary checks:** No solution, a single value meeting `T`, the whole array
as the only solution, and a large total sum.

### Problem 5 — Count Bounded-Difference Segments

**Algorithm.** Store candidate indexes in an increasing-value minimum deque
and a decreasing-value maximum deque. When adding an index, discard dominated
candidates from each back. Advance `left` while current maximum minus minimum
exceeds `D`, expiring an index when it reaches a deque's front. For every
right endpoint, add `right-left+1` valid segments to the `long long` answer.

**Invariant and correctness.** The front of the minimum deque is the smallest
value in the active window and the front of the maximum deque is the largest;
each deque contains only unexpired indexes. After shrinking, their difference
is at most `D`. Every suffix ending at `right` that starts at or after `left`
is valid, and earlier starts are invalid because their range contains the
current invalid window as a subset. There are exactly `right-left+1` such
suffixes, counted once at this endpoint.

**Complexity.** `O(N)` amortized time and `O(N)` auxiliary space. Each index
enters and leaves each deque at most once.

**Sample output:** `7`.

**Boundary checks:** `D=0`, all equal values, increasing values, alternating
low/high values, and `N=200,000`.

## Reproducible verification

Run `python3 tests/run_tests.py`. It compiles each solution using `g++` with
C++17 and warning flags, checks the five published samples and 23 additional
boundary cases, compares every optimized solution against its independent
brute-force reference for 100 random cases, and checks full-size stress inputs.
Random seeds are `30031` through `30035`. Stress inputs use `N=200,000` and
`M=200,000` for Problem 3. See [tests/README.md](tests/README.md) for details.

**Executed results in this workspace:** All five samples and 23 boundary
cases passed; all 500 randomized brute-force comparisons passed; all five
maximum-size stress cases passed using `g++ (Ubuntu 15.2.0-16ubuntu1)
15.2.0`. Measurements from the run:

| Problem | Stress size | Output | Runtime | Peak RSS |
|---:|---|---:|---:|---:|
| 1 | `N=200,000` | `200000` | 0.009 s | 5,220 KiB |
| 2 | `N=200,000` | `200000` | 0.009 s | 8,260 KiB |
| 3 | `N=M=200,000` | `1` | 0.017 s | 6,820 KiB |
| 4 | `N=200,000` | `200000` | 0.006 s | 5,048 KiB |
| 5 | `N=200,000` | `20000100000` | 0.009 s | 4,400 KiB |

Peak RSS was measured with GNU `/usr/bin/time`; runtimes and memory depend on
the machine. The rerunnable command and deterministic seeds are documented in
[tests/README.md](tests/README.md).

## Personal reflections

The answers to the personal reflection questions are intentionally left for
Eddie to write in [SELF_CHECK.md](SELF_CHECK.md), as required by the assignment.
The unanswered Day29 reflections remain separate from this lesson.
