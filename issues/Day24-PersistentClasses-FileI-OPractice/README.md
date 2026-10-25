# Day24 --- Persistent Classes & File I/O Practice

## Goal
Today the learning goal was to move from raw text handling toward a simple object model where each maintenance record is represented by a class, and a second class manages a collection of records.

## MaintenanceRecord
`MaintenanceRecord` keeps related data together in one object:
- component
- date
- severity
- notes

This prevents the common "parallel vectors" problem where unrelated data can drift out of sync.

## MaintenanceLog
`MaintenanceLog` owns a `std::vector<MaintenanceRecord>` and exposes a controlled interface for adding records, counting them, and querying them.

## Why Use Two Classes?
A single record has a meaning of its own, while the whole log is a collection of many records. Separating them keeps responsibilities clear.

## Class Composition
This is class composition:
`
MaintenanceLog
  -> vector<MaintenanceRecord>
`
The log owns the records, and each record keeps its own fields together.

## File Format
The file format is:
`component|date|severity|notes`

Example:
```
Right Motor|2026-09-13|4|Motor rotates slower than left
Servo|2026-09-14|1|Movement looks normal
Ultrasonic|2026-09-15|3|Some readings return -1
```

## Serialization
Serialization writes each `MaintenanceRecord` to one text line in the agreed format.

## Parsing
The loader uses `find('|')` three times to locate the three separators and then extracts each field with `substr()`.

## Validation
The program validates both the numeric text and the final record fields before creating an object. This matters because some lines are parseable but still invalid.

## Safe stoi Preparation
The loader checks `isPositiveIntegerText()` before calling `std::stoi()`. This prevents values like `abc` and `4abc` from crashing or corrupting the program.

## Save Process
When saving, the code opens the file with `std::ofstream`, writes every record as a serialised line, closes the file, and returns `true` only if the file opened.

## Load Process
The loader opens the file with `std::ifstream`, reads each line, skips malformed entries, and builds a new `MaintenanceLog` before replacing the in-memory version only after the file opened successfully.

## Why load() Modifies MaintenanceLog
`loadMaintenanceLog()` accepts `MaintenanceLog&` because it needs to change the collection. `saveMaintenanceLog()` takes `const MaintenanceLog&` because it only reads the log.

## Why save() Uses const
The writer reads the log but does not alter it, so using a const reference communicates the correct contract and prevents accidental mutation.

## Persistence Experiment
Observed result after recording several maintenance entries and saving, then restarting the program:
```
Loaded 3 records from maintenance.txt
```
The program correctly restored the saved records.

## Spaces Experiment
I tested a component with spaces:
`Right Motor Assembly`
I also used notes with spaces:
`Motor becomes slower after several minutes`
The save and reload cycle preserved the text exactly, including the spaces.

## Malformed Severity Experiment
I tested a deliberately malformed line:
`Motor|2026-09-13|abc|Test`
Result: skipped, no crash.

## Partial Number Experiment
I tested:
`Motor|2026-09-13|4abc|Test`
Result: skipped, no crash.
This confirms the `abc`/`4abc` rejection pattern is effectively preventing unsafe integer conversion.

## Invalid Range Experiment
I tested:
`Motor|2026-09-13|99|Test`
Result: skipped, no crash.
The record is syntactically valid but invalid because the severity is outside the accepted range.

## Missing Field Experiment
I tested:
- `Motor|2026-09-13|4`
- `Motor`
Result: both skipped.

## Empty Field Experiment
I tested:
- `|2026-09-13|4|Test`
- `Motor||4|Test`
Result: both skipped.

## Delimiter Experiment
I tested this note:
`Motor works | but sometimes stops`
The line saved as:
`Motor|2026-09-13|3|Motor works | but sometimes stops`
The parser still handled it correctly because everything after the third delimiter becomes part of the notes field. However, if the component name itself contains `|`, then the file format becomes ambiguous.

## Save Failure Experiment
I attempted saving to a nonexistent directory path.
Result: `Failed to save maintenance log.`
The program correctly handled the failure without crashing.

## Reload Failure Experiment
I attempted to reload a missing file after the program already held in-memory records.
Result: existing records remained available.
This verifies that the log is only cleared after the file has opened successfully.

## Problems I Encountered
The first difficulty was designing the file parser carefully so it handled the three delimiters and the note field without breaking when notes included spaces. Another important issue was making sure malformed values were skipped without crashing the whole program.

## Hardest Bug
The hardest bug was the unsafe integer conversion issue. A severity such as `abc` or `4abc` must not be sent to `std::stoi()` without validating first.

## Most Interesting Thing I Learned
The most interesting lesson was that file data must always be treated as untrusted input and validated before it becomes a valid object. The class model makes this much easier to reason about because each record owns its own state.