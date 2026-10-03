# Day26 --- Algorithmic Complexity: Why Correct Code Can Still Fail

## Today's mission

Until now, we have mostly asked:

- Does my program produce the correct answer?

For competitive programming, there is a second question:

- Can my program produce the correct answer fast enough?

A program can be logically correct and still receive 0 points because it takes too long for the maximum input.

Today we learn how to estimate that before writing the program.

## 1. A simple example

Suppose we have:

```cpp
std::vector<int> numbers = {4, 7, 2, 9, 5};
```

We want to know whether 9 exists.

One solution:

```cpp
bool found = false;

for (int i = 0; i < numbers.size(); ++i) {
    if (numbers[i] == 9) {
        found = true;
        break;
    }
}
```

For 5 numbers, this is trivial.

But what if there are:

- 100 numbers?
- 100,000 numbers?
- 1,000,000 numbers?
- 100,000,000 numbers?

Now the number of operations matters.

This is called algorithmic complexity.

## 2. What is Big O?

We use notation such as:

- O(1)
- O(log N)
- O(N)
- O(N log N)
- O(N²)

It describes approximately how the amount of work grows when input size N grows.

Do not think of Big O as measuring exact seconds.

Think: if N becomes much larger, how quickly does the amount of work grow?

## 3. O(1) --- Constant time

Example:

```cpp
int first = numbers[0];
```

Whether the vector contains:

- 10 elements
- 1,000 elements
- 1,000,000 elements

we still access one element.

Approximately: 1 operation.

So: O(1)

Another example:

```cpp
int answer = a + b;
```

The size of some unrelated input array does not affect this operation.

## 4. O(N) --- Linear time

Consider:

```cpp
for (int i = 0; i < n; ++i) {
    std::cout << numbers[i] << '\n';
}
```

If:

- N = 10, the loop runs 10 times.
- N = 100,000, it runs 100,000 times.

Approximately: work ≈ N.

Therefore: O(N)

Another example:

```cpp
int sum = 0;

for (int i = 0; i < n; ++i) {
    sum += numbers[i];
}
```

Still: O(N)

## 5. Two separate loops are NOT O(N²)

This is important:

```cpp
for (int i = 0; i < n; ++i) {
    // work
}

for (int i = 0; i < n; ++i) {
    // work
}
```

The work is approximately:

- N + N = 2N

Big O ignores the constant 2.

So this is: O(N), not O(N²)

## 6. O(N²) --- Nested loops

Now:

```cpp
for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
        // work
    }
}
```

For every i, the inner loop runs N times.

Total: N × N = N².

Therefore: O(N²)

Look at how quickly this grows:

| N | N² |
|---|---:|
| 10 | 100 |
| 100 | 10,000 |
| 1,000 | 1,000,000 |
| 10,000 | 100,000,000 |
| 100,000 | 10,000,000,000 |

At N = 100,000, an O(N²) algorithm may require about 10 billion iterations.

That should immediately look dangerous in a programming contest.

## 7. The first HSG habit

Before coding, Eddie should always find the constraints.

If the problem says:

- 1 ≤ N ≤ 100000

stop.

Do not immediately start writing loops.

Ask: What complexity can my solution afford?

This should become automatic.

## 8. Rough contest intuition

This is not an exact law, because operations and computers differ, but it is useful intuition:

- Maximum N = 10 to 20: exponential solutions may sometimes be possible
- ~100: O(N³) may sometimes work
- ~1,000: O(N²) may be possible
- ~100,000: usually look for O(N log N) or O(N)
- ~1,000,000: usually look strongly toward O(N) or near-linear
- 10^9 or 10^18: you normally cannot iterate through every value

Do not memorize this as an absolute rule. Use it as a warning system.

## 9. O(log N)

Suppose the numbers are sorted:

```text
2  5  8  12  17  21  30  42
```

We want 30.

Instead of checking every number, we can inspect the middle.

```text
2 5 8 12 | 17 21 30 42
         ^
```

If the target is larger, eliminate the left half. Then eliminate half again. And again.

This idea is binary search.

For about one million elements:

- linear search: ≈ 1,000,000 checks
- binary search: ≈ 20 checks

Its complexity is: O(log N)

