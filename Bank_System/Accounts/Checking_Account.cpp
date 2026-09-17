#include "CheckingAccount.hpp"
#include "../Bank/BankExcepsion.hpp"
#include "Account.hpp"
#include <iostream>
double Checking_Account::transFee = 5.0;

std::string Checking_Account::gettype() { return "Checking_Account"; }

bool Checking_Account::is_cooled() { return iscooled; }

void Checking_Account::clooAc() { iscooled = !iscooled; }

void Checking_Account::setOV(double OV) { Over_draft_limit = OV; }

double Checking_Account::getOV() { return Over_draft_limit; }

double Checking_Account::withdraw(Bank& bank, double WD, std::string Pas) {
    if (Pas != Password) throw InvalidPasException();
    if (WD <= 0) throw InvalidAmountException();

    if ((WD + transFee) > (Balance + Over_draft_limit)) throw InsufficientFundsException();

    Balance -= (WD + transFee);
    bank.earseMoney(WD);
    return Balance;
}

void Checking_Account::displayAccountInfo(std::string Pas) {
    if (Pas != Password) throw InvalidPasException();
    std::cout << "____________________________\n";
    std::cout << "Account user Info:\n";
    std::cout << "National Number: " << National_Number << "\n";
    std::cout << "Id: " << id << "\n";
    std::cout << "____________________________\n";
    std::cout << "Balance Info:\n";
    std::cout << "Balance: " << Balance << "\n";
    std::cout << "Over draft Limit: " << Over_draft_limit << "\n";
}

void Checking_Account::getinfo(std::unordered_map<std::string, std::string>& info) {
    Account::getinfo(info);
    info["Over_draft_limit"] = std::to_string(Over_draft_limit);
    info["Is_Current?"] = !iscooled ? "True" : "False";
}

double Checking_Account::get_transFee() { return transFee; }
