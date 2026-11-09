# Day30 SELF_CHECK

## Answers

1. A contiguous segment contains every array element between its first and last indexes, with no gaps.
2. There are `N(N+1)/2` nonempty contiguous segments: `N` choices of the first index and a suffix of possible end indexes for each.
3. Two pointers move through an array while preserving useful state; a nested-loop enumeration restarts work for many pairs of endpoints.
4. The right pointer advances at most `N` times and the left pointer also advances at most `N` times in total, so their combined movement is linear.
5. In Problem 1, `left` is the earliest start retained after removing enough values to make the current window affordable.
6. A sum can reach `200,000 * 10^9 = 2 * 10^14`, exceeding a 32-bit signed integer.
7. Subtract the value leaving the window and add the value entering it; each shift takes constant time.
8. Removing a negative value can increase a sum, so shrinking does not monotonically restore validity.
9. Yes. With nonnegative values, removing the leftmost value never increases the sum; the same shrinking argument works. Zeros may create several valid start positions but do not invalidate the longest-window method.
10. A frequency table stores how many times each category appears in the current window.
11. When adding a value, increase the distinct count only if its frequency was zero before the increment.
12. When removing a value, decrease the distinct count only if its frequency becomes zero.
13. The answer is `0`, because no nonempty window can contain at most zero distinct categories.
14. In sorted arrays, advancing the pointer at the smaller current value cannot skip a better pair using that value: all remaining values on the other side are at least as large.
15. If `A[i] < B[j]`, advance `i`.
16. Sorting and scanning takes `O(N log N + M log M)` time.
17. Once a window reaches the target sum, removing its leftmost positive value makes it smaller. Trying each such shorter qualifying window is necessary to find the minimum length.
18. If no window reaches `T`, the required segment does not exist; the statement specifies `0`.
19. A monotonic deque is a deque whose values (at stored indexes) stay in increasing or decreasing order.
20. Indexes identify both the value and when it expires as the left edge moves; values alone cannot tell whether an equal or smaller value is still inside the window.
21. The minimum deque's indexes are increasing, and their corresponding values are strictly increasing from front to back.
22. The maximum deque's indexes are increasing, and their corresponding values are strictly decreasing from front to back.
23. While a deque's front index is less than `left`, remove that front index. The solution expires an index when `left` reaches it.
24. With a fixed `right`, all suffixes of a valid window are also valid, so there are exactly `right - left + 1` valid segments ending at `right`.
25. `N(N+1)/2` is about 20 billion when `N=200,000`, larger than the maximum signed 32-bit integer.
26. Each index enters and leaves each deque at most once, so time is `O(N)` and auxiliary space is `O(N)`.
27. Brute force is simple enough to serve as an independent oracle on small inputs; comparing outputs can uncover boundary and invariant errors.
28. Record the seed, generator/ranges, input, and executable version or source revision so another person can recreate the case.
29. **Eddie's personal reflection — to be answered by Eddie:** Which problem was hardest, and where did you get stuck?
30. **Eddie's personal reflection — to be answered by Eddie:** Which new technique will be most useful in a future contest, and why?
