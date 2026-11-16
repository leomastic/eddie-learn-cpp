# Day 33 — Provincial HSG Mock 03

Five standalone C++17 solutions for the electricity-billing, signal-run,
divisor-statistics, maximum-interval, and triple-compatibility problems.

## Solutions and complexity

| Problem | File | Approach | Time | Auxiliary space |
|---|---|---|---:|---:|
| 1 — Electricity Billing | [ELECTRIC.cpp](./ELECTRIC.cpp) | Calculate each household's bill by usage tier, apply the surcharge when applicable, and accumulate the total in 64-bit arithmetic. | `O(N)` | `O(1)` |
| 2 — Longest Signal Run | [SIGNAL.cpp](./SIGNAL.cpp) | Scan maximal runs of equal characters; update only for a strictly longer run so a tie keeps the earliest start. | `O(N)` | `O(1)` |
| 3 — Divisor Statistics | [DIVISORS.cpp](./DIVISORS.cpp) | Sieve divisor counts through the largest queried value, group values by divisor count, and use binary searches to answer each range query. | `O(M log M + Q log M)` | `O(M)` |
| 4 — Maximum Energy Interval | [INTERVAL.cpp](./INTERVAL.cpp) | Build 64-bit prefix sums and maintain a monotonic deque of candidate starts for each allowed interval length. | `O(N)` | `O(N)` |
| 5 — Triple Compatibility | [TRIPLES.cpp](./TRIPLES.cpp) | Count scores by remainder and enumerate nondecreasing remainder triples, adding the appropriate combination count for each multiplicity pattern. | `O(N + M^3)` | `O(M)` |

Here, `N` is the input size, `Q` is the number of divisor queries, `M` in
Problem 3 is the largest queried integer (up to 1,000,000), and `M` in
Problem 5 is the modulus (up to 30).

The Problem 3 implementation has lookup buckets for divisor counts from 0
through 100. Confirm that this matches the original statement's query limit
when the statement is available.

## Verification record

The independent review report supplied with this submission records:

- **C++17 compilation:** 5/5 solutions passed.
- **Test cases:** 590/590 passed — 5 official samples, 580 randomized checks
  against independent reference solutions, and 5 maximum-size stress cases.
- **Maximum-size stress tests:** 5/5 passed.
- No algorithmic correctness defect was reported in those tests.

The report specifically notes these checks:

- **Problem 1:** Tier boundaries at 50, 150, and 200 kWh; individual
  surcharges; and 100,000 households using 109 kWh.
- **Problem 2:** Equal-length runs, one-character input, and a
  200,000-character string.
- **Problem 3:** `d(1) = 1`, divisor counts over small ranges, and 100,000
  queries with right endpoints up to 1,000,000.
- **Problem 4:** All-negative arrays, varied minimum and maximum interval
  lengths, and 200,000 elements.
- **Problem 5:** Duplicate scores, modulus 1, scores up to 10^18, and 200,000
  students.

These are results reported by the independent reviewer; they are not a claim
that the same test suite was rerun for this directory correction.

## Exam and self-check record

The technical review score was **20/20**. It assesses the tested solutions,
not a verified unaided 150-minute exam result. Complete the following from
your own records before treating it as an exam score:

- Problems completed during the timed attempt: [Complete from your own record]
- Assistance used during the timed attempt: [State accurately]
- Exam start, end, and total time: [Complete from your own record]
- Per-problem time spent: [Complete from your own record]

Complete the Day 33 questions in `SELF_CHECK.md` in your own words. No Day 33
self-check has been supplied or inferred from the Day 32 self-check.
