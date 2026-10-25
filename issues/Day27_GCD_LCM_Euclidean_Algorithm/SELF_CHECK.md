# Day27 SELF_CHECK

## Answers

1. GCD is the greatest common divisor: the largest positive integer that divides both numbers.
2. The Vietnamese abbreviation for GCD is `ƯCLN`.
3. LCM is the least common multiple: the smallest positive integer divisible by both numbers.
4. The Vietnamese abbreviation for LCM is `BCNN`.
5. `b` divides `a` when dividing `a` by `b` leaves remainder zero.
6. In C++, test it with `a % b == 0` (when `b` is nonzero).
7. Common divisors are integers that divide both numbers.
8. `gcd(18, 24) = 6`.
9. Two integers are coprime when their GCD is 1.
10. No. Coprime numbers do not both have to be prime.
11. `8` and `15` are both non-prime, but `gcd(8, 15) = 1`.
12. Scanning every integer up to `min(a, b)` can require an impractical number of checks when the values are large.
13. The Day26 habit is to read the constraints and estimate the work before choosing an algorithm.
14. The Euclidean identity is `gcd(a, b) = gcd(b, a % b)`.
15. When `b` becomes zero, the current `a` is the GCD.
16. For `gcd(48, 18)`, the first step calculates `48 % 18`.
17. `48 % 18 = 12`.
18. The pair `(48, 18)` is replaced by `(18, 12)`.
19. The common divisors are unchanged because a divisor of both `a` and `b` also divides `a - q*b = a % b`, and a divisor of `b` and `a % b` also divides `q*b + (a % b) = a`.
20. Euclid takes approximately `O(log(min(a, b)))` steps.
21. Euclid repeatedly replaces the inputs with a smaller pair of remainders, rather than checking each candidate up to `10^12`.
22. `gcd(0, 25) = 25`.
23. `gcd(17, 0) = 17`.
24. In this implementation, `gcd(0, 0) = 0`.
25. For positive integers, `gcd(a, b) * lcm(a, b) = a * b`.
26. Divide first in `a / gcd(a, b) * b` to reduce the intermediate product and lower the risk of overflow.
27. `lcm(6, 8) = 24`.
28. Divide both the numerator and denominator by their GCD to simplify a fraction.
29. `42 / 56 = 3 / 4`, because `gcd(42, 56) = 14`.
30. Process the vector once, repeatedly calculating `gcdEuclid(currentGcd, nextValue)`.
31. `currentGcd` can start at 0 because `gcd(0, x) = x` for nonnegative `x`.
32. If `gcd(a, b) == 1`, then `a` and `b` are coprime.
33. The largest equal grouping problem suggests GCD.
34. The next simultaneous repetition problem suggests LCM.
35. GCD can be a hidden tool when a problem asks for the largest equal grouping or a reduced fraction without naming GCD.
36. Constraints determine whether an otherwise correct algorithm will finish within the available time and resources.
37. I need to be careful to save `a % b` before assigning `a = b`; otherwise I can lose the old values needed for the next state.
38. Teacher Problem #17 (Special Prime) helped me practice checking constraints before attempting divisor enumeration. Its recorded limits are `n <= 100,000` and `a_i <= 10^12`; it is a number-theory connection, not a direct GCD problem.
39. The hardest idea for me was understanding why replacing `(a, b)` with `(b, a % b)` preserves exactly the same common divisors.
40. The most interesting thing I learned was that a remainder can replace a huge divisor search with only a small number of steps.

Questions 37--40 are personal reflections and should be reviewed and edited to match my own experience.
