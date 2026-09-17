#pragma once
#include "User.hpp"

class Bank;

class Employee : public User {
protected:
    bool Access = false;
    double Salary = 0.0;
    std::string Jop;
    std::string Rank;

public:
    Employee(std::string N, std::string G, std::string J, long long NI, double S)
        : User(N, G, NI), Salary(S), Jop(J) {}

    Employee(std::string N, std::string G, std::string P, std::string J, long long NI, double S)
        : User(N, G, P, NI), Salary(S), Jop(J) {}

    Employee(std::string N, std::string G, std::string P, std::string J, std::string R, long long NI, double S)
        : User(N, G, P, NI), Salary(S), Jop(J), Rank(R) {}

    void Accesble(bool A) { Access = A; }

    bool is_Access();

    void getInfo(std::unordered_map<std::string, std::string>& Info);

    double getSalary();

    std::string getJop();

    std::string getRank();

    std::string addCustomer(Bank* BANK, std::string Name, std::string Gamil, std::string AccountType,
                             std::string UserPas, long long National_Number, std::string AccPas,
                             double StartBalance, double LimitOrODL);

    void addAc(Bank& bank, int userid, std::string type, std::string AcPas, double FirstBalance, double Other);

    bool delAc(Bank& bank, int userid, int Acid, int transid, int Actransid, std::string Accpas, std::string UPas);

    std::unordered_map<std::string, std::string> getdata(Bank& bank, int CusId);

    std::unordered_map<std::string, std::string> checkAcc(Bank& bank, int CusId, int Accinfo);

    int get_Num_Of_users(Bank& bank);

    int get_Num_Of_Accounts(Bank& bank);

    double get_CIR(Bank& bank);

    double get_tf(Bank& bank);

    std::string colling_Acc(Bank& bank, int User_Id, int Acc_Id, std::string reason);

    std::string un_colling_Acc(Bank& bank, int User_Id, int Acc_Id, std::string reason);
};
