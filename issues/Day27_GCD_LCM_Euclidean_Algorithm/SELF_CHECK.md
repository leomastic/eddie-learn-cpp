# Day27 SELF_CHECK

## My answers

1. GCD means the greatest common divisor: the largest positive integer that divides both numbers.
2. The Vietnamese abbreviation is `ƯCLN`.
3. LCM means the least common multiple: the smallest positive number divisible by both values.
4. The Vietnamese abbreviation is `BCNN`.
5. `b divides a` means `a % b == 0`.
6. In C++, I test divisibility with `if (a % b == 0)`.
7. Common divisors are the numbers that divide both values at the same time.
8. `gcd(18, 24) = 6`.
9. Coprime means the GCD is 1.
10. No. Two coprime numbers do not both have to be prime.
11. Example: `8` and `15` are not prime themselves, but `gcd(8, 15) = 1`.
12. Scanning every number up to `min(a, b)` can be too slow because it may require millions, billions, or even trillions of checks when the values are huge.
13. The Day26 habit is to read constraints first and reject brute-force solutions that are too expensive.
14. The Euclidean identity is `gcd(a, b) = gcd(b, a % b)`.
15. When `b` becomes `0`, the current `a` is the answer.
16. For `gcd(48, 18)`, the first step is `48 % 18 = 12`.
17. The pair `(48, 18)` is replaced by `(18, 12)`.
18. Replacing `(a, b)` with `(b, a % b)` preserves the GCD because the common divisors of the old pair are exactly the common divisors of the new pair.
19. Euclid is roughly `O(log(min(a, b)))`.
20. Euclid is dramatically better than scanning to `10^12` because it reduces the problem by remainders, not by trying every number.
21. `gcd(0, 25)` is `25`.
22. `gcd(17, 0)` is `17`.
23. `gcd(0, 0)` is `0` in this implementation.
24. For positive integers, `gcd(a, b) * lcm(a, b) = a * b`.
25. `a / gcd(a, b) * b` is preferred because multiplying before dividing can overflow sooner than necessary.
26. `lcm(6, 8) = 24`.
27. GCD simplifies a fraction by dividing numerator and denominator by their shared GCD.
28. `42 / 56 = 3 / 4` because `gcd(42, 56) = 14`.
29. To calculate the GCD of many numbers, iterate through the vector and keep reducing the running answer with `gcdEuclid(currentGcd, value)`.
30. `currentGcd` can start at `0` because `gcd(0, x) = x`.
31. If `gcd(a, b) == 1`, then `a` and `b` are coprime.
32. Largest equal grouping suggests GCD.
33. Next simultaneous repetition suggests LCM.
34. GCD is useful even when a problem does not say "find the GCD" because many grouping and reduction tasks are hidden GCD problems.
35. Constraints matter because a mathematically correct idea must still fit the problem limits.
36. The most common mistake is updating the variables incorrectly, for example forgetting the exact step `remainder = a % b; a = b; b = remainder;`.
37. Day27 helped me understand teacher problems about reducing fractions and grouping objects because the hidden tool was the GCD pattern.
38. The hardest idea for me was understanding why `gcd(a, b) = gcd(b, a % b)` preserves the same common divisors.
39. The most interesting thing I learned was that mathematics can shrink a huge problem into a tiny remainder-based computation.
40. I still need to keep reading constraints before choosing an algorithm, because the right math matters more than just writing code quickly.

## Completion note

I checked the key Day27 concepts: divisibility, GCD, LCM, coprime numbers, Euclid's algorithm, vector GCD reduction, and fraction simplification. The project builds successfully and the sample challenge outputs match the expected reasoning.
