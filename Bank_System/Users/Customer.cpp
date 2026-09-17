#include "Customer.hpp"
#include "../Accounts/Account.hpp"
#include "../Accounts/SavingAccount.hpp"
#include "../Accounts/CheckingAccount.hpp"

Customer::Customer(std::string N, std::string G, long long NI) : User(N, G, NI) {}

Customer::Customer(std::string N, std::string G, std::string P, long long NI) : User(N, G, P, NI) {}

bool Customer::login(std::string Pas, int Id, bool Trust) {
    if (!Trust)
        throw FaildAccess();

    if (Id != U_Id)
        return false;

    if (Pas != Password)
        throw InvalidPasException();

    return true;
}

void Customer::makeSA(std::string Pas, double Ba, double L) {
    std::unique_ptr<Saving_Account> newSA;

    if (L == -1)
        newSA = std::make_unique<Saving_Account>(Pas, National_Number, Ba);
    else
        newSA = std::make_unique<Saving_Account>(Pas, National_Number, Ba, L);

    int newId = newSA->getid();
    Accounts[newId] = std::move(newSA);
}

void Customer::makeCA(std::string Pas, double Ba, double OV) {
    double actualBalance = (Ba == -1) ? 10 : Ba;
    double actualOverdraft = (OV == -1) ? 0 : OV;

    auto newCA = std::make_unique<Checking_Account>(Pas, National_Number, actualBalance, actualOverdraft);

    int newId = newCA->getid();
    Accounts[newId] = std::move(newCA);
}

void Customer::delAc(Bank& bank, int del, bool sure, Account* trans, std::string AcPas, std::string UPas) {
    if (!sure) return;

    auto it = Accounts.find(del);
    if (it == Accounts.end())
        throw AccountNotFound();
    Account* acc = it->second.get();

    if (UPas != Password || !acc->isrightpas(AcPas))
        throw InvalidPasException();

    double balance = acc->CheckBalance(AcPas);
    if (balance != 0) {
        if (trans == nullptr)
            throw OutstandingBalance();
        bank.transfer(acc, trans, balance);
    }

    if (acc->CheckBalance(AcPas) > 0)
        throw OutstandingBalance();

    Accounts.erase(it);
}

std::unordered_map<std::string, std::string> Customer::getACinfo(int id, std::string Pas) {
    auto it = Accounts.find(id);
    if (it == Accounts.end())
        throw AccountNotFound();

    if (!it->second->isrightpas(Pas))
        throw InvalidPasException();

    std::unordered_map<std::string, std::string> info;
    it->second->getinfo(info);

    return info;
}

void Customer::getInfo(std::unordered_map<std::string, std::string>& info) {
    User::getInfo(info);
    info["Accounts_Number"] = std::to_string(Accounts.size());
    for (auto& pair : Accounts) {
        info["Type:" + std::to_string(pair.first)] = pair.second->gettype();
    }
}

Account* Customer::getaccount(int id) {
    auto it = Accounts.find(id);
    if (it != Accounts.end())
        return it->second.get();
    return nullptr;
}

void Customer::transfer(Bank& bank, double Money, int ToAccid, int FromAccId, int To_id, std::string Pas) {
    if (Pas != Password)
        throw InvalidPasException();

    auto My_Acc = getaccount(FromAccId);
    if (My_Acc == nullptr)
        throw AccountNotFound();

    auto thier_Acc = bank.getAccount(To_id, ToAccid);

    bank.transfer(My_Acc, thier_Acc, Money);
}

Customer::~Customer() {
    Accounts.clear();
}
