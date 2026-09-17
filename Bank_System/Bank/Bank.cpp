#include "Bank.hpp"
#include "BankExcepsion.hpp"
#include "../Users/Customer.hpp"
#include "../Users/Employee.hpp"
#include "../Users/Admin.hpp"
#include "../Accounts/Account.hpp"
#include "../Accounts/CheckingAccount.hpp"
#include "../Accounts/SavingAccount.hpp"
#include <stdexcept>

using UserInfo = std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;

Bank::Bank(std::string BN, double M, std::string B_P) : Bank_Password(B_P), Bank_Name(BN), Money(M) {}

Bank::~Bank() {
    Customers.clear();
    Employees.clear();
    Admins.clear();
}

int Bank::Num_Of_Accounts = 0;
int Bank::Num_Of_Users = 0;

std::string Bank::getName() { return Bank_Name; }

void Bank::addAdmin(bool HighAccess, std::string N, std::string G, std::string P, std::string J, std::string R, long long NI, double S) {
    if (!HighAccess)
        throw AccessRequired();

    auto Adm = std::make_unique<Admin>(N, G, J, P, R, NI, S);
    Adm->Accesble(true);

    int newId = Adm->getId(P);
    Admins[newId] = std::move(Adm);
}

void Bank::addCustomer(bool Access, std::string Name, std::string Gamil, std::string Type, std::string UserPas, long long National, std::string AccountPas, double Balance, double Onther) {
    if (!Access)
        throw AccessRequired();

    auto Cus = std::make_unique<Customer>(Name, Gamil, UserPas, National);

    std::string upperType = Bisto::strings::Upper(Type);
    if (upperType == "SAVING_ACCOUNT")
        Cus->makeSA(AccountPas, Balance, Onther);
    else if (upperType == "CHECKING_ACCOUNT")
        Cus->makeCA(AccountPas, Balance, Onther);
    else
        throw FailedSignUp();

    int newId = Cus->getId(UserPas);
    Customers[newId] = std::move(Cus);
}

void Bank::addEmployee(bool HighAccess, bool isAccess, std::string N, std::string G, std::string P, std::string J, std::string R, long long NI, double S) {
    if (!HighAccess)
        throw AccessRequired();

    auto Emp = std::make_unique<Employee>(N, G, P, J, R, NI, S);
    Emp->Accesble(isAccess);

    int newId = Emp->getId(P);
    Employees[newId] = std::move(Emp);
}

void Bank::delAdmin(bool HighAccess, int id, long long Natiol_Number) {
    if (!HighAccess)
        throw AccessRequired();

    auto it = Admins.find(id);
    if (it == Admins.end())
        throw UserNotFound();

    std::unordered_map<std::string, std::string> info;
    it->second->getInfo(info);

    if (info["National_Number"] != std::to_string(Natiol_Number))
        throw FailedSignUp();

    Admins.erase(it);
}

std::string Bank::delCustomer(bool Acces, int id, long long Natiol_Number, std::string reason) {
    if (!Acces)
        throw AccessRequired();

    auto it = Customers.find(id);
    if (it == Customers.end())
        throw UserNotFound();

    std::unordered_map<std::string, std::string> info;
    it->second->getInfo(info);

    if (info["National_Number"] != std::to_string(Natiol_Number))
        throw FailedSignUp();

    Customers.erase(it);

    return reason;
}

void Bank::delEmployee(bool HighAccess, int employeeId, long long National_Number) {
    if (!HighAccess)
        throw AccessRequired();

    auto it = Employees.find(employeeId);
    if (it == Employees.end())
        throw UserNotFound();

    std::unordered_map<std::string, std::string> info;
    it->second->getInfo(info);

    if (info["National_Number"] != std::to_string(National_Number))
        throw FailedSignUp();

    Employees.erase(it);
}

Customer* Bank::getCustomer(int customerId) {
    auto it = Customers.find(customerId);
    if (it != Customers.end())
        return it->second.get();
    throw UserNotFound();
}

Employee* Bank::getEmployee(int employeeId) {
    auto it = Employees.find(employeeId);
    if (it != Employees.end())
        return it->second.get();
    throw UserNotFound();
}

Admin* Bank::getAdmin(int Id) {
    auto it = Admins.find(Id);
    if (it != Admins.end())
        return it->second.get();
    throw UserNotFound();
}

UserInfo Bank::getCustomers(std::string BankPas) {
    if (BankPas != Bank_Password)
        throw FailedSignUp();

    UserInfo Cus;
    for (auto& it : Customers) {
        std::unordered_map<std::string, std::string> data;
        it.second->getInfo(data);
        Cus[it.second->getName()] = data;
    }
    return Cus;
}

