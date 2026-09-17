#include "SavingAccount.hpp"
#include "../Bank/BankExcepsion.hpp"
#include "Account.hpp"
#include <iostream>

double Saving_Account::Current_Interest_Rate = 0.02;

double Saving_Account::Monthly_applyInterest() {
    Balance += Balance * (Interest_Rate / 12.0);
    return Balance;
}

double Saving_Account::Yearly_applyInterest() {
    Balance += Balance * Interest_Rate;
    return Balance;
}

double Saving_Account::Calclimits() {
    Limit_Rate = (30.0 / 100.0) * Balance;
    return Limit_Rate;
}

double Saving_Account::resetInterest() {
    Interest_Rate = Current_Interest_Rate;
    return Interest_Rate;
}

double Saving_Account::withdraw(Bank& bank, double WD, std::string Pas) {
    if (Pas != Password) throw InvalidPasException();
    if (WD <= 0) throw InvalidAmountException();
    if (WD > Balance) throw InsufficientFundsException();
    if ((WD + Limits) > Limit_Rate) throw ExceededLimitException();

    Balance -= WD;
    Limits += WD;
    bank.earseMoney(WD);
    return Balance;
}

void Saving_Account::displayAccountInfo(std::string Pas) {
    if (Pas != Password) throw InvalidPasException();
    std::cout << "____________________________\n";
    std::cout << "Account user Info:\n";
    std::cout << "National Number: " << National_Number << "\n";
    std::cout << "Id: " << id << "\n";
    std::cout << "____________________________\n";
    std::cout << "Balance Info:\n";
    std::cout << "Balance: " << Balance << "\n";
    std::cout << "The Limit: " << Limits << "\n";
    std::cout << "Interest: " << Interest_Rate << "% yearly\n";
}

double Saving_Account::getcurrentlimit(std::string Pas) {
    if (Pas != Password) throw InvalidPasException();
    return Limit_Rate;
}

double Saving_Account::getinterest(std::string Pas) {
    if (Pas != Password) throw InvalidPasException();
    return Interest_Rate;
}

double Saving_Account::getlimit(std::string Pas) {
    if (Pas != Password) throw InvalidPasException();
    return Limits;
}

void Saving_Account::monthlyreset(bool isInterestReset) {
    Calclimits();
    Monthly_applyInterest();
    if (isInterestReset) resetInterest();
    Limits = 0;
}

void Saving_Account::yearlyreset(bool isInterestReset) {
    Calclimits();
    Yearly_applyInterest();
    if (isInterestReset) resetInterest();
    Limits = 0;
}

std::string Saving_Account::gettype() { return "Saving_Account"; }

void Saving_Account::getinfo(std::unordered_map<std::string, std::string>& info) {
    Account::getinfo(info);
    info["Limits"] = std::to_string(Limits);
    info["Interest_Rate"] = std::to_string(Interest_Rate);
}

double Saving_Account::get_Current_Interest_Rate() {
    return Current_Interest_Rate;
}
