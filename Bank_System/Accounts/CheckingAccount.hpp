#pragma once
#include <string>
#include <unordered_map>
#include "Account.hpp"
#include "../Bank/Bank.hpp"

class Checking_Account : public Account {
private:
    static double transFee;
    double Over_draft_limit;
    bool iscooled;

public:
    Checking_Account(std::string Pas, long long NaNu)
        : Account(Pas, NaNu, 10), Over_draft_limit(0), iscooled(false) {}

    Checking_Account(std::string Pas, long long NaNu, double Ba)
        : Account(Pas, NaNu, Ba), Over_draft_limit(0), iscooled(false) {}

    Checking_Account(std::string Pas, long long NaNu, double Ba, double OV)
        : Account(Pas, NaNu, Ba), Over_draft_limit(OV), iscooled(false) {}

    void clooAc();

    bool is_cooled();

    void setOV(double OV);

    double getOV();

    static double get_transFee();

    double withdraw(Bank& bank, double draw, std::string Pas);

    void displayAccountInfo(std::string Pas);

    std::string gettype();

    void getinfo(std::unordered_map<std::string, std::string>& info);

    friend void Edit_transfee(double New_ts);
};
