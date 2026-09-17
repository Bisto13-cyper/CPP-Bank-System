#pragma once
#include "User.hpp"
#include "../Bank/BankExcepsion.hpp"
#include "../Bank/Bank.hpp"
#include <unordered_map>
#include <memory>

class Saving_Account;
class Checking_Account;
class Account;

class Customer : public User {
private:
    std::unordered_map<int, std::unique_ptr<Account>> Accounts;
    double total_balance = 0;

public:
    Customer(std::string N, std::string G, long long NI);

    Customer(std::string N, std::string G, std::string P, long long NI);

    bool login(std::string Pas, int Id, bool Trust);

    void makeCA(std::string Pas, double Balance, double Limit);

    void makeSA(std::string Pas, double Balance, double Over_draft);

    void delAc(Bank& bank, int delID, bool sure, Account* trans, std::string AccountPas, std::string UserPas);

    Account* getaccount(int id);

    void transfer(Bank& bank, double Money, int ToAccid, int FromAccId, int To_id, std::string Pas);

    std::unordered_map<std::string, std::string> getACinfo(int id, std::string Pas);

    void getInfo(std::unordered_map<std::string, std::string>& Info);

    ~Customer();
};
