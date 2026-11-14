# Day 31 self-check

## Answers

1. A 64-bit total is needed because the sum includes the fees from every parking session. Even if each fee is capped, many capped fees can exceed the 32-bit signed maximum.
2. A **started** 15-minute block is any partial or complete block after the free/initial 30 minutes. The number charged is the ceiling of the excess minutes divided by 15: 1–15 extra minutes count as one block, 16–30 as two.
3. For an even-length sorted array, the lower median is the earlier of the two middle values, at zero-based index `(N-1)/2`.
4. Sorting puts equal values together. The scan updates the mode only when a frequency is strictly greater than the best frequency; because values are visited in ascending order, the first value with the winning frequency remains the mode, resolving ties to the smallest value.
5. Sorting places equal package weights next to each other and lets binary search find the smallest weight that is at least the requested weight in `O(log N)` rather than scanning all packages for each query.
6. `lower_bound(x)` finds the first element `>= x`; `upper_bound(x)` finds the first element `> x`.
7. An index of `N` is the end position: no array value is at least the query.
8. A full scan costs `O(N)` per query, or `O(NQ)` altogether. At large `N` and `Q`, that amount of work is too large; sorting once and using binary search reduces it to `O(N log N + Q log N)`.
9. A contiguous period is stable when its maximum value minus its minimum value is no more than the allowed limit.
10. A running sum can be updated by subtracting the departing value, but it does not reveal the current minimum or maximum. The condition depends on both extrema, which may change when either endpoint moves.
11. A monotonic deque stores candidate array indexes for one extremum: the minimum deque's values increase from front to back, while the maximum deque's values decrease. The indexes also indicate when candidates leave the window.
12. An index outside the current window cannot be used as its minimum or maximum. Keeping it at the front could report an extremum that is no longer in the period.
13. Each index is inserted into and removed from each deque at most once. Though shrinking uses a `while` loop inside the right-pointer loop, total pointer/deque operations are `O(N)`, not `O(N^2)`.
14. A team must contain three different students, so its members are three distinct positions in the input—even if some students have equal skill values.
15. If every triple satisfies the condition, the maximum is `C(N,3) = N(N-1)(N-2)/6`.
16. The answer can be on the order of `N^3`. It can exceed a 32-bit integer even when `N` itself fits in an `int`, so the team count uses `long long`.
17. After sorting, if the smallest remaining pair with a fixed first student satisfies the limit even with the largest right value, every value between `left+1` and `right` also satisfies it. They can all be counted at once as `right-left` teams.
18. Subtasks award partial credit for simpler solutions that handle smaller input bounds. They make it possible to earn points before implementing the fully optimized algorithm and expose which constraints require better complexity.
19. **Personal reflection draft—please edit to match your experience:** Question 1 was hardest because I had to carefully model the first billable block after 30 minutes, round partial 15-minute blocks upward, and apply the per-session cap before adding the fees. The key obstacle was avoiding an off-by-one error at exact 15-minute boundaries.
20. **Personal reflection draft—please edit to match your actual 150 minutes:** Next time, I would budget 10 minutes to read constraints and plan, 20 minutes for Question 1, 25 minutes each for Questions 2 and 3, 35 minutes for Question 4, 20 minutes for Question 5, and reserve the final 15 minutes for boundary tests. That totals 150 minutes and protects time for the deque problem and final review.

## Personalization note

Answers 19–20 are suggested first-person drafts, not a record of what the
student actually experienced or how the 150 minutes were spent. Replace them
with truthful reflections before submitting.
