# Day 25 Self Check

1. CRUD stands for Create, Read, Update, and Delete.
2. The menu operation that represents Create is option 2: Add record.
3. The operation that represents Read is option 1: List records.
4. The operation that represents Update is option 3: Update record.
5. The operation that represents Delete is option 4: Delete record.
6. Each record needs an ID so it can be found reliably even after other records are added, moved, or deleted.
7. A vector index is a current storage position. A record ID is a stable identity for the record itself.
8. Yes, a vector index can change after deletion because the remaining records shift left.
9. No, a record ID should not change when another record is deleted.
10. `MaintenanceRecord` does not provide `setId()` because the ID is the record's identity and should stay fixed after creation.
11. `findRecordIndexById()` receives an integer record ID and searches the vector for a matching record.
12. It returns the matching vector index, or `-1` when no record with that ID exists.
13. `-1` means the record was not found.
14. We do not use `std::find_if()` yet because the learning goal is to practice ordinary loops, comparisons, and index-based logic before STL algorithms are introduced.
15. Update must validate all new values before modifying the record so partial updates do not corrupt the object.
16. If fields were changed one at a time before validation finished, the record could be left in a half-updated state.
17. We delete a record without iterators by shifting later records left and then calling `pop_back()`.
18. `pop_back()` removes the last element from the vector.
19. Deleting ID 2 does not make ID 3 become ID 2 because IDs are permanent identities, not positions.
20. IDs must be written to the file so they can be restored after a restart.
21. IDs must be restored when loading so the next record continues after the highest loaded ID instead of reusing a duplicate number.
22. If `nextId_` reset to 1 after every restart, duplicate IDs would reappear and the log would lose identity consistency.
23. If loaded IDs are 2, 8, and 5, the next ID should be 9 because the highest loaded ID is 8 and the next valid value is 9.
24. `addRecord()` creates a new user-created record and generates a fresh ID. `addLoadedRecord()` restores an existing persisted record and preserves its original ID while updating `nextId_` to stay ahead of all loaded IDs.
25. Malformed IDs should be rejected before `stoi()` because invalid data can overflow, parse incorrectly, or crash the program.
26. `999999999999999999999999` is dangerous because it exceeds the range of `int` and can overflow if converted without checking the value first.
27. File data is still untrusted because no external file can be assumed to be valid, complete, or correctly formatted.
28. An unknown update ID should leave the log unchanged because the operation should be a safe failure.
29. An unknown delete ID should leave the log unchanged because deleting a missing record would be incorrect and could corrupt the data set.
30. After deleting a record, we save again so the file reflects the latest state and the next run loads the corrected data.
31. Persistent CRUD means the application can create, read, update, and delete records while saving the data so the state remains available after restart.
32. `nextId_` belongs to `MaintenanceLog` because this class is responsible for the whole collection and for assigning fresh IDs to new records.
33. `MaintenanceLog` is responsible for generating IDs because it owns the collection and tracks the next available number.
34. Notes containing `|` are still accepted after the fourth delimiter because everything after the fourth separator is treated as the notes field.
35. If one of the earlier fields contains `|`, that makes the file ambiguous and the record should be treated as malformed and skipped.
36. The lifecycle is: create a `MaintenanceRecord`, save it to the file, restart the program, load it back into a `MaintenanceLog`, update it or add more records, save again, and reopen to confirm persistence.
37. The hardest bug I encountered today was making sure the next ID restored correctly after loading existing IDs and verifying duplicate IDs were not re-used after a restart.
38. The most interesting thing I learned today was that an ID is a durable identity, while a vector index is just a moving location in memory.
39. My favorite part was seeing how a record remains stable even when the vector shifts and the class keeps working correctly with the ID-based lookup.
40. I learned that careful validation is the safety net that prevents broken data from being saved or silently corrupting the log.
