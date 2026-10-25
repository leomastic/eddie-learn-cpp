# Day 25: Persistent CRUD and Data Integrity

This project extends the Day 24 persistence exercise with Create, Read, Update, and Delete operations. The key idea is that a vector index is only a storage position, while an ID identifies the record itself.

## Core design

- `MaintenanceRecord` stores an integer `id_` plus the component, date, severity, and notes.
- `MaintenanceLog` owns the vector of records and the `nextId_` counter.
- `nextId_` is never reset to 1 during a normal load; it is advanced past every loaded ID.
- The file format is:

  `id|component|date|severity|notes`

- Each saved record uses the ID as a stable identity even after vector reordering or deletion.

## CRUD flow

- Create: add a new record, assign an ID, save the file.
- Read: list records with their IDs.
- Update: find a record by ID, validate new values first, then modify the record.
- Delete: locate the record by ID, shift later records left, then pop the last item.

## Data integrity rules

- Update must validate all values before writing to the object.
- Unknown IDs must fail without changing the log.
- Malformed persisted records are skipped safely.
- Duplicate persisted IDs are rejected so one record cannot overwrite another.
- Deleting record 2 does not rename record 3 into ID 2.

## Experiment results

### A. Create

- I created three records.
- Observed IDs: 1, 2, 3.
- Save + restart kept the IDs unchanged.

### B. Update

- Updated ID 2 from severity 2 to severity 4.
- After reload, the updated severity persisted as 4.

### C. Delete

- Deleted ID 2.
- Remaining IDs were 1 and 3.
- ID 3 did not become ID 2.

### D. Create after deletion

- Added a new record after deleting ID 2.
- The new record received ID 4.

### E. Create after restart

- Loaded records with IDs 2, 8, and 5.
- The next new record became ID 9.

### F. Unknown ID

- Update ID 999 and delete ID 999 both failed safely and left the log unchanged.

### G. Invalid update

- Updating a valid record with severity 9 failed.
- The original record remained unchanged after listing it again.

### H. Malformed persisted ID

- `abc|Motor|2026-09-18|3|Test` was skipped.
- `999999999999999999999999|Motor|2026-09-18|3|Test` was skipped.
- The program did not crash.

### I. Duplicate persisted IDs

- File content:

  `3|Motor|2026-10-01|2|First`
  `3|Servo|2026-10-02|4|Duplicate`

- Result: the first record with ID 3 is loaded; the duplicate ID 3 is skipped.
- The program does not crash, and data integrity is preserved.

## Notes

- The program deliberately avoids `std::find_if`, iterators, STL algorithms, and exceptions in the learning exercise.
- The important conceptual rule is: an index tells you where the record is now; an ID tells you which record it is.
