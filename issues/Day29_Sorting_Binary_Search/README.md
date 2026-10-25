# Day29 — Sorting, Binary Search & Constraint-Driven Problem Solving

Each program is a separate C++17 executable. `std::sort` is used to order inputs before searches; exact search and both bound functions are implemented directly rather than calling standard-library search helpers.

## Sorting and search traces

Sorting `8 3 8 1 5` gives `1 3 5 8 8`. The two 8s occupy sorted indexes 3 and 4; after sorting, equal values do not carry enough information to tell which came from original index 0 versus index 2.

For exact binary search on indexed `[1,3,5,8,8]`:

| Target | Trace `(left,right,mid,value)` and decision | Result |
|---:|---|---:|
| 5 | `(0,4,2,5)` match | index 2 |
| 7 | `(0,4,2,5)` go right; `(3,4,3,8)` go left; interval ends | not found |
| 8 | `(0,4,2,5)` go right; `(3,4,3,8)` match | index 3 (not necessarily the first duplicate) |
| 1 in `[1]` | `(0,0,0,1)` match | index 0 |
| 2 in `[1]` | `(0,0,0,1)` go right; interval ends | not found |

For bounds on `[1,2,2,2,4,7]`, query 2 gives lower index 1 and upper index 4 (frequency 3); query 3 gives indices 4 and 4 (frequency 0). Both functions return index `N` when no qualifying position exists.

## Problem 1 — Ticket Lookup

**Maximum constraints:** `N = Q = 200,000`, code `<= 10^9`.

**Naive idea and work:** Scan all `N` codes for each query: `O(NQ)`, up to 40 billion comparisons. This does not fit.

**Improved idea:** Sort the codes once, then run inclusive-interval exact binary search for every query. Duplicates are harmless because the output only needs existence; the search may return any matching index.

**Correctness:** Sorting preserves each code's presence. In each binary-search step, if a target remains, it lies in `[left,right]`: values below the middle can be discarded when the middle is too small, and values above it can be discarded when too large. Equality reports `YES`; an exhausted interval reports `NO`.

**Boundary cases:** Empty remaining search interval, one item, duplicates, target below/above all values, and absent target between two values.

**Complexity:** `O(N log N + Q log N)` time; `O(N)` input storage.

**Sample output:**
```text
YES
NO
YES
YES
NO
```

**Additional tests (input -> output):**

1. `1 3; codes: 7; queries: 7 6 8` -> `YES NO NO`
2. `5 4; codes: 4 4 4 4 4; queries: 4 3 5 4` -> `YES NO NO YES`
3. `6 4; codes: 10 2 8 4 6 12; queries: 1 5 12 13` -> `NO NO YES NO`

## Problem 2 — Equal Score Frequency

**Maximum constraints:** `N = Q = 200,000`, score `<= 10^9`.

**Naive idea and work:** Scan all scores for each query: up to 40 billion comparisons, which does not fit.

**Improved idea:** Sort once. Implement lower bound (first element `>= x`) and upper bound (first element `> x`). The difference between these indexes is the score frequency.

**Correctness:** In sorted order, all values equal to `x` form one contiguous range from the first value not less than `x` to the first value greater than `x`. Its length is exactly `upperBound(x) - lowerBound(x)`. If no value equals `x`, both indexes are equal.

**Boundary cases:** Empty helper input, no matching score, all values below/above the query, one match, and a run of duplicates.

**Complexity:** `O(N log N + Q log N)` time; `O(N)` input storage.

**Sample output:**
```text
3
2
0
1
```

**Additional tests (input -> output):**

1. `1 3; scores: 5; queries: 5 4 6` -> `1 0 0`
2. `5 4; scores: 7 7 7 7 7; queries: 7 6 8 7` -> `5 0 0 5`
3. `6 5; scores: 0 2 2 5 9 9; queries: 0 2 3 9 10` -> `1 2 0 2 0`

## Problem 3 — First Affordable Upgrade

**Maximum constraints:** `N = Q = 200,000`, price and threshold `<= 10^9`.

