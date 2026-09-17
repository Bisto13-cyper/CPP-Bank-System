#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include "../helper/bisto.h"

class Customer;
class Employee;
class Admin;
class Account;

class Bank {
private:
    std::unordered_map<int, std::unique_ptr<Customer>> Customers;
    std::unordered_map<int, std::unique_ptr<Employee>> Employees;
    std::unordered_map<int, std::unique_ptr<Admin>> Admins;

    std::string Bank_Password;
    std::string Bank_Name;
    double Money = 0;

    static int Num_Of_Users;
    static int Num_Of_Accounts;

    using UserInfo = std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;

public:
    Bank(std::string BN, double M, std::string B_P);

    std::string getName();

    void addAdmin(bool HighAccess, std::string Name, std::string Gamil, std::string Password, std::string Jop, std::string Rank, long long National, double Salary);

    void addCustomer(bool Access, std::string Name, std::string Gamil, std::string Type, std::string UserPas, long long National, std::string AccountPas, double Balance, double Onther);

    void addEmployee(bool HighAccess, bool isAcces, std::string Name, std::string Gamil, std::string Password, std::string Jop, std::string Rank, long long National, double Salary);

    void delAdmin(bool HighAccess, int id, long long Natiol_Number);

    std::string delCustomer(bool Access, int id, long long Natiol_Number, std::string reason);

    void delEmployee(bool HighAccess, int Id, long long Natiol_Number);

    Admin* getAdmin(int Id);

    Customer* getCustomer(int Id);

    Employee* getEmployee(int Id);

    Account* getAccount(int User_Id, int Ac_Id);

    UserInfo getCustomers(std::string BankPas);

    UserInfo getEmployees(std::string BankPas);

    UserInfo getAdmins(std::string BankPas);

    bool transfer(Account* From, Account* To, double Money);

    void addMoney(double Add);

    void earseMoney(double Reomve);

    double getMoney(std::string BankPas);

    void Edit_transfe(double New_tf);

    double get_transFee();

    void Edit_Cur_Inter_Rate(double New_CIR);

    double get_CIR();

    static void plus_Account();

    static void minus_Account();

    int get_Num_Of_Accounts(bool HighAccess);

    static void plus_User();

    static void minus_User();

    int get_Num_Of_Users(bool HighAccess);

    void colling_Acc(int User_Id, int Acc_Id);

    void un_colling_Acc(int User_Id, int Acc_Id);

    void give_Access(int Id);

    void remove_Access(int Id);

    virtual ~Bank();
};