We will study binary search properly later. Today Eddie only needs to understand why repeatedly removing half of the possibilities is extremely powerful.

## 10. O(N log N)

Efficient sorting algorithms commonly run around: O(N log N)

C++ provides: `std::sort(...)`.

We haven't formally studied it yet, so Eddie does not need to use it today.

For now, recognize:

- O(N): very good for large N
- O(N log N): usually good for large N
- O(N²): dangerous when N becomes large

## 11. A real HSG-style example

Suppose:

- N ≤ 100000
- We need to count pairs: A[i] + A[j] == K

A straightforward idea is:

```cpp
for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
        if (a[i] + a[j] == k) {
            ++count;
        }
    }
}
```

Logically, this works.

But complexity is: O(N²)

At N = 100000, there are approximately:

- 100000 × 100000 ≈ 10,000,000,000

possible operations in the roughest estimate.

So in a contest:

- Correct idea for small input ≠ correct full solution.

## 12. Subtasks matter

HSG problems often have subtasks.

Imagine:

- Subtask 1: N ≤ 100
- Subtask 2: N ≤ 1000
- Subtask 3: N ≤ 100000

Maybe Eddie only knows an O(N²) solution.

That does not necessarily mean:

- I cannot solve this problem.

It may mean:

- I can solve Subtask 1 and perhaps Subtask 2.

That can earn points.

This is an important competition strategy:

- Never throw away a correct partial solution just because you cannot yet solve the full constraint.

## 13. Complexity exercise A

Without running anything, determine the complexity.

### Program A

```cpp
for (int i = 0; i < n; ++i) {
    std::cout << a[i];
}
```

Answer: O(N)

### Program B

```cpp
for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
        std::cout << a[i] + a[j];
    }
}
```

Answer: O(N²)

### Program C

```cpp
for (int i = 0; i < n; ++i) {
    std::cout << a[i];
}

for (int i = 0; i < n; ++i) {
    std::cout << a[i];
}
```

Answer: O(N)

### Program D

```cpp
int i = 1;

while (i < n) {
    i *= 2;
}
```

Values might be: 1, 2, 4, 8, 16, 32, 64, ...

Complexity: O(log N)

## 14. Complexity exercise B --- predict first

For each N, calculate approximately how many iterations an O(N²) loop performs.

- N = 10 → 100
- N = 100 → 10,000
- N = 1,000 → 1,000,000
- N = 10,000 → 100,000,000
- N = 100,000 → 10,000,000,000

Write the answers in README before running the experiment. Then we see how the machine behaves.

## 15. Today's programming experiment

Create:

```text
issues/
└── Day26_Algorithmic_Complexity/
    ├── CMakeLists.txt
    ├── main.cpp
    ├── README.md
    └── SELF_CHECK.md
```

Write two functions:

```cpp
long long linearWork(int n) {
    long long operations = 0;

    for (int i = 0; i < n; ++i) {
        ++operations;
    }

    return operations;
}
```

```cpp
long long quadraticWork(int n) {
    long long operations = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ++operations;
        }
    }

    return operations;
}
```

Do not optimize them. Their purpose is to demonstrate growth.

## 16. Run the experiment

Run both with:

- N = 10
- N = 100
- N = 1000
- N = 10000

Record:

- N
- linear operations
- quadratic operations

Expected mathematical relationship:

- linear = N
- quadratic = N²

Do not run the quadratic version with enormous N just to make the computer suffer. The calculation itself tells us what would happen.

For N = 100000, calculate N² instead.

## 17. Challenge 1 --- Find maximum

Given:

- N
- A1 A2 ... AN

find the largest number.

Constraints: 1 ≤ N ≤ 100000

Example:

```text
Input
6
3 17 2 9 21 4

Output
21
```

Requirements:

- use a vector
- one loop to find the maximum
- complexity must be O(N)
- explain why checking every element is necessary

## 18. Challenge 2 --- Count equal pairs

Given N integers, count pairs (i, j) where:

- i < j
- A[i] == A[j]

For today: N ≤ 1000

Example:

```text
Input
5
2 7 2 3 2

Equal pairs of value 2 are:
index 0 and 2
index 0 and 4
index 2 and 4

Output
3
```

Use nested loops.

Expected complexity: O(N²)

This is intentional.

Tomorrow or later, we will ask: Can we do better?

