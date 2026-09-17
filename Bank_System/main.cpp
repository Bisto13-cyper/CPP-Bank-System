#include "headers.hpp"
#include <iostream>
#include <limits>

// ---------- small console helpers ----------

static void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static std::string askString(const std::string& label) {
    std::cout << label;
    std::string v;
    std::getline(std::cin, v);
    return v;
}

static int askInt(const std::string& label) {
    std::cout << label;
    int v;
    while (!(std::cin >> v)) {
        std::cout << "Please enter a valid number: ";
        clearInputBuffer();
    }
    clearInputBuffer();
    return v;
}

static long long askLL(const std::string& label) {
    std::cout << label;
    long long v;
    while (!(std::cin >> v)) {
        std::cout << "Please enter a valid number: ";
        clearInputBuffer();
    }
    clearInputBuffer();
    return v;
}

static double askDouble(const std::string& label) {
    std::cout << label;
    double v;
    while (!(std::cin >> v)) {
        std::cout << "Please enter a valid number: ";
        clearInputBuffer();
    }
    clearInputBuffer();
    return v;
}

static void printInfo(const std::unordered_map<std::string, std::string>& info) {
    for (auto& kv : info)
        std::cout << "   " << kv.first << ": " << kv.second << "\n";
}

// ---------- role menus ----------

