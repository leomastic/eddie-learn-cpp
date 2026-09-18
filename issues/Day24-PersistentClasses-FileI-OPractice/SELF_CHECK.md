# Self-check for Day24

1. Persistence means data survives after the program exits.
2. Serialization is the act of converting an object into a file-friendly format.
3. Parsing is reading the serialized text and breaking it into fields.
4. Validation is checking that the parsed values meet the required rules.
5. Parsing and validation are different because a line can be split correctly but still contain invalid data.
6. File contents should be treated as untrusted because they may be malformed, edited by hand, or incomplete.
7. `std::ofstream` writes output to a file.
8. `std::ifstream` reads input from a file.
9. `is_open()` should be checked to confirm that the file was actually opened successfully.
10. `std::getline()` reads a full line, including spaces.
11. `getline()` is useful because notes may contain spaces.
12. A delimiter is a character used to separate fields, such as `|`.
13. Four fields require three delimiters.
14. `find()` returns `std::string::npos` when the delimiter is not found.
15. `std::string::npos` means "not found".
16. `substr()` extracts a substring from a string.
17. `"abc"` should be rejected before `stoi()` because it is not a valid integer string.
18. `"4abc"` should also be rejected because partial numeric text is not safe to convert.
19. Severity `99` is invalid even though `"99"` is a valid integer text because the range must be 1 through 5.
20. `MaintenanceRecord` represents one maintenance record.
21. `MaintenanceLog` represents the collection of all maintenance records.
22. `MaintenanceLog` owns a `vector<MaintenanceRecord>` to keep all records together and encapsulate the storage.
23. Class composition means one class contains another class as part of its state.
24. `records_` is private to protect the internal data structure and keep the interface controlled.
25. We use `addRecord()` instead of exposing the vector so `main()` does not need to know storage details.
26. `getRecordCount()` is `const` because it does not modify the object.
27. `saveMaintenanceLog()` takes a `const MaintenanceLog&` because it only reads the log.
28. `loadMaintenanceLog()` cannot take `const MaintenanceLog&` because it needs to modify the collection.
29. Saved state and memory state are different because the file is persistent storage while memory is temporary while the program runs.
30. A malformed line should be skipped without crashing the program.
31. If the load file cannot be opened, the program should leave the current in-memory log intact.
32. Existing memory data should not be erased before verifying that the file opened successfully.
33. `findHighestSeverityIndex()` returns `-1` for an empty log because there is no valid index.
34. `-1` is used for "not found" because it is a convenient invalid index value.
35. No sorting is required because we can scan the vector once and track the highest value.
36. If notes contain `|` after the third delimiter, the parser still treats the rest as part of the notes field.
37. If the component name contains `|`, the format becomes ambiguous and cannot be parsed reliably.
38. The full lifecycle is: `MaintenanceRecord` -> saved to file -> restart -> load -> create `MaintenanceRecord` objects again.
39. The hardest bug I encountered was preventing unsafe integer conversions from malformed severity text.
40. The most interesting thing I learned was that file data is untrusted and must be parsed and validated before being trusted as an object.