## 19. Challenge 3 --- The trap

Same problem: Count equal pairs.

But change the constraint to: N ≤ 200000.

Do not write a new advanced solution today.

Instead, put in README:

- My Day26 O(N²) solution is / is not suitable because...

Calculate approximately: N² for N = 200,000.

Then propose what you would need conceptually:

- I need some way to avoid comparing every pair.

That is enough today.

Recognizing that the current algorithm is too slow is itself a skill.

## 20. Challenge 4 --- Estimate before coding

Consider:

```cpp
for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
        // one comparison
    }
}
```

Answer in README:

- Is this O(N) or O(N²)?
- Does the inner loop always run N times?
- Does that change the complexity?
- Why should this algorithm produce the correct answer?

And finally:

## Complexity

- Time complexity:
- Space complexity:

This becomes the standard format for the HSG track.

## 23. Don't optimize blindly

There is another important lesson.

Suppose:

- N ≤ 20
- Eddie writes a complicated O(N log N) solution instead of a simple O(N²) solution.

That is not automatically better.

Contest programming asks for:

- the simplest correct algorithm that comfortably fits the constraints.

Simple code is easier to debug.

So do not think: O(N²) = bad.

Think:

- O(N²) with N = 50 → probably fine
- O(N²) with N = 200000 → impossible-looking

Context matters.

## 24. Connection to your current school HSG training

Your teacher's current C++ assignment contains very different limits:

- n = 1000 in some problems
- arrays of 100000 elements
- individual values up to 10^12 or 10^18
- as many as 1000000 test cases

That is exactly why today's lesson matters.

For every HSG problem, do this before coding:

1. Read the maximum constraints.
2. Write down the obvious/naïve algorithm.
3. Estimate its time complexity.
4. Estimate its work at maximum input.
5. Decide whether it is likely suitable.
6. Only then design and code the solution.

Day26 is not about learning every advanced algorithm. It is about recognizing whether the first idea fits the constraints.

## 25. Required README experiments

README must contain Eddie's own results for:

### Experiment 1

Calculate N, N² for 10, 100, 1,000, 10,000, and 100,000.

### Experiment 2

Run `linearWork()` and `quadraticWork()` for reasonable N and compare growth.

### Experiment 3

Explain why two consecutive O(N) loops remain O(N).

### Experiment 4

Explain why nested N loops become O(N²).

### Experiment 5

Calculate: 200000² and explain why Challenge 2's algorithm should not be used for Challenge 3.

### Experiment 6

For N = 1,000,000, repeatedly divide the remaining search space by 2 and determine approximately how many divisions are required to reach 1. Relate this to O(log N).

### Experiment 7 — Analyze Eddie's teacher assignment

Apply today's complexity-first method to three assigned HSG problems.

#### Teacher Problem 2 — ĐUA ROBOT (Robot Race)

Constraints from the assignment:

- n ≤ 1000
- d ≤ 10^9
- v_i ≤ 1000

In README, answer:

- If you compare every pair of robots, what is the complexity?
- Approximately how many pairs exist for n = 1000?
- Does O(N²) look reasonable here?
- What information would you calculate for each robot to decide which finishes first?
- Why does this show that O(N²) is not automatically bad?

Do not search for a more advanced algorithm today.

#### Teacher Problem 17 — SỐ NGUYÊN TỐ ĐẶC BIỆT (Special Prime)

Constraints:

- n ≤ 100000
- a_i ≤ 10^12

The assignment defines a special prime as a positive integer having exactly 3 positive divisors and explicitly says not to loop to count all divisors.

In README, answer:

- Why is checking every integer from 1 to a_i impossible at these limits?
- If you checked up to sqrt(a_i) for every value, approximately how much worst-case work could that require?
- What is the teacher's hint telling you about the intended approach?
- What mathematical property should you try to discover before coding?
- Why can a mathematical observation dramatically reduce complexity?

Do not implement the final solution today. We will formally study primes, divisors, and efficient primality testing later.

#### Teacher Problem 21 — BƯỚC NHẢY (Jump)

Constraints:

- T ≤ 1000000
- 0 ≤ x, y ≤ 2^31

In README, answer:

