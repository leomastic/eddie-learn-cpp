# Day28 — HSG Algorithm Challenge: New Number Theory Problems

All six solutions are separate C++17 programs, built as `problem1` through `problem6`. Each reads only its own problem's input format from standard input.

## Problem 1 — Prime Factor Signature

**Maximum constraints:** `N = 200,000`, `a[i] = 1,000,000`.

**Straightforward approach:** Trial-divide every input independently, trying candidate divisors up to its square root and removing repeated copies when a factor is found. This takes `O(N sqrt(V))` in the worst case, about 200 million candidate checks at the maximum constraints, so it is too slow to rely on.

**Efficient approach:** Read the values and find their maximum. Build a smallest-prime-factor table up to that maximum with a sieve. Factor each value through the table, counting each prime and dividing out all of that prime's copies before continuing.

**Correctness:** Every value greater than 1 has a smallest prime factor in the table. Dividing out all copies of that factor visits each distinct prime divisor exactly once. The value 1 skips the loop and gets signature 0.

**Complexity:** `O(V log log V + N log V)` time and `O(V + N)` auxiliary space, where `V = max(a[i])`.

**Provided sample output:**
```text
0 1 2 2 1 4
```

**Additional tests (input -> output):**

1. `N=1; values: 1` -> `0`
2. `N=5; values: 2 4 8 16 32` -> `1 1 1 1 1`
3. `N=4; values: 30 210 1000000 999983` -> `3 4 2 1`

## Problem 2 — Square-Free Detective

**Maximum constraints:** `N = 200,000`, `a[i] = 1,000,000`.

**Straightforward approach:** Check candidate divisors up to the square root of each value and determine whether any prime factor repeats. This takes `O(N sqrt(V))` in the worst case, about 200 million candidate checks, so it is too slow to rely on.

**Efficient approach:** Build a smallest-prime-factor table up to the largest input. Factor each number and reject it if any prime occurs twice consecutively in its factorization.

**Correctness:** A number is divisible by a prime square exactly when its prime factorization contains that prime with exponent at least 2. The repeated-factor check detects exactly this condition. The number 1 has no factors to reject it, so it is counted as square-free.

**Complexity:** `O(V log log V + N log V)` time and `O(V + N)` auxiliary space.

**Provided sample output:**
```text
5
```

**Additional tests (input -> output):**

1. `N=1; values: 1` -> `1`
2. `N=5; values: 4 8 9 25 49` -> `0`
3. `N=6; values: 2 3 6 10 30 999983` -> `6`

## Problem 3 — Coprime Neighbors

**Maximum constraints:** `N = 200,000`, `a[i] = 1,000,000,000`.

**Straightforward approach:** For each adjacent pair, test every candidate divisor up to the smaller value. In the worst case this is `O(N * M)` and does not fit.

**Efficient approach:** Visit the `N-1` adjacent pairs and apply the Euclidean algorithm (`std::gcd`) to each pair.

**Correctness:** The Euclidean algorithm returns the greatest common divisor of each pair. A pair is coprime precisely when this result is 1. If `N=1`, there are no adjacent pairs, so the count is 0.

**Complexity:** `O(N log M)` time and `O(N)` auxiliary space for the input array, where `M = max(a[i])`.

**Provided sample output:**
```text
4
```

**Additional tests (input -> output):**

1. `N=1; values: 1` -> `0`
2. `N=4; values: 1 1 2 4` -> `2`
3. `N=4; values: 1000000000 999999999 1000000000 999999999` -> `3`

## Problem 4 — Divisor Champion

**Maximum constraints:** `1 <= L <= R = 1,000,000`.

**Straightforward approach:** Count divisors independently for every number in `[L,R]` by checking all candidates up to that number. This can take `O((R-L+1)R)` time and does not meet the target.

**Efficient approach:** Initialize a divisor-count array through `R`. For every `d` from 1 to `R`, increment the count of each multiple of `d`. Scan `[L,R]` from smallest to largest and replace the champion only when a strictly larger count is found.

