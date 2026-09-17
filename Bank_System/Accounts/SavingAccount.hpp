#pragma once
#include <string>
#include <unordered_map>

#include "../Bank/Bank.hpp"
#include "Account.hpp"

class Saving_Account : public Account {
private:
    static double Current_Interest_Rate;
    double Interest_Rate;
    double Limit_Rate;
    double Limits;

public:
    Saving_Account(std::string Pas, long long NaNu, double Ba)
        : Account(Pas, NaNu, Ba), Limit_Rate(0), Limits(0) {
        Interest_Rate = Current_Interest_Rate;
        Calclimits();
    }

    Saving_Account(std::string Pas, long long NaNu, double Ba, double L)
        : Account(Pas, NaNu, Ba), Limit_Rate(L), Limits(0) {
        Interest_Rate = Current_Interest_Rate;
    }

    double Monthly_applyInterest();

    double Yearly_applyInterest();

    double Calclimits();

    double resetInterest();

    double withdraw(Bank& bank, double draw, std::string Pas);

    double getinterest(std::string Pas);

    double getlimit(std::string Pas);

    double getcurrentlimit(std::string Pas);

    static double get_Current_Interest_Rate();

    std::string gettype();

    void monthlyreset(bool isInterestReset);

    void yearlyreset(bool isInterestReset);

    void displayAccountInfo(std::string Pas);

    void getinfo(std::unordered_map<std::string, std::string>& info);

    friend void Edit_Current_Interest_Rate(double New_CIR);

    ~Saving_Account() {}
};
