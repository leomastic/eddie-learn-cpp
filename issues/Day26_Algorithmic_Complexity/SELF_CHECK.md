# Day26 Self Check

1. Algorithmic complexity describes how the work required by an algorithm grows as the input size increases.
2. No. Big O usually describes growth rate, not exact seconds.
3. N usually represents the size of the input, such as the number of elements or the size of a problem instance.
4. O(1) means constant time: the work does not grow with input size.
5. Example: accessing `numbers[0]` or doing `a + b`.
6. O(N) means linear time: the work grows proportionally to N.
7. Example: iterating through a vector once to find the sum or maximum.
8. If N doubles, an O(N) algorithm does about twice the work.
9. O(N²) means quadratic time: the work grows with the square of N.
10. A nested loop is the most common structure that produces O(N²).
11. If N doubles, N² grows by about four times.
12. No. Two separate O(N) loops are still O(N) overall because N + N = 2N, and constants are ignored.
13. The complexity of N + N is O(N).
14. The complexity of N × N is O(N²).
15. O(log N) means the work is reduced by repeated halving, so it grows much more slowly than linear time.
16. Binary search is the common example of logarithmic behavior.
17. One million can be divided by 2 about 20 times before reaching 1.
18. Binary search is approximately O(log N).
19. Binary search is much faster because it throws away half the remaining candidates at each step.
20. O(N log N) is commonly associated with efficient sorting algorithms such as merge sort or `std::sort` in practice.
21. You read constraints first because the best algorithm depends on the maximum input size and time budget.
22. No. An O(N²) solution can still be fine when N is small enough.
23. Maximum N matters because exponential or quadratic growth can become impossible at large input sizes.
24. For N = 10, O(N²) is usually not a problem.
25. For N = 100,000, O(N²) is worrying because it is about 10 billion operations.
26. 100,000² is 10,000,000,000.
27. A subtask is a smaller test case or a restricted version of the main problem.
28. A slower algorithm can still be useful for a subtask if the small input size makes it fast enough to pass that part.
29. No. Even a partial solution may earn points when the full problem is too hard yet.
30. If N = 100,000 and Q = 100,000, and each query scans all N elements, the complexity is about O(NQ) = O(10^10) work.
31. Repeated work matters because it can create huge total costs even when each step looks small.
32. Preprocessing means doing some setup work once in advance so later operations are cheaper.
33. Preprocessing can make later queries faster by avoiding repeated costly work.
34. The fastest theoretical algorithm is not always the best to implement because it may be much harder to write, test, and debug.
35. Before implementing an HSG solution, ask: what are the constraints, what is the naive algorithm, what is the rough complexity, and is it likely fast enough?
36. The problem that most clearly forces us to avoid a naïve algorithm is the teacher's large-limit problem, because the cost of checking everything becomes huge.
37. I am most likely to make the mistake of forgetting to estimate the maximum workload before coding.
38. The hardest idea to understand today was realizing that a nested loop can quickly become a huge number of operations even when each loop looks simple.
39. The most interesting thing I learned was that the same algorithm can be perfectly fine for small N but completely impossible for large N.
40. My personal analysis is that complexity is not just about correctness; it is about choosing a strategy that fits the problem's real limits.
