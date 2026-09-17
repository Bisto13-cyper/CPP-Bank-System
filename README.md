# 🏦 Bank System v1.0

A console-based Bank Management System written in modern **C++17**, built to practice and combine core OOP concepts (inheritance, polymorphism, encapsulation, abstraction) with intermediate/advanced features (custom exception hierarchies, smart pointers, STL containers, static members, operator-safe design).

This is a **learning project** — the architecture is intentionally kept clean and I/O-free at the core, so it can grow into a real backend later (SQL persistence, a REST API, a frontend) without rewriting the business logic.

---

## ✨ Features

### 👤 User Roles
- **Customer** — sign up, log in, open accounts, deposit/withdraw, transfer money, check balances, change password
- **Employee** — onboard customers, open accounts on their behalf, view customer data, freeze/unfreeze checking accounts, view bank-wide stats (requires granted access)
- **Admin** — hire/fire employees, grant/revoke employee access, create other admins, view all users, edit bank-wide settings (transfer fee, interest rate), view total bank money

### 💳 Account Types
- **Saving Account** — yearly/monthly compounding interest, rolling withdrawal limit (30% of balance per period)
- **Checking Account** — overdraft limit, flat transfer fee per withdrawal, freeze/unfreeze support

### 🛡️ Core Engineering
- Custom exception hierarchy (`BankException` base + 12 specific subclasses) instead of error codes
- RAII + `std::unique_ptr` ownership everywhere (no raw `new`/`delete`)
- Every read operation returns `std::unordered_map<std::string,std::string>` instead of printing — the core has **zero UI coupling**, so it's ready to sit behind an API later
- Static member tracking for global counters (total users, total accounts) and bank-wide policy values (interest rate, transfer fee)
- Unique ID generation with collision checking for both `User` and `Account`

---

## 🧰 Tech Stack

| Layer | Technology |
|---|---|
| Language | C++17 |
| Build | g++ / GCC |
| Data storage | In-memory (`unordered_map`) — **no persistence yet**, see [Roadmap](#-roadmap--known-limitations) |
| Interface | Console menu (`main.cpp`) |

---

## 📦 Prerequisites

You need a C++ compiler that supports C++17. Pick your platform:

### Windows
1. Install [MSYS2](https://www.msys2.org/) (recommended) or [MinGW-w64](https://www.mingw-w64.org/).
2. Inside the MSYS2 terminal, run:
   ```
   pacman -S mingw-w64-ucrt-x86_64-gcc
   ```
3. Add the MinGW `bin` folder to your PATH, then confirm with:
   ```
   g++ --version
   ```
4. Run the project from **Git Bash** or **WSL** (recommended) so `Compile.sh` works as-is. On plain CMD/PowerShell, use the manual build command in [Build & Run](#-build--run) instead.

### macOS
```
xcode-select --install
```
This installs Apple's Clang toolchain, which g++ is aliased to. Confirm with `g++ --version`.

### Linux (Debian/Ubuntu)
```
sudo apt update && sudo apt install g++ build-essential
```

---

## 🚀 Build & Run

```bash
gh repo clone Bisto13-cyper/CPP-Bank-System
cd BankSystem
chmod +x Compile.sh
./Compile.sh
```

`Compile.sh` does exactly this:
```bash
g++ -std=c++17 -Wall -Wextra main.cpp Bank/*.cpp Users/*.cpp Accounts/*.cpp helper/*.cpp -o BankSystem
./BankSystem
```

If you'd rather build manually (e.g. on Windows CMD):
```
g++ -std=c++17 -Wall -Wextra main.cpp Bank/*.cpp Users/*.cpp Accounts/*.cpp helper/*.cpp -o BankSystem.exe
BankSystem.exe
```

On first run, the program seeds one Admin account and prints its ID + password to the console — use those to log in and explore the Admin menu.

---

## 📁 Project Structure

```
BankSystem/
├── main.cpp                 # Console menu / entry point
├── headers.hpp               # Single aggregator include
├── Compile.sh
├── Bank/
│   ├── Bank.hpp / Bank.cpp           # Core orchestrator: owns all users, bank-wide policy
│   └── BankExcepsion.hpp             # Custom exception hierarchy
├── Users/
│   ├── User.hpp / User.cpp           # Base class: id, password, name, national number
│   ├── Customer.hpp / Customer.cpp   # Owns accounts, transfers, self-service actions
│   ├── Employee.hpp / Employee.cpp   # Onboarding, access-gated customer operations
│   └── Admin.hpp / Admin.cpp         # Employee management, bank-wide settings
├── Accounts/
│   ├── Account.hpp / Account.cpp             # Abstract base: balance, password, id
│   ├── SavingAccount.hpp / SavingAccount.cpp # Interest + rolling limit
│   └── CheckingAccount.hpp / Checking_Account.cpp # Overdraft + transfer fee
└── helper/
    └── bisto.h / bisto.cpp           # Random ID generation, string helpers, password strength check
```

---

## 🖥️ Menu Walkthrough

```
1. Login as Admin
2. Login as Employee
3. Login as Customer
4. Sign up as new Customer
0. Exit
```

Each role then opens its own submenu (deposit/withdraw/transfer for customers, onboarding/access-gated lookups for employees, staff & policy management for admins). Every action is wrapped in try/catch, so mistakes (wrong password, insufficient funds, missing access) print a clear message instead of crashing.

---

## ⚠️ Exception Reference

| Exception | Thrown when |
|---|---|
| `InvalidPasException` | Wrong password supplied |
| `WeakPasswordException` | New password fails the strength check |
| `InsufficientFundsException` | Withdrawal exceeds available balance/overdraft |
| `InvalidAmountException` | Amount is zero or negative |
| `ExceededLimitException` | Saving account withdrawal exceeds its rolling limit |
| `FaildAccess` | Untrusted login attempt |
| `OutstandingBalance` | Trying to close an account without clearing its balance |
| `FailedSignUp` | Bad signup parameters (unknown account type, wrong bank password, etc.) |
| `AccessRequired` | Employee action attempted without granted access |
| `UserNotFound` / `AccountNotFound` | Lookup by ID failed |
| `WrongProcess` | Invalid state transition (e.g. un-freezing an account that isn't frozen) |

---

## 🧭 Roadmap / Known Limitations

Ordered from **easiest → hardest**, matching the order I plan to tackle them:

| # | Limitation | What's missing |
|---|---|---|
| 1 | **Hardcoded seed/config values** | Bank name, bank password, and the seed admin are hardcoded in `main.cpp` — should move to a config file |
| 2 | **No automated tests** | No unit tests yet; correctness is currently verified manually |
| 3 | **Plaintext passwords** | Passwords are compared as raw strings — needs proper hashing (bcrypt/argon2) before this touches anything real |
| 4 | **No logging** | No audit trail of transactions/logins — needed before this could be trusted with real money |
| 5 | **No persistence layer (SQL)** | Everything lives in `unordered_map` in memory — restarting the program wipes all data. Next step: a `Repository` interface backed by SQLite, then Postgres/MySQL |
| 6 | **No backend/API** | The core logic is already decoupled from I/O (returns maps, throws exceptions) — next is wrapping it in a REST API (`cpp-httplib`/`Crow`, or a separate Node/Python service on top of this engine) |
| 7 | **No frontend** | Once the API exists, any client (React/Vue/plain HTML+JS) can consume it |
| 8 | **No concurrency support** | Single-threaded only — real banking backends need to handle simultaneous transactions safely (mutexes/transactions) |

---

## 📜 License

Personal learning project — use freely for your own practice. 