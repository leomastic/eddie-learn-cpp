# Day28 SELF_CHECK

## Answers

1. A prime counted once contributes one regardless of how many times it appears in the factorization. Counting with multiplicity contributes its exponent.
2. The prime factor signature of 1 is 0 because 1 has no prime divisors.
3. `12 = 2^2 * 3`. Its distinct prime factors are 2 and 3, so its signature is 2; counting multiplicity gives `2 + 1 = 3` prime factors. (The exercise prompt's claim of four prime factors with multiplicity is incorrect.)
4. A number is square-free if no prime has exponent greater than 1 in its prime factorization; equivalently, no prime square greater than 1 divides it.
5. One has no prime factors, so no prime square divides it. It is square-free by convention as well.
6. No. `49 = 7^2`, so it is divisible by the square of the prime 7.
7. Two positive integers are coprime when their greatest common divisor is 1.
8. The Euclidean algorithm finds each pair's GCD in logarithmic time rather than scanning possible divisors. Applying it to every adjacent pair takes `O(N log M)` overall.
9. A divisor-count sieve loops through each possible divisor and increments the counts of its multiples.
10. If divisor counts tie, choose the smallest integer in the interval.
11. There can be `O(NQ)` total elements scanned across all queries, which is too much at `N,Q = 200,000`.
12. A prefix-count array stores the cumulative number of qualifying items through each position; here it stores non-prime counts.
13. For 1-indexed inclusive `[L,R]`, subtract `prefix[L-1]` from `prefix[R]`.
14. One is not prime because a prime must have exactly two positive divisors, while 1 has only one.
15. `n!` grows too quickly to fit in ordinary integer types, even for relatively modest `n`, and this problem allows `n` as large as one billion.
16. Factor `b` into primes and record each prime's exponent; each exponent gives the required multiplicity per copy of `b`.
17. The factorial may contain different numbers of copies of each prime required by `b`, so the scarcest required prime determines the maximum number of copies.
18. Problem 5 benefits especially from preprocessing: a prime sieve plus one prefix-count array lets each of up to 200,000 range queries be answered in constant time.
19. **Eddie's own reflection — complete personally:** Which problem was hardest for you, and what exactly blocked you?
20. **Eddie's own reflection — complete personally:** What is the most useful new idea you learned today?