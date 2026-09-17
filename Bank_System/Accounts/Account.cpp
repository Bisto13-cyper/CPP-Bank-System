#include "Account.hpp"
#include "../Bank/BankExcepsion.hpp"
#include "../Bank/Bank.hpp"
#include "../helper/bisto.h"

std::unordered_set<int> Account::IDS;

int Account::genrateuniqe_id() {
    int newid;
    do {
        newid = ID.randomInt(0, 1000000);
    } while (IDS.count(newid));
    IDS.insert(newid);
    return newid;
}

void Account::resetpas(std::string OldPas, const std::string& NewPas) {
    if (OldPas != Password) throw InvalidPasException();
    if (!Bisto::logger::isStrongPassword(NewPas)) throw WeakPasswordException();
    Password = NewPas;
}

void Account::resetpas(long long Nat, int I, const std::string& NewPas) {
    if (I != id || Nat != National_Number) throw InvalidPasException();
    if (!Bisto::logger::isStrongPassword(NewPas)) throw WeakPasswordException();
    Password = NewPas;
}

double Account::CheckBalance(std::string Pas) {
    if (Pas != Password) throw InvalidPasException();
    return Balance;
}

bool Account::isrightpas(std::string Pas) { return Pas == Password; }

void Account::deposit(Bank& bank, double Add) {
    if (Add <= 0) throw InvalidAmountException();
    Balance += Add;
    bank.addMoney(Add);
}

void Account::getinfo(std::unordered_map<std::string, std::string>& info) {
    info["National_Number"] = std::to_string(National_Number);
    info["ID"] = std::to_string(id);
    info["Balance"] = std::to_string(Balance);
    info["Type"] = gettype();
}

Account::~Account() {
    Bank::minus_Account();
    IDS.erase(id);
}
