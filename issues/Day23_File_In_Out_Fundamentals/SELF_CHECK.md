# SELF_CHECK — File I/O Fundamentals

1. What does I/O stand for?
   - Input / Output.

2. What is the difference between data in RAM and data stored in a file?
   - RAM is temporary and cleared when the program/process ends; files on disk persist between runs.

3. Which header provides C++ file streams?
   - `<fstream>`.

4. What is `std::ofstream` used for?
   - Writing text to files (output file stream).

5. What is `std::ifstream` used for?
   - Reading text from files (input file stream).

6. What does `file.is_open()` tell you?
   - Whether the stream successfully opened the file.

7. Why should a program check whether a file opened successfully?
   - Opening can fail for many reasons (permissions, missing directory, disk issues); writing/reading without checking can cause data loss or crashes.

8. What does `file.close()` do?
   - Flushes and releases the file handle; indicates the program is done accessing the file.

9. What happens to an output file's existing content when opened normally with `std::ofstream`?
   - It is overwritten (replaced).

10. What does `std::ios::app` mean?
    - Open the file in append mode; writes go to the end without erasing existing data.

11. What is the difference between overwrite and append?
    - Overwrite replaces the whole file contents; append adds new data to the end.

12. What does `std::getline()` read?
    - A full line from a stream up to (but not including) the newline.

13. Why is `getline()` useful for mission names containing spaces?
    - Because it preserves spaces; `>>` would stop at the first space.

14. What would operator `>>` read from: `Repair Mars Rover`?
    - `Repair` (the first token up to whitespace).

15. What does this loop mean? `while (std::getline(file, line))`
    - Read one line at a time; continue while reading succeeds.

16. Why should you prefer that over: `while (!file.eof())`?
    - `eof()` isn't a reliable read condition; reading should control loop termination.

17. How do you load file lines into a vector?
    - `while (getline(file,line)) { vec.push_back(line); }`.

18. What is persistence?
    - Data that survives program termination by storing it on disk (files/databases).

19. What happens to a mission added in memory but never saved?
    - It is lost when the program exits.

20. What happens after it is saved?
    - It is written to disk and can be reloaded on the next run.

21. What is a delimiter?
    - A character that separates fields in a record (here `|`).

22. Which delimiter did today's Mission Logbook use?
    - `|` (pipe).

23. What does `string.find('|')` do?
    - Returns the index of the first `|` or `std::string::npos` if not found.

24. What does `std::string::npos` mean?
    - A sentinel value indicating "not found".

25. What does `substr()` do?
    - Extracts a substring from a string given a start index and optional length.

26. What does `std::stoi()` do?
    - Converts a numeric string to an `int`.

27. What is parsing?
    - Interpreting structured text to extract fields and convert them to program types.

28. Why should file data still be validated?
    - Files can be edited or corrupted; treat file data like user input and validate it.

29. What should happen to an empty line?
    - It should be skipped.

30. What should happen to a line without the required delimiter?
    - It should be skipped (malformed).

31. What should happen if a priority is outside 1–5?
    - The line should be skipped and not loaded.

32. Why are `Mission` and file-loading code in separate modules?
    - Separation of concerns: mission logic vs file I/O improves reuse and maintainability.

33. Why should `main.cpp` not contain all file-parsing logic?
    - `main.cpp` should orchestrate program flow; low-level parsing belongs in a dedicated module for clarity and reuse.

34. What does `saveMissions()` return?
    - A `bool` indicating success (`true`) or failure (`false`).

35. Why is returning a `bool` useful?
    - Callers can report success/failure and take action (retry, warn user).

36. What ambiguity exists if `loadMissions()` returns an empty vector?
    - Empty vector could mean the file didn't open, or it opened and contained zero valid lines.

37. What is the difference between memory state and saved state?
    - Memory state is the runtime vector in RAM; saved state is the file on disk.

38. Describe the complete process: Mission object → file → program restart → Mission object
    - Create/modify Mission objects in memory → `saveMissions()` writes lines to file → program exits → restart → `loadMissions()` reads file lines, parses and validates them, and reconstructs Mission objects in memory.

39. What was the hardest bug you encountered?
    - (Answer in your own words when you implement and run) Common issue: forgetting to consume the newline after `>>`, making `getline()` read an empty string.

40. What was the most interesting thing you learned about file I/O?
    - (Answer in your own words) Files are persistent but untrusted; always validate data even if your program wrote it.
