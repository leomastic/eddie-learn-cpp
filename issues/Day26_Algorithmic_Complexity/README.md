# Day26 Results --- Algorithmic Complexity

## Main rule

> Before I code, I read the constraints. Before I choose an algorithm, I estimate its complexity.

Big O describes how an algorithm's work grows as input size grows; it does not give exact runtime. The maximum constraints help determine whether an approach is suitable.

## Experiment 1: calculate N and N²

| N | N² |
|---:|---:|
| 10 | 100 |
| 100 | 10,000 |
| 1,000 | 1,000,000 |
| 10,000 | 100,000,000 |
| 100,000 | 10,000,000,000 |

## Experiment 2: run the work counters

Enter `1` as the first input to run `linearWork()` and `quadraticWork()` for each listed size.

Actual output:

```text
N = 10, linear = 10, quadratic = 100
N = 100, linear = 100, quadratic = 10000
N = 1000, linear = 1000, quadratic = 1000000
N = 10000, linear = 10000, quadratic = 100000000
```

The linear work equals N, while the quadratic work equals N². The gap grows quickly as N increases. I did not run the quadratic loop at N = 100,000; its 10 billion iterations can be calculated directly.

## Experiment 3: consecutive linear loops

Two consecutive loops each doing N operations perform about N + N = 2N operations. Big O ignores the constant factor, so the total complexity remains O(N).

## Experiment 4: nested loops

With N outer iterations and N inner iterations for each outer iteration, the total is N × N = N², so the complexity is O(N²).

## Experiment 5: equal pairs at N = 200,000

200,000² = 40,000,000,000. Comparing every pair is therefore not suitable at this input size. The nested-loop implementation is for the smaller Day26 constraint; a larger-limit version needs a way to avoid checking every pair.

## Experiment 6: repeated halving

Starting from 1,000,000, repeated division by 2 reaches 1 after about 20 divisions. This is the intuition behind O(log N): halving the remaining search space takes very few steps.

## Experiment 7: teacher-problem analysis

### Problem #2 — Robot Race

- Comparing every pair takes O(N²).
- At n = 1,000, there are 1,000 × 999 / 2 = 499,500 distinct pairs.
- This pairwise work looks reasonable for n ≤ 1,000.
- To compare which robot finishes first, calculate the relevant finish-time information for each robot from the given distance and speed.
- O(N²) is not automatically bad; its suitability depends on the maximum input size.

### Problem #17 — Special Prime

- Scanning every integer up to a_i is impossible when a_i can be 10^12.
- Checking to sqrt(a_i) can still take about 10^6 steps for one value. For 100,000 values, that is about 10^11 steps in the worst case.
- The hint not to count all divisors suggests using a mathematical property instead of enumerating divisors.
- A useful property to investigate is the relationship between a number with exactly three positive divisors and the prime factorization of that number.
- A mathematical observation can replace a large search with a small number of checks.

### Problem #21 — Jump

- If each test takes O(|y-x|), large distances make an individual test too expensive.
- With up to 1,000,000 tests, even moderately expensive work per test becomes too much overall.
- The constraints suggest looking for a direct mathematical method with very little work per test, rather than iterating through the entire distance.

| Teacher problem | Main maximum constraint | First complexity considered | Suitable? | Reason |
|---|---|---|---|---|
| #2 Robot Race | n ≤ 1,000 | O(N²) | Yes | About 499,500 pair comparisons at the maximum n. |
| #17 Special Prime | n ≤ 100,000, a_i ≤ 10^12 | Divisor enumeration | No | Even checking to sqrt(a_i) for each value can mean about 10^11 checks. |
| #21 Jump | T ≤ 1,000,000 | O(|y-x|) per test | No | The distance can be huge and the number of tests is large. |

O(N²) can be acceptable for Robot Race because n is only 1,000. For Problem #17, even a square-root scan repeated for 100,000 values could require roughly 100 billion operations; Problem #21 likewise needs very little work per test.

## Challenge 1: find the maximum

Implemented as `findMaximum()` in [main.cpp](./main.cpp). It initializes the answer from the first vector element and inspects each remaining element once, so its time complexity is O(N) and additional space complexity is O(1). Every element must be checked because any unchecked element could be the maximum.

Enter `2`, then N and the N values, to find the maximum.

## Challenge 2: count equal pairs

Implemented as `countEqualPairs()` in [main.cpp](./main.cpp), using nested loops and checking each pair i < j once. Its time complexity is O(N²); the vector storage uses O(N) space. For the sample input `5` followed by `2 7 2 3 2`, the output is `3`.

Enter `3`, then N and the vector values, to count equal pairs.

## Challenge 4: estimate before coding

The loop with `j = i + 1` performs N(N-1)/2 comparisons, so its complexity is O(N²), even though the inner loop gets shorter for later i values. It is correct for equal-pair counting because each valid pair is checked exactly once.

## Subtasks and choosing an algorithm

A correct slower solution can still earn points on a subtask whose constraints are small enough. The goal is the simplest correct algorithm that fits the actual constraints—not to avoid O(N²) in every situation.

## Complexity summary

| Operation/approach | Time complexity |
|---|---|
| Access one vector element | O(1) |
| One pass through N elements | O(N) |
| Two consecutive passes | O(N) |
| Nested N-by-N loops | O(N²) |
| Repeatedly halve the search space | O(log N) |
| Common efficient comparison sorts | O(N log N) |

## Verification

- CMake build succeeds.
- Input `1` produces the four recorded experiment rows above.
- Input `2`, followed by `6` and values `3 17 2 9 21 4`, produces `21`.
- Input `3`, followed by `5` and values `2 7 2 3 2`, produces `3`.