**Naive idea and work:** Inspect every price per threshold, up to 40 billion comparisons.

**Improved idea:** Sort prices and use a custom lower bound for each threshold. If its returned index is `N`, print `-1`; otherwise print the price at that index.

**Correctness:** Lower bound returns the first sorted price not less than the threshold, which is exactly the smallest qualifying available price. If the index is `N`, every price is smaller than the threshold, so no answer exists. Returning a smaller nearby price would violate the threshold.

**Boundary cases:** Threshold below all prices, equal to a duplicate, between prices, equal to the maximum, and above the maximum.

**Complexity:** `O(N log N + Q log N)` time; `O(N)` input storage.

**Sample output:**
```text
15
40
40
100
-1
```

**Additional tests (input -> output):**

1. `1 3; prices: 10; thresholds: 1 10 11` -> `10 10 -1`
2. `5 4; prices: 5 5 5 5 5; thresholds: 5 4 6 5` -> `5 5 -1 5`
3. `4 5; prices: 20 3 12 8; thresholds: 1 4 9 13 20` -> `3 8 12 20 20`

## Problem 4 — Pairs Under a Limit

**Maximum constraints:** `N = 200,000`, `S <= 2,000,000,000`, values `<= 1,000,000,000`.

**Naive idea and work:** Check every pair of positions in `O(N^2)`, up to about 20 billion pairs. This does not fit.

**Improved idea:** Sort once. For every index `i`, binary-search the first position after all values `<= S - a[i]` using the custom upper bound. Count only indexes from `i+1` up to (but not including) that result. This avoids enumerating pairs and does not use two pointers.

**Correctness:** Because values are sorted, all partner values satisfying `a[j] <= S-a[i]` precede the upper-bound position. Restricting the counted interval to `j > i` counts each valid pair of distinct positions exactly once and excludes pairing an item with itself. Pair counts use `long long`.

**Boundary cases:** No pair qualifies; all pairs qualify; duplicate values; threshold exactly equal to a pair sum; a limit smaller than the smallest possible pair sum.

**Complexity:** `O(N log N)` time including sorting and one binary search per first index; `O(N)` input storage.

**Sample output:**
```text
6
```

**Additional tests (input -> output):**

1. `N=2, S=2; values: 1 1` -> `1`
2. `N=4, S=3; values: 1 2 2 3` -> `2`
3. `N=5, S=10; values: 1 2 3 4 5` -> `10`

## Problem 5 — Minimum Machine Speed

**Maximum constraints:** `N = 100,000`, `H <= 10^12`, `work[i] <= 10^9` and `H >= N`.

**Naive idea and work:** Test every speed from 1 to `max(work)`, scanning all jobs each time. This takes `O(N * max(work))`, up to `10^14` job checks.

**Improved idea:** Binary-search speed in `[1,max(work)]`. Feasibility is monotonic: increasing speed cannot increase any job's required hours, so once a speed works, all larger speeds work. Use the lower-bound invariant: the minimum feasible speed remains in `[left,right]`; feasible mid moves `right` to mid, otherwise `left` to mid+1. Calculate ceiling division as `work/speed + (work%speed != 0)` and stop as soon as accumulated hours exceed `H`.

**Correctness:** For any fixed speed, summing the integer ceiling hours gives exactly the sequential processing time. The monotonic property makes the feasible speeds a suffix of the search interval. The binary search preserves the first feasible speed and terminates with `left == right`, the minimum feasible value. `H >= N` guarantees speed `max(work)` is feasible because each job then takes one hour.

**Boundary cases:** One job, `H=N`, speed 1 already works, exact ceiling divisions, and speed `max(work)` as the guaranteed feasible upper bound.

**Complexity:** `O(N log(max(work)))` time; `O(N)` input storage.

**Sample output:**
```text
4
```

**Additional tests (input -> output):**

1. `1 1; work: 1` -> `1`
2. `3 3; work: 5 5 5` -> `5`
3. `4 10; work: 3 6 7 11` -> `3`
4. `4 8; work: 3 6 7 11` -> `4`