UserInfo Bank::getEmployees(std::string BankPas) {
    if (BankPas != Bank_Password)
        throw FailedSignUp();

    UserInfo Emp;
    for (auto& it : Employees) {
        std::unordered_map<std::string, std::string> data;
        it.second->getInfo(data);
        Emp[it.second->getName()] = data;
    }
    return Emp;
}

UserInfo Bank::getAdmins(std::string BankPas) {
    if (BankPas != Bank_Password)
        throw FailedSignUp();

    UserInfo Adm;
    for (auto& it : Admins) {
        std::unordered_map<std::string, std::string> data;
        it.second->getInfo(data);
        Adm[it.second->getName()] = data;
    }
    return Adm;
}

void Bank::addMoney(double Add) { Money += Add; }

void Bank::earseMoney(double Reomve) { Money -= Reomve; }

double Bank::getMoney(std::string BP) {
    if (BP != Bank_Password)
        throw FailedSignUp();
    return Money;
}

bool Bank::transfer(Account* From, Account* To, double Money) {
    if (From == nullptr || To == nullptr)
        throw AccountNotFound();

    try {
        From->withdraw(*this, Money, From->PaswithhighAcces(this));
    }
    catch (const BankException&) {
        return false;
    }

    To->deposit(*this, Money);
    return true;
}

void Edit_transfee(double New_tf) {
    if (New_tf <= 0)
        throw std::invalid_argument("Transfer fee can't be negative or zero.");

    Checking_Account::transFee = New_tf;
}

void Bank::Edit_transfe(double New_tf) {
    Edit_transfee(New_tf);
}

void Edit_Current_Interest_Rate(double New_CIR) {
    if (New_CIR <= 0)
        throw std::invalid_argument("Interest rate can't be negative or zero.");

    Saving_Account::Current_Interest_Rate = New_CIR;
}

void Bank::Edit_Cur_Inter_Rate(double New_CIR) {
    Edit_Current_Interest_Rate(New_CIR);
}

double Bank::get_transFee() {
    return Checking_Account::get_transFee();
}

double Bank::get_CIR() {
    return Saving_Account::get_Current_Interest_Rate();
}

void Bank::plus_Account() { Num_Of_Accounts++; }

void Bank::minus_Account() { Num_Of_Accounts--; }

int Bank::get_Num_Of_Accounts(bool HighAccess) {
    if (!HighAccess)
        throw AccessRequired();
    return Num_Of_Accounts;
}

void Bank::plus_User() { Num_Of_Users++; }

void Bank::minus_User() { Num_Of_Users--; }

int Bank::get_Num_Of_Users(bool HighAccess) {
    if (!HighAccess)
        throw AccessRequired();
    return Num_Of_Users;
}

void Bank::colling_Acc(int User_Id, int Acc_Id) {
    auto User = getCustomer(User_Id);
    auto Base_Acc = User->getaccount(Acc_Id);

    if (Base_Acc == nullptr)
        throw AccountNotFound();

    auto Acc = dynamic_cast<Checking_Account*>(Base_Acc);
    if (Acc == nullptr)
        throw AccountNotFound();

    if (Acc->is_cooled())
        throw WrongProcess();

    Acc->clooAc();
}

void Bank::un_colling_Acc(int User_Id, int Acc_Id) {
    auto User = getCustomer(User_Id);
    auto Base_Acc = User->getaccount(Acc_Id);

    if (Base_Acc == nullptr)
        throw AccountNotFound();

    auto Acc = dynamic_cast<Checking_Account*>(Base_Acc);
    if (Acc == nullptr)
        throw AccountNotFound();

    if (!Acc->is_cooled())
        throw WrongProcess();

    Acc->clooAc();
}

Account* Bank::getAccount(int User_Id, int Ac_Id) {
    auto Us = getCustomer(User_Id);
    Account* acc = Us->getaccount(Ac_Id);
    if (acc == nullptr)
        throw AccountNotFound();
    return acc;
}

void Bank::give_Access(int Id) {
    auto it = Employees.find(Id);
    if (it == Employees.end())
        throw UserNotFound();
    if (it->second->is_Access())
        throw WrongProcess();
    it->second->Accesble(true);
}

void Bank::remove_Access(int Id) {
    auto it = Employees.find(Id);
    if (it == Employees.end())
        throw UserNotFound();
    if (!it->second->is_Access())
        throw WrongProcess();
    it->second->Accesble(false);
}
