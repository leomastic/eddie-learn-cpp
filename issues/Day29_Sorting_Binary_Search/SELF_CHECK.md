# Day29 SELF_CHECK

## Answers

1. Sorting reorders elements; without saved position data, original indexes are generally lost.
2. Sorting gives an order that lets each binary search discard half the remaining candidates instead of checking each element.
3. `std::sort` takes `O(N log N)` time.
4. Binary search needs a sorted range (or, for answer search, a monotonic condition).
5. Binary search takes `O(log N)` time.
6. `left + (right-left)/2` avoids overflowing from adding two large endpoints.
7. `-1` means the exact target was not found.
8. No. Exact binary search may return any matching duplicate.
9. Lower bound is the first index whose value is greater than or equal to `x`, or `N` if none exists.
10. Upper bound is the first index whose value is strictly greater than `x`, or `N` if none exists.
11. It returns `N`.
12. It returns `N`.
13. Equal values occupy the sorted half-open range `[lowerBound, upperBound)`, whose length is upper minus lower.
14. Compare the returned indexes with a simple left-to-right loop that finds the first index satisfying each condition.
15. `O(QN)`.
16. `O(N log N + Q log N)`.
17. Index `N` means there is no array element at or after the threshold insertion point.
18. Equal values remain in a contiguous range in sorted order; comparisons still discard only portions that cannot contain the target.
19. Only positions `j > i` represent the required unordered distinct-position pair once; earlier positions were already handled.
20. There can be `N(N-1)/2` pairs, which exceeds a 32-bit signed integer at maximum `N`.
21. At `N=200,000`, quadratic work is on the order of tens of billions of checks.
22. Faster speed never increases required hours, so feasible speeds stay feasible at every larger speed.
23. At least one hour is needed per job, so `H >= N` ensures the maximum work value is a feasible speed.
24. At that speed every job takes exactly one hour because all work values are no larger than the maximum.
25. Use `work / speed + (work % speed != 0)` with integer arithmetic.
26. `O(N log(max(work)))`.
27. Small random cases are cheap to solve exhaustively, giving an independent correctness reference for the optimized algorithm.
28. Empty/single-element ranges, targets outside the data, missing in-between targets, duplicates, and first/last positions can expose boundary errors.
29. **Eddie's own reflection — complete personally:** What was the hardest bug or idea for you today?
30. **Eddie's own reflection — complete personally:** What was the most interesting thing you learned today?
