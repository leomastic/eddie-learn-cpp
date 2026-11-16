# Self-check

Questions that depend on personal recollection or exam details are marked for
the student to answer. The other answers are based on the source files and
problem statements available here.

1. **Which problem did you attempt first? Why?**  
   i didnt record.

2. **How long did you spend reading the full exam?**  
   i didnt record

3. **Which problem took the most time?**  
   i didnt record

4. **Did you complete all five problems within 150 minutes?**  
   no

5. **What is the largest possible digit-weighted checksum in Problem 1's
   constraints?**  
   With a maximum lock code of 10^18, the largest checksum is 1539, attained
   by 999,999,999,999,999,999: each of its 18 digits is 9, so the checksum is
   `9 × (1 + 2 + ... + 18) = 9 × 171 = 1539`. The value 10^18 itself has
   checksum 1.

6. **What happens if the lock code contains zero digits internally?**  
   A zero contributes zero to the checksum, but still occupies its digit
   position. Digits to its right keep their correct position weights.

7. **Why must a substring be contiguous in Problem 2?**  
   A substring is a consecutive segment of the original string; skipping
   characters would make it a subsequence, not a substring.

8. **How is a tie for maximum substring length resolved?**  
   The sliding-window solution updates only when a strictly longer window is
   found. As right endpoints are processed in increasing order, this keeps
   the earliest starting position among equal maximum lengths.

9. **What should Problem 2 output when `K=0`?**  
   The current code outputs `0 0`.

10. **What does `omega(1)` equal?**  
    `0`, because 1 has no prime divisors.

11. **Why can a per-query factorization potentially be slow for Problem 3?**  
    Up to 100,000 queries may repeat factorization work over overlapping
    ranges. Precomputing the distinct-prime-factor counts once and using
    prefix sums avoids repeating that work for every query.

12. **What does the word “distinct” change in prime-factor counting?**  
    A prime is counted once even if it occurs with an exponent greater than
    one; for example, 12 has two distinct prime divisors, 2 and 3.

13. **Why can Problem 4's array contain negative numbers?**  
    A negative value represents energy lost during that hour.

14. **Why does the total in Problem 4 need 64-bit storage?**  
    Up to 200,000 values can each have magnitude 10^9, so a range sum can
    reach magnitude 2 × 10^14, beyond a 32-bit signed integer.

15. **What is the maximum possible number of pairs in Problem 5?**  
    `N(N - 1)/2`. For `N = 200,000`, this is 19,999,900,000.

16. **Why are equal IDs at different positions counted separately?**  
    The pair is defined by distinct positions `i < j`, not by distinct ID
    values. Two equal IDs at different positions form a valid pair when their
    sum is divisible by `M`.

17. **How does the case `M=1` affect Problem 5?**  
    Every integer sum is divisible by 1, so all `N(N - 1)/2` position pairs
    are valid.

18. **Which problem was easiest to test with a brute-force reference?**  
    Problem 5: for a small array, check every index pair `i < j` and directly
    test whether `(Ai + Aj) % M == 0`.

19. **Describe a real mistake or uncertainty you encountered, and how you
    i didnt record

20. **If you took this exam again, how would you allocate the 150 minutes
    i didnt record
