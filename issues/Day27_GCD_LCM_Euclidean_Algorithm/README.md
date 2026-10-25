# Day27 Results --- GCD, LCM & Euclidean Algorithm

## Challenge 1 --- GCD of two numbers

Input:
```text
1
252 105
```

Output:
```text
21
```

This uses `gcdEuclid()`, which applies the identity `gcd(a,b) = gcd(b, a % b)`. The algorithm keeps replacing `(a, b)` with `(b, a % b)` until `b` becomes zero. The last non-zero value is the answer.

## Challenge 2 --- Are they coprime?

Examples:
```text
2
8 15
```

Output:
```text
YES
```

```text
2
12 18
```

Output:
```text
NO
```

Two numbers are coprime when their greatest common divisor is 1.

## Challenge 3 --- Simplify a fraction

Input:
```text
3
42 56
```

Output:
```text
3 4
```

The fraction is reduced by dividing both numerator and denominator by their GCD.

Additional checks:
```text
3
100 25
```

Output:
```text
4 1
```

## Challenge 4 --- GCD of N numbers

Input:
```text
4
5
24 36 60 48 72
```

Output:
```text
12
```

The vector version keeps an accumulated gcd and updates it as each new value is processed:
`currentGcd = gcdEuclid(currentGcd, value)`.

## Challenge 5 --- LCM

Input:
```text
5
12 18
```

Output:
```text
36
```

This uses the divide-first formula:
`lcm(a, b) = a / gcd(a, b) * b`

This avoids an unnecessary multiplication overflow risk when the numbers are large.

## Experiment 1 --- Slow vs Euclid

I ran the slow scan and the Euclidean implementation on several values.

Actual output:
```text
a=48 b=18 slow=6 Euclid=6 slowChecks=18 EuclidSteps=3
a=1000 b=625 slow=125 Euclid=125 slowChecks=625 EuclidSteps=4
a=100000 b=99999 slow=1 Euclid=1 slowChecks=99999 EuclidSteps=2
a=1000000 b=999999 slow=1 Euclid=1 slowChecks=999999 EuclidSteps=2
```

The Euclid version is much more efficient because it works with remainders instead of checking every possible divisor from 1 to min(a, b).

## Experiment 2 --- Euclidean traces

Predicted and verified:

- `gcd(48,18)`
  - `48 % 18 = 12`
  - replace `(48,18)` with `(18,12)`
  - `18 % 12 = 6`
  - replace `(18,12)` with `(12,6)`
  - `12 % 6 = 0`
  - answer `6`

- `gcd(252,105)`
  - `252 % 105 = 42`
  - `105 % 42 = 21`
  - `42 % 21 = 0`
  - answer `21`

This matches the direct calculation of the code and confirms the Euclidean identity.

## Experiment 3 --- Coprime cases

Examples checked:
- `8 15` -> gcd is `1` -> coprime
- `14 21` -> gcd is `7` -> not coprime
- `17 19` -> gcd is `1` -> coprime
- `35 64` -> gcd is `1` -> coprime
- `100 25` -> gcd is `25` -> not coprime

This reinforces that coprime does not mean both numbers are prime themselves.

## Experiment 4 --- GCD of many values

Starting from `currentGcd = 0`:
- after `24`: `currentGcd = 24`
- after `36`: `currentGcd = 12`
- after `60`: `currentGcd = 12`
- after `48`: `currentGcd = 12`
- after `72`: `currentGcd = 12`

The final answer is `12`, which is the GCD of all values.

## Experiment 5 --- Day26 complexity connection

For `a = 10^12` and `b = 999999999999`, a naive divisor scan would have to try around `10^12` candidates in the worst case because it checks every value up to min(a, b).

That is unacceptable for contest constraints. Euclid shrinks the pair quickly using remainders, so it avoids checking a huge fraction of the search space.

This is exactly the Day26 lesson: do not use a brute-force algorithm when the constraints and mathematical structure point to a smarter approach.

## Experiment 6 --- Teacher-problem connection

This day helped me understand problems where the key idea is not scanning divisors, but exploiting number structure:

- Largest equal grouping -> GCD
- Next simultaneous event -> LCM
- Fraction reduction -> GCD
- Many-number GCD -> repeated Euclid accumulation

## Complexity

### `gcdEuclid(a, b)`
- Time: `O(log(min(a, b)))`
- Extra space: `O(1)`

### `lcmUsingGcd(a, b)`
- Time: `O(log(min(a, b)))` for the gcd step, plus constant-time arithmetic
- Extra space: `O(1)`

### `gcdOfVector(numbers)`
- Time: `O(N log M)` in a simple upper-bound form, where `N` is the number of values and `M` is the largest value size.
- Extra space: `O(1)` aside from the input vector itself.

## Final observations

The biggest idea in Day27 is that an algorithm does not have to enumerate every candidate when the mathematical structure gives us a much smaller equivalent problem. Euclid's algorithm turns large searches into a few remainder steps, and that is why it is the standard tool for GCD-based problems.
