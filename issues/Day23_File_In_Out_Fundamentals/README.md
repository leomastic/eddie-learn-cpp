# C++ Lesson 23 — File I/O Fundamentals

## Goal
Teach basic text-file persistence: open, read, parse, validate, write, close.

## What Is File I/O?
File I/O means reading from and writing to files on persistent storage (disk), so program data can survive after the program exits.

## ofstream
`std::ofstream` opens a file for output. Using `<<` writes text to the file. By default it overwrites existing contents.

## ifstream
`std::ifstream` opens a file for input. Use `std::getline()` to read lines safely.

## Opening and Closing Files
Always check `file.is_open()` after opening. Call `file.close()` when done (streams close automatically on scope exit but explicit close clarifies intent).

## is_open()
Returns `true` if the file opened successfully, `false` otherwise.

## getline()
Reads a full line (including spaces) into a `std::string` until a newline.

## `>>` vs `getline()`
`>>` stops at whitespace (useful for single tokens). `getline()` preserves spaces for full lines or names.

## Overwrite Experiment
Opening an `std::ofstream` normally replaces the file contents. Use `std::ios::app` to append.

## Append Experiment
Opening with `std::ios::app` adds new data to the end without deleting existing content.

## Mission File Format
Each mission is saved as: `Name|Priority` (one mission per line). Priority is an integer 1–5.

## Parsing
Load each line, find the `|` delimiter, `substr` the name and priority text, then `std::stoi()` the priority and validate.

## Validation
Validate: name non-empty, priority between 1 and 5. Skip malformed lines or invalid priorities.

## Save / Restart / Load Experiment
On startup the program loads `missions.txt`. Use the menu to add, save, reload, and exit. Exiting will attempt to auto-save (the program warns if saving fails).

Example output after startup when no file exists:

```
Loaded 0 missions from missions.txt
===== Mission Logbook =====
...
```

Example after saving 3 missions and restarting:

```
Loaded 3 missions from missions.txt
```

## Malformed File Tests
Empty lines and lines without the delimiter are skipped with no crash.

## Project Structure
## Project Structure
- CMakeLists.txt
- main.cpp
- mission.h
- mission.cpp
- file_io.h
- file_io.cpp
- README.md
- SELF_CHECK.md

Runtime-generated files (created when you run the program):
- activity.log
- missions.txt

## Malformed File Tests
Empty lines and lines without the delimiter are skipped with no crash. Priority text is validated as numeric before conversion (so inputs like `Repair Rover|abc` or `Repair Rover|3abc` are skipped and will not crash the loader).
- Files can be manually edited and become malformed — loader skips bad lines.

## Most Interesting Observation
Files are untrusted input: even data your program produced must be validated before use.
