# Day 25 Self Check

1. What does CRUD stand for?
2. Which menu operation represents Create?
3. Which operation represents Read?
4. Which operation represents Update?
5. Which operation represents Delete?
6. Why does each record need an ID?
7. What is the difference between a vector index and a record ID?
8. Can a vector index change after deletion?
9. Should a record ID change after deletion of another record?
10. Why doesn't `MaintenanceRecord` provide `setId()`?
11. What does `findRecordIndexById()` receive?
12. What does it return?
13. What does `-1` mean?
14. Why don't we use `std::find_if()` yet?
15. Why must update validate all new values before modifying the record?
16. What could happen if fields were modified one at a time before validation finished?
17. How do we delete a record without using iterators?
18. What does `pop_back()` do?
19. Does deleting ID 2 mean ID 3 becomes ID 2?
20. Why not?
21. Why must IDs be written to the file?
22. Why must IDs be restored when loading?
23. What problem would occur if `nextId_` returned to 1 after every restart?
24. If loaded IDs are 2, 8, and 5, what should the next ID be?
25. Why?
26. What is the difference between `addRecord()` and `addLoadedRecord()`?
27. Why should malformed IDs be rejected before `stoi()`?
28. Why is `999999999999999999999999` dangerous even though it contains only digits?
29. Why is file data still considered untrusted?
30. Why should an unknown update ID leave the log unchanged?
31. Why should an unknown delete ID leave the log unchanged?
32. After deleting a record, why do we save again?
33. What does persistent CRUD mean?
34. Which class owns `nextId_`?
35. Why is that class responsible for generating IDs?
36. What happens to notes containing `|`?
37. What happens if one of the earlier fields contains `|`?
38. Describe the lifecycle of a record from creation to save to restart to update to save to restart.
39. What was the hardest bug you encountered today?
40. What was the most interesting thing you learned today?

## Personal answers

1. CRUD stands for Create, Read, Update, and Delete.
2. The menu operation for Create is option 2: Add record.
3. The menu operation for Read is option 1: List records.
4. The menu operation for Update is option 3: Update record.
5. The menu operation for Delete is option 4: Delete record.
6. Each record needs an ID so it can be found reliably even after other records are added, moved, or deleted.
7. A vector index is the current storage position, while an ID is a stable identity.
8. Yes, the vector index can change after deletion.
9. No, the record ID should stay the same after another record is deleted.
10. `MaintenanceRecord` does not provide `setId()` because the ID should not change after creation.
11. `findRecordIndexById()` receives an integer record ID.
12. It returns the matching vector index for that ID.
13. `-1` means the record was not found.
14. We do not use `std::find_if()` yet because the lesson is still practicing ordinary loops and index logic.
15. Update validates first so the record is never left half-modified.
16. If fields changed one at a time, the object could end up in a partially updated state.
17. We delete a record by shifting later records left and then calling `pop_back()`.
18. `pop_back()` removes the last element in the vector.
19. No, deleting ID 2 does not make ID 3 become ID 2.
20. IDs are identities, not storage positions.
21. IDs must be written to the file so they survive a restart.
22. IDs must be restored when loading so the next record does not reuse an old ID.
23. If `nextId_` reset to 1 after every restart, duplicate IDs would be created.
24. The next ID should be 9.
25. Because the highest loaded ID is 8, so the next valid ID is 9.
26. `addRecord()` creates a brand-new record and generates a fresh ID, while `addLoadedRecord()` restores an existing persisted record and preserves its original ID.
27. Malformed IDs should be rejected before `stoi()` to avoid invalid or overflow-prone input.
28. `999999999999999999999999` is dangerous because it is too large for `int` and can overflow.
29. File data is untrusted because external files can be missing, corrupted, or malformed.
30. An unknown update ID should leave the log unchanged because the operation should fail safely.
31. An unknown delete ID should leave the log unchanged because it does not exist.
32. We save again so the file reflects the latest state after the delete.
33. Persistent CRUD means the data survives across program restarts.
34. `nextId_` belongs to `MaintenanceLog`.
35. `MaintenanceLog` is responsible because it owns the collection and assigns new IDs.
36. Notes containing `|` are treated as part of the notes field because everything after the fourth separator is notes.
37. If an earlier field contains `|`, the record becomes ambiguous and should be skipped as malformed.
38. A record is created, saved, loaded on restart, updated, saved again, and then loaded again to confirm persistence.
39. The hardest bug was making sure duplicate loaded IDs were rejected while still preserving the correct next ID.
40. The most interesting thing I learned was that an ID is identity while a vector index is only location.
