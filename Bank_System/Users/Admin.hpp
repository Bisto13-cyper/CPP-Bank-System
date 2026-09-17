#pragma once

#include "Employee.hpp"
#include "../Bank/Bank.hpp"

using UserInfo = std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;

class Admin : public Employee {
public:
    Admin(std::string N, std::string G, std::string J, std::string P, std::string R, long long NI, double S)
        : Employee(N, G, P, J, R, NI, S) {
        Access = true;
    }

    bool addemployee(Bank& bank, std::string Name, std::string Gamil, std::string Password, std::string Jop, std::string Rank, long long National, double Salary);

    void delemployee(Bank& bank, int id, long long National);

    void give_Access(Bank& bank, int Emp_Id);

    void remove_Access(Bank& bank, int Emp_Id);

    std::unordered_map<std::string, std::string> getemployee(Bank& bank, int EmpId);

    UserInfo getCustomers(Bank& bank, std::string BankPas);

    UserInfo getEmployees(Bank& bank, std::string BankPas);

    UserInfo getAdmins(Bank& bank, std::string BankPas);

    void addAdmin(Bank& bank, bool HighAccess, bool isAcces, std::string Name, std::string Gamil, std::string Password, std::string Jop, std::string Rank, long long National, double Salary);

    std::unordered_map<std::string, std::string> getAdmin(Bank& bank, int id);

    void delAdmin(Bank& bank, int id, long long National);

    double getmoney(Bank& bank, std::string BankPas);

    void Edit_transfee(Bank& bank, double New_tf);

    void Edit_Current_Interest_Rate(Bank& bank, double New_CIR);
};
