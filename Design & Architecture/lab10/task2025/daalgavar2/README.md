# Task 2

Goal: compare OOP enrollment flow with FP enrollment pipeline.

Requirement implemented:
- If student credits are 3 or more, enrollment succeeds
- Otherwise an error is returned

Files:
- `src/main.ts`: OOP + FP implementations
- `mermaid.md`: sequence diagram and pipe flow diagram

How to run:
```bash
cd lab11/daalgavar2
npm run build
npm start
```

Included concepts:
- OOP uses `StudentService.enroll()` and throws `Exception`
- FP uses `validateCredits -> createStudent -> saveToDB`
- FP error handling is done with `Either`