static void customerMenu(Bank& bank, int myId) {
    while (true) {
        std::cout << "\n--- Customer Menu (ID " << myId << ") ---\n"
                  << "1. View my info\n"
                  << "2. Open Saving Account\n"
                  << "3. Open Checking Account\n"
                  << "4. Deposit\n"
                  << "5. Withdraw\n"
                  << "6. View account info\n"
                  << "7. Transfer money\n"
                  << "8. Change password\n"
                  << "0. Logout\n";
        int choice = askInt("Choose: ");

        try {
            Customer* me = bank.getCustomer(myId);

            if (choice == 1) {
                std::unordered_map<std::string, std::string> info;
                me->getInfo(info);
                printInfo(info);
            } else if (choice == 2) {
                std::string pas = askString("Account password: ");
                double bal = askDouble("Starting balance (-1 for default): ");
                double limit = askDouble("Monthly limit override, 30% of balance if -1: ");
                me->makeSA(pas, bal, limit);
                std::cout << "Saving account created.\n";
            } else if (choice == 3) {
                std::string pas = askString("Account password: ");
                double bal = askDouble("Starting balance (-1 for default 10): ");
                double ov = askDouble("Overdraft limit (-1 for none): ");
                me->makeCA(pas, bal, ov);
                std::cout << "Checking account created.\n";
            } else if (choice == 4) {
                int accId = askInt("Account ID: ");
                double amt = askDouble("Amount: ");
                Account* acc = me->getaccount(accId);
                if (!acc) throw AccountNotFound();
                acc->deposit(bank, amt);
                std::cout << "Deposited.\n";
            } else if (choice == 5) {
                int accId = askInt("Account ID: ");
                std::string pas = askString("Account password: ");
                double amt = askDouble("Amount: ");
                Account* acc = me->getaccount(accId);
                if (!acc) throw AccountNotFound();
                acc->withdraw(bank, amt, pas);
                std::cout << "Withdrawn.\n";
            } else if (choice == 6) {
                int accId = askInt("Account ID: ");
                std::string pas = askString("Account password: ");
                auto info = me->getACinfo(accId, pas);
                printInfo(info);
            } else if (choice == 7) {
                std::string myPas = askString("Your login password: ");
                int fromAcc = askInt("Your account ID to send from: ");
                int toUser = askInt("Recipient customer ID: ");
                int toAcc = askInt("Recipient account ID: ");
                double amt = askDouble("Amount: ");
                me->transfer(bank, amt, toAcc, fromAcc, toUser, myPas);
                std::cout << "Transfer complete.\n";
            } else if (choice == 8) {
                std::string oldPas = askString("Old password: ");
                std::string newPas = askString("New password (6+ chars, letters+digits): ");
                me->resetpas(oldPas, newPas);
                std::cout << "Password changed.\n";
            } else if (choice == 0) {
                return;
            } else {
                std::cout << "Unknown option.\n";
            }
        } catch (const BankException& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
}

static void employeeMenu(Bank& bank, int myId) {
    while (true) {
        std::cout << "\n--- Employee Menu (ID " << myId << ") ---\n"
                  << "1. Add customer\n"
                  << "2. Add account for existing customer\n"
                  << "3. View customer data\n"
                  << "4. Check a specific customer account\n"
                  << "5. Freeze / unfreeze a checking account\n"
                  << "6. Bank stats (users / accounts / rates)\n"
                  << "0. Logout\n";
        int choice = askInt("Choose: ");

        try {
            Employee* me = bank.getEmployee(myId);

            if (choice == 1) {
                std::string name = askString("Customer name: ");
                std::string mail = askString("Email: ");
                std::string type = askString("Account type (SAVING_ACCOUNT / CHECKING_ACCOUNT): ");
                std::string userPas = askString("Customer login password: ");
                long long nat = askLL("National number: ");
                std::string accPas = askString("Account password: ");
                double startBal = askDouble("Starting balance (-1 default): ");
                double other = askDouble("Overdraft/limit (-1 default): ");
                std::cout << me->addCustomer(&bank, name, mail, type, userPas, nat, accPas, startBal, other);
            } else if (choice == 2) {
                int custId = askInt("Customer ID: ");
                std::string type = askString("Account type (SAVING_ACCOUNT / CHECKING_ACCOUNT): ");
                std::string accPas = askString("Account password: ");
                double startBal = askDouble("Starting balance (-1 default): ");
                double other = askDouble("Overdraft/limit (-1 default): ");
                me->addAc(bank, custId, type, accPas, startBal, other);
                std::cout << "Account added.\n";
            } else if (choice == 3) {
                int custId = askInt("Customer ID: ");
                auto data = me->getdata(bank, custId);
                printInfo(data);
            } else if (choice == 4) {
                int custId = askInt("Customer ID: ");
                int accId = askInt("Account ID: ");
                auto data = me->checkAcc(bank, custId, accId);
                printInfo(data);
            } else if (choice == 5) {
                int custId = askInt("Customer ID: ");
                int accId = askInt("Account ID: ");
                std::string action = askString("freeze/unfreeze: ");
                if (action == "freeze")
                    std::cout << me->colling_Acc(bank, custId, accId, "Frozen by employee");
                else
                    std::cout << me->un_colling_Acc(bank, custId, accId, "Unfrozen by employee");
            } else if (choice == 6) {
                std::cout << "Users: " << me->get_Num_Of_users(bank) << "\n";
                std::cout << "Accounts: " << me->get_Num_Of_Accounts(bank) << "\n";
                std::cout << "Current Interest Rate: " << me->get_CIR(bank) << "\n";
                std::cout << "Transfer Fee: " << me->get_tf(bank) << "\n";
            } else if (choice == 0) {
                return;
            } else {
                std::cout << "Unknown option.\n";
            }
        } catch (const BankException& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
}

static void adminMenu(Bank& bank, int myId, const std::string& bankPassword) {
    while (true) {
        std::cout << "\n--- Admin Menu (ID " << myId << ") ---\n"
                  << "1. Add employee\n"
                  << "2. Delete employee\n"
                  << "3. Grant employee access\n"
                  << "4. Revoke employee access\n"
                  << "5. Add another admin\n"
                  << "6. List all customers\n"
                  << "7. List all employees\n"
                  << "8. Bank total money\n"
                  << "9. Edit transfer fee\n"
                  << "10. Edit interest rate\n"
                  << "0. Logout\n";
        int choice = askInt("Choose: ");

        try {
            Admin* me = bank.getAdmin(myId);

            if (choice == 1) {
                std::string name = askString("Name: ");
                std::string mail = askString("Email: ");
                std::string pass = askString("Password: ");
                std::string job = askString("Job title: ");
                std::string rank = askString("Rank: ");
                long long nat = askLL("National number: ");
                double sal = askDouble("Salary: ");
                bool ok = me->addemployee(bank, name, mail, pass, job, rank, nat, sal);
                std::cout << (ok ? "Employee added.\n" : "Failed to add employee.\n");
            } else if (choice == 2) {
                int id = askInt("Employee ID: ");
                long long nat = askLL("Their national number: ");
                me->delemployee(bank, id, nat);
                std::cout << "Employee removed.\n";
            } else if (choice == 3) {
                int id = askInt("Employee ID: ");
                me->give_Access(bank, id);
                std::cout << "Access granted.\n";
            } else if (choice == 4) {
                int id = askInt("Employee ID: ");
                me->remove_Access(bank, id);
                std::cout << "Access revoked.\n";
            } else if (choice == 5) {
                std::string name = askString("Name: ");
                std::string mail = askString("Email: ");
                std::string pass = askString("Password: ");
                std::string job = askString("Job title: ");
                std::string rank = askString("Rank: ");
                long long nat = askLL("National number: ");
                double sal = askDouble("Salary: ");
                me->addAdmin(bank, true, true, name, mail, pass, job, rank, nat, sal);
                std::cout << "Admin added.\n";
            } else if (choice == 6) {
                auto all = me->getCustomers(bank, bankPassword);
                for (auto& kv : all) {
                    std::cout << kv.first << ":\n";
                    printInfo(kv.second);
                }
            } else if (choice == 7) {
                auto all = me->getEmployees(bank, bankPassword);
                for (auto& kv : all) {
                    std::cout << kv.first << ":\n";
                    printInfo(kv.second);
                }
            } else if (choice == 8) {
                std::cout << "Bank money: " << me->getmoney(bank, bankPassword) << "\n";
            } else if (choice == 9) {
                double v = askDouble("New transfer fee: ");
                me->Edit_transfee(bank, v);
                std::cout << "Updated.\n";
            } else if (choice == 10) {
                double v = askDouble("New interest rate (e.g. 0.02 for 2%): ");
                me->Edit_Current_Interest_Rate(bank, v);
                std::cout << "Updated.\n";
            } else if (choice == 0) {
                return;
            } else {
                std::cout << "Unknown option.\n";
            }
        } catch (const BankException& e) {
            std::cout << "Error: " << e.what() << "\n";
        } catch (const std::invalid_argument& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
}

int main() {
    const std::string bankPassword = "root123";
    Bank bank("Bisto Bank", 1000000.0, bankPassword);

    try {
        bank.addAdmin(true, "Root Admin", "root@bank.com", "Admin123", "Manager", "Root", 100000000, 20000);
    } catch (const BankException& e) {
        std::cout << "Seed admin failed: " << e.what() << "\n";
    }

    auto admins = bank.getAdmins(bankPassword);
    for (auto& kv : admins) {
        std::cout << "Seed admin ready -> Name: " << kv.first
                  << " | ID: " << kv.second.at("Id")
                  << " | Password: Admin123\n";
    }

    std::cout << "\n===== Welcome to " << bank.getName() << " =====\n";

    while (true) {
        std::cout << "\n1. Login as Admin\n"
                  << "2. Login as Employee\n"
                  << "3. Login as Customer\n"
                  << "4. Sign up as new Customer\n"
                  << "0. Exit\n";
        int choice = askInt("Choose: ");

        if (choice == 0) {
            std::cout << "Goodbye.\n";
            break;
        }

        try {
            if (choice == 1) {
                int id = askInt("Admin ID: ");
                std::string pas = askString("Password: ");
                Admin* adm = bank.getAdmin(id);
                adm->getId(pas); // throws InvalidPasException on mismatch
                adminMenu(bank, id, bankPassword);
            } else if (choice == 2) {
                int id = askInt("Employee ID: ");
                std::string pas = askString("Password: ");
                Employee* emp = bank.getEmployee(id);
                emp->getId(pas);
                employeeMenu(bank, id);
            } else if (choice == 3) {
                int id = askInt("Customer ID: ");
                std::string pas = askString("Password: ");
                Customer* cus = bank.getCustomer(id);
                cus->login(pas, id, true);
                customerMenu(bank, id);
            } else if (choice == 4) {
                std::string name = askString("Name: ");
                std::string mail = askString("Email: ");
                std::string type = askString("Account type (SAVING_ACCOUNT / CHECKING_ACCOUNT): ");
                std::string userPas = askString("Choose a login password: ");
                long long nat = askLL("National number: ");
                std::string accPas = askString("Choose an account password: ");
                double startBal = askDouble("Starting balance (-1 default): ");
                double other = askDouble("Overdraft/limit (-1 default): ");
                bank.addCustomer(true, name, mail, type, userPas, nat, accPas, startBal, other);
                std::cout << "Signed up! Log in from the main menu with your login password.\n";
            } else {
                std::cout << "Unknown option.\n";
            }
        } catch (const BankException& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}
