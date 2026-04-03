# Client Architecture

## Tech Stack

- Frontend: HTML, TypeScript, Fetch API
- Backend: Node.js, Express, CORS
- Language: TypeScript
- Data format: JSON
- Architecture style: Client-Server Architecture
- Design pattern: Strategy Pattern

## Architecture Overview

This system is split into two main parts:

1. Client
   The browser UI collects user input such as year, total income, worked days, and daily income. It sends this data to the server using an HTTP `POST` request.

2. Server
   The Express server receives the request, creates a `TaxPayer` object, and sends it to `TaxService`. `TaxService` selects the correct strategy based on the given year:
   - `Tax2023Strategy`
   - `Tax2024Strategy`

After calculation, the server returns the result as JSON, and the client shows the tax amount to the user.

## Request Flow

1. User enters tax data in the browser
2. Client sends `POST /tax/calculate`
3. Server processes the request
4. `TaxService` chooses the correct tax strategy
5. Server returns JSON response
6. Client displays the result