**Correctness:** Each positive divisor `d` increments exactly the numbers divisible by `d`, so each array entry becomes its exact divisor count. The ascending scan and strict-greater update keep the earliest number whenever counts tie.

**Complexity:** `O(R log R + R-L+1)` time and `O(R)` auxiliary space.

**Provided sample output:**
```text
12 6
```

**Additional tests (input -> output):**

1. `1 1` -> `1 1`
2. `2 3` -> `2 2`
3. `14 16` -> `16 5`

## Problem 5 — Prime-Free Segments

**Maximum constraints:** `N = Q = 200,000`, `a[i] = 1,000,000`.

**Straightforward approach:** Test every array value for primality by trial division, then scan every queried segment. This takes `O(N sqrt(V) + NQ)` in the worst case; the `NQ` term can reach 40 billion checks, so it does not fit.

**Efficient approach:** Sieve primality once through the maximum array value. Build `nonPrimePrefix[i]`, the number of non-prime values in the first `i` positions. Answer each inclusive query as `nonPrimePrefix[R] - nonPrimePrefix[L-1]`.

**Correctness:** The sieve identifies primes, with both 0 and 1 marked non-prime (only positive array values occur here). The prefix entry stores the cumulative non-prime count through that position, so subtracting the count before `L` from the count through `R` leaves exactly the count in `[L,R]`.

**Complexity:** `O(V log log V + N + Q)` time and `O(V + N)` auxiliary space, where `V = max(a[i])`.

**Provided sample output:**
```text
4
3
2
1
```

**Additional tests (input -> output):**

1. Input:
   ```text
   1 1
   1
   1 1
   ```
   Output: `1`
2. Input:
   ```text
   5 3
   2 3 5 7 11
   1 5
   2 4
   3 3
   ```
   Output:
   ```text
   0
   0
   0
   ```
3. Input:
   ```text
   6 3
   1 4 9 2 17 1000000
   1 6
   2 5
   4 6
   ```
   Output:
   ```text
   4
   2
   1
   ```

## Problem 6 — Factorial Divisibility Challenge

**Maximum constraints:** `n = 1,000,000,000`, `2 <= b = 1,000,000`.

**Straightforward approach:** Construct `n!` and repeatedly divide by `b`. This does not fit: even storing `n!` needs `Theta(n log n)` bits, and constructing it requires large-integer arithmetic; at `n = 1,000,000,000` neither time nor storage is practical.

**Efficient approach:** Factorize `b` as `product(p^e)`. For each prime `p`, calculate its exponent in `n!` with Legendre's sum `floor(n/p) + floor(n/p^2) + ...`. The number of copies of `b` available is the minimum of `floor(v_p(n!)/e)` across its prime factors.

**Correctness:** Each copy of `b` requires `e` copies of every prime `p` in its factorization. Thus each prime independently limits the number of copies to `floor(v_p(n!)/e)`. The minimum satisfies every prime requirement and is therefore the greatest valid `k`. Prime factorization and exponent counting also cover `n=1` and prime `b`.

**Complexity:** `O(sqrt(b) + omega(b) log n)` time and `O(1)` auxiliary space, where `omega(b)` is the number of distinct prime factors of `b`.

**Provided sample output:**
```text
4
```

**Additional tests (input -> output):**

1. `1 2` -> `0`
2. `5 2` -> `3`
3. `10 16` -> `2`
4. `1000000000 999983` -> `1000`

## Hardest problem

Problem 6 is the most involved algorithmically: it combines factorization of the base, Legendre's prime-exponent count, and taking the minimum across independent prime constraints. Its large `n` also rules out direct factorial construction.

## Build

From this directory, configure and build with CMake. The six independent executable targets are `problem1`, `problem2`, `problem3`, `problem4`, `problem5`, and `problem6`.