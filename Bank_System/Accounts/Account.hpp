#pragma once
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "../helper/bisto.h"
#include "../Bank/Bank.hpp"

class Bank;

class Account {
private:
    Bisto::randoms ID;
    static std::unordered_set<int> IDS;

protected:
    std::string Password;
    long long National_Number;
    double Balance;
    int id;

public:
    Account(std::string Pas, long long NaNu) : Password(Pas), National_Number(NaNu), Balance(0) {
        id = genrateuniqe_id();
        Bank::plus_Account();
    }

    Account(std::string Pas, long long NaNu, double Ba) : Password(Pas), National_Number(NaNu), Balance(Ba) {
        id = genrateuniqe_id();
        Bank::plus_Account();
    }

    Account(const Account&) = delete;
    Account& operator=(const Account&) = delete;

    bool isrightpas(std::string Pas);

    int genrateuniqe_id();

    int getid() { return id; }

    void resetpas(std::string Old_Pas, const std::string& New_Pas);

    void resetpas(long long National_Number, int Id, const std::string& New_Pas);

    void deposit(Bank& bank, double Add);

    virtual double withdraw(Bank&, double, std::string) = 0;

    double CheckBalance(std::string);

    virtual void displayAccountInfo(std::string) = 0;

    virtual std::string gettype() = 0;

    virtual void getinfo(std::unordered_map<std::string, std::string>& info);

    virtual ~Account();

private:
    friend class Bank;
    std::string PaswithhighAcces(Bank* /*BANK*/) {
        return Password;
    }
};
