# Task 3 Mermaid Code

Paste the following code into Mermaid Live Editor.

## Sequence Diagram

```mermaid
sequenceDiagram
    actor User
    participant Controller
    participant Service
    participant Repository

    User->>Controller: submit registration request
    Controller->>Service: register(request)
    Service->>Service: validate credits
    Service->>Repository: save(student)
    Repository-->>Service: saved student
    Service-->>Controller: registration result
    Controller-->>User: response
```

## Data Flow Diagram

```mermaid
flowchart LR
    A[RegistrationRequest] --> B[validateCredits]
    B --> C[normalizeName]
    C --> D[saveStudent]
    D --> E[RegistrationResult]
```

## Explanation

- The sequence diagram focuses on interaction between objects.
- The data flow diagram focuses on transformation steps.
- The TypeScript code in `src/main.ts` follows the same flow as the Mermaid diagrams.