## Experiments

### A — Exact search and B — Bounds

Ran 150 deterministic generated sorted arrays (seed `2901`), each with a length from 0 through 40 and values in `[-10,10]`. For each, queried every integer from `-12` through `12`. Exact search's found/not-found result was compared with a linear search; lower and upper indexes were compared with direct loops. This includes empty arrays, missing values, duplicates, and out-of-range values.

**Observed result:** all exact-search and bound comparisons passed.

### C — Complexity work estimates

Assume each linear search inspects all `N` entries (for example, an unsuccessful query or a match at the end). For `Q=N`, estimate linear search as `N*Q` comparisons and sorting plus binary searches as `N log2(N) + Q log2(N)` comparison-scale work. These are asymptotic estimates, not measured runtimes:

| N=Q | Repeated linear comparisons | Sort + binary-search estimate |
|---:|---:|---:|
| 1,000 | 1,000,000 | about 19,932 |
| 10,000 | 100,000,000 | about 265,754 |
| 100,000 | 10,000,000,000 | about 3,321,928 |

### D — Pair counting

Compared the Problem 4 counting function against nested-loop enumeration on 50 deterministic random arrays (seed `2901`), with `2 <= N <= 30`, values in `[1,50]`, and limits in `[1,100]`.

**Observed result:** all 50 counts matched. The `O(N^2)` reference is useful at these small sizes because it directly checks each pair; at `N=200,000`, about 20 billion pair checks make it unsuitable as the submitted algorithm.

### E — Minimum machine speed

Compared Problem 5 with trying every speed from 1 through `max(work)` for 50 deterministic random cases (seed `2901`), with `1 <= N <= 10`, each work value in `[1,30]`, and `H >= N`.

**Observed result:** all 50 minimum speeds matched. The reference is tractable for these tiny cases; the production solution checks feasibility in `O(N)` at each of only `O(log(max(work)))` binary-search steps. Speeds are monotonic because each `ceil(work[i]/speed)` cannot increase when speed increases. The search keeps the first feasible speed in `[left,right]`.

### F — Maximum-constraint executions

Built all targets in Release mode with **GNU C++ 15.2.0** (`c++ (Ubuntu 15.2.0-16ubuntu1)`) on **Linux x86_64**, host `eddie-p5570`, kernel `7.0.0-38-generic` (20 online logical CPUs). Inputs were generated at the maximum `N` and, for the query programs, maximum `Q`. Times and peak resident memory are the actual `/usr/bin/time` results, rounded to hundredths of a second / KB by the command's format:

| Program | Executed maximum-size case | Actual result | Runtime | Peak RSS |
|---|---|---|---:|---:|
| 1 | 200,000 sorted-domain codes and 200,000 in-domain queries | All `YES` (first three: `YES`, `YES`, `YES`) | 0.04 s | 4,420 KB |
| 2 | 200,000 scores and 200,000 queries | Completed (first three frequencies: `20`, `20`, `0`) | 0.03 s | 4,420 KB |
| 3 | 200,000 prices and 200,000 thresholds | Completed (first three results: `7920`, `15839`, `23758`) | 0.05 s | 4,420 KB |
| 4 | 200,000 values, all `1,000,000,000`, limit `2,000,000,000` | `19999900000` | 0.01 s | 5,220 KB |
| 5 | 100,000 jobs each `1,000,000,000`, `H=100,000` | `1000000000` | 0.01 s | 4,416 KB |

All five executions exited successfully. The Problem 4 result equals `N(N-1)/2`, since every pair meets the limit; the Problem 5 result is the required maximum work value when `H=N`.

## Hardest problem

Problem 5 is the hardest because it is not a search over an existing sorted array: feasibility must first be shown to be monotonic, then the binary search must preserve the minimum feasible speed, with safe hour accumulation and ceiling division.

## Build

Configure and build this directory with CMake. It defines five independent targets: `problem1` through `problem5`.
