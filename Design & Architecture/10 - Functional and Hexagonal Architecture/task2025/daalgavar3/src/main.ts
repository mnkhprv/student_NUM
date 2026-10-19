type RegistrationRequest = {
  id: string;
  name: string;
  credits: number;
};

type RegistrationResult =
  | { ok: true; student: RegistrationRequest }
  | { ok: false; error: string };

const validateCredits = (request: RegistrationRequest): RegistrationResult =>
  request.credits >= 3
    ? { ok: true, student: request }
    : { ok: false, error: "Credits must be at least 3" };

const normalizeName = (result: RegistrationResult): RegistrationResult =>
  result.ok
    ? {
        ok: true,
        student: {
          ...result.student,
          name: result.student.name.trim(),
        },
      }
    : result;

const saveStudent = (result: RegistrationResult): RegistrationResult => result;

function runFlow(request: RegistrationRequest): RegistrationResult {
  return saveStudent(normalizeName(validateCredits(request)));
}

const input: RegistrationRequest = { id: "S-003", name: " Carol ", credits: 5 };

console.log("Task 3");
console.log("Input:", input);
console.log("Output:", runFlow(input));
console.log("");
console.log("Explanation");
console.log("1. The sequence diagram shows who calls whom in the OOP style.");
console.log("2. The data flow diagram shows how data moves step by step in the FP style.");
console.log("3. Mermaid code is provided in mermaid.md for Mermaid Live Editor.");