- What happens if every test takes O(|y-x|) work?
- Why does one million test cases make per-test complexity especially important?
- Should you look for work proportional to the entire distance, or a mathematical/direct method requiring very little work per test?
- Without solving it, what are the constraints telling you about the intended algorithm?

#### Compare the three teacher problems

Complete:

| Teacher problem | Main maximum constraint | First complexity considered | Looks suitable? | Why? |
|---|---|---|---|---|
| #2 Robot Race | n ≤ 1000 | O(N²) | Yes | The input size is small enough that comparing pairs is reasonable. |
| #17 Special Prime | n ≤ 100000, a_i ≤ 10^12 | Too large for naive full-range checks | No | A simple scan to a_i or even to sqrt(a_i) per input is too expensive. |
| #21 Jump | T ≤ 1000000 | O(|y-x|) per test | No | One million tests require almost constant-time or near-constant-time behavior. |

Then answer in 2-4 sentences:

Why can O(N²) be acceptable in one HSG problem but completely impossible in another?

This connects Day26 directly to the HSG problems Eddie is currently receiving from his school teacher.

## SELF_CHECK.md

Eddie should answer these himself.

1. What does algorithmic complexity describe?
2. Does Big O normally tell us the exact number of seconds?
3. What does N normally represent?
4. What does O(1) mean?
5. Give one example of an O(1) operation.
6. What does O(N) mean?
7. Give one example of an O(N) algorithm.
8. If N doubles, approximately what happens to the work of an O(N) algorithm?
9. What does O(N²) mean?
10. What common code structure often produces O(N²)?
11. If N doubles, approximately what happens to N²?
12. Are two separate O(N) loops O(N²)? Why not?
13. What is the complexity of N + N?
14. What is the complexity of N × N?
15. What does O(log N) roughly mean?
16. What operation commonly creates logarithmic behavior?
17. Approximately how many times can one million be divided by 2 before reaching 1?
18. What is binary search's approximate complexity?
19. Why can binary search be dramatically faster than linear search?
20. What is O(N log N) commonly associated with?
21. Why should you read constraints before coding?
22. Is an O(N²) solution necessarily bad?
23. Why does maximum N matter?
24. Would you normally worry about O(N²) for N = 10?
25. Why is O(N²) worrying for N = 100,000?
26. Approximately what is 100,000²?
27. What is a subtask?
28. Why can a slower algorithm still be useful for a subtask?
29. If you cannot solve the full problem, should you automatically submit nothing?
30. If N = 100,000 and Q = 100,000 and each query scans all N elements, what is the approximate complexity?
31. Why is repeated work important to notice?
32. What does preprocessing mean in your own words?
33. Why might preprocessing make later queries faster?
34. Why isn't the fastest theoretical algorithm always the best algorithm to implement?
35. What four questions should you ask before implementing an HSG solution?
36. Compare teacher Problems Day2, Labs #2, 07 thuc hanh #17, and Practice Project - Robot Mission Control Simulator #21. Which one most clearly forces you to avoid a naïve algorithm, and why?
37. What complexity mistake do you think you are most likely to make?
38. What was the hardest idea to understand today?
39. What was the most interesting thing you learned today?
40. Questions 37-40 must be Eddie's own analysis rather than copied answers.

## Day26 grading rubric

| Requirement | Points |
|---|---:|
| Understands O(1) | 4 |
| Understands O(N) | 5 |
| Understands O(N²) | 6 |
| Understands O(log N) conceptually | 5 |
| Understands O(N log N) conceptually | 3 |
| Correctly distinguishes consecutive vs nested loops | 6 |
| Can estimate operation growth | 6 |
| Uses constraints before choosing algorithm | 8 |
| linearWork() experiment | 5 |
| quadraticWork() experiment | 5 |
| Challenge 1 correct O(N) | 6 |
| Challenge 2 correct O(N²) | 6 |
| Challenge 3 analysis | 5 |
| Challenge 4 analysis | 4 |
| HSG algorithm-choice exercise | 5 |
| Subtask reasoning | 5 |
| Analysis of teacher Problems #2, #17, and #21 | 5 |
| README actual observations | 5 |
| SELF_CHECK completed personally | 5 |
| Total | 100 |

Passing:

- 90-100: PASS
- 80-89: MINOR REWORK
- <80: REWORK

## Most important Day26 rule

> Before I code, I read the constraints. Before I choose an algorithm, I estimate its complexity.
>
> For HSG preparation, I would consider understanding that rule more valuable today than learning another C++ language feature.

## Experiment 1: exact calculations

- N = 10 => N² = 100
- N = 100 => N² = 10,000
- N = 1,000 => N² = 1,000,000
- N = 10,000 => N² = 100,000,000
- N = 100,000 => N² = 10,000,000,000

## Experiment 2: direct growth check

```cpp
long long linearWork(int n) {
    long long operations = 0;

    for (int i = 0; i < n; ++i) {
        ++operations;
    }

    return operations;
}
```

```cpp
long long quadraticWork(int n) {
    long long operations = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ++operations;
        }
    }

    return operations;
}
```

For the same N:

- `linearWork(n)` returns approximately N
- `quadraticWork(n)` returns approximately N²

The gap grows rapidly as N grows.

## Experiment 3: why two consecutive O(N) loops remain O(N)

```cpp
for (int i = 0; i < n; ++i) { /* work */ }
for (int i = 0; i < n; ++i) { /* work */ }
```

This is roughly N + N = 2N, and constants are ignored in Big O. Therefore the overall cost is still O(N).

## Experiment 4: why nested loops become O(N²)

```cpp
for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
        // work
    }
}
```

The inner loop runs N times for each of the N outer iterations, so total work is N × N = N².

## Experiment 5: 200000² and the trap

- 200000² = 40,000,000,000

A pair-counting algorithm with nested loops is O(N²), and for N = 200000 this means about 40 billion comparisons. That is not suitable for a contest problem with large limits.

## Experiment 6: how many times to divide by 2?

For N = 1,000,000:

- 1,000,000 → 500,000 → 250,000 → 125,000 → 62,500 → 31,250 → 15,625 → 7,812 → 3,906 → 1,953 → 976 → 488 → 244 → 122 → 61 → 30 → 15 → 7 → 3 → 1

This takes about 20 divisions.

That is the intuition behind O(log N): repeated halving is extremely fast compared with checking every value.

## Experiment 7: teacher-problem analysis

### Teacher Problem 2 — Robot Race

For n = 1000, comparing every pair of robots gives:

- pairs ≈ 1000 × 999 / 2 = 499,500

This is O(N²) and is reasonable for this limit. The useful information would be each robot's finish time or effective score after comparing against the others.

### Teacher Problem 17 — Special Prime

For each a_i ≤ 10^12, a naive check from 1 to a_i is impossible. Even checking up to sqrt(a_i) for every value can be around 10^6 operations per query, and for 100000 values that becomes roughly 10^11 operations in the worst case. The teacher's hint is telling us to look for a mathematical property that avoids scanning everything.

### Teacher Problem 21 — Jump

If every test takes O(|y-x|), then with T ≤ 1,000,000 and large distances, the work becomes enormous. The limit tells us the algorithm must use something near O(1) or a direct mathematical formula each time.

## Challenge 1: maximum in O(N)

Use one pass through the vector, keeping the current maximum. Each element is checked exactly once, so the cost is O(N). You cannot skip checking an element without risking missing the true maximum.

## Challenge 2: count equal pairs in O(N²)

This is a classic nested-loop solution. For each i, we compare with every j > i.

The total number of comparisons is roughly N(N-1)/2, which is O(N²).

## Challenge 3: trap analysis

My Day26 O(N²) solution is not suitable when N ≤ 200000 because:

- 200000² = 40,000,000,000
- this is far too many pair checks for the maximum input.

I need some way to avoid comparing every pair, such as counting occurrences with a faster structure or a mathematical shortcut.

## Challenge 4: estimate before coding

The loop

```cpp
for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
        // one comparison
    }
}
```

is O(N²), not O(N), because the inner loop does not always run N times. Its exact count is about N(N-1)/2, which still grows quadratically. The algorithm is correct because it compares every valid pair exactly once.

## Final reflection

O(N²) is acceptable in some HSG problems when constraints are small and the data size is modest. It becomes completely impossible when the maximum N is large enough that the number of comparisons explodes. The real lesson is not that O(N²) is always bad, but that every algorithm must be chosen based on the actual limits and the actual work at those limits.
