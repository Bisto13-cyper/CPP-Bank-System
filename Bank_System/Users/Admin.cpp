#include "Admin.hpp"
#include "Employee.hpp"

using UserInfo = std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;

bool Admin::addemployee(Bank& bank, std::string Name, std::string Gamil, std::string Password, std::string Jop, std::string Rank, long long National, double Salary) {
    try {
        bank.addEmployee(true, true, Name, Gamil, Password, Jop, Rank, National, Salary);
    }
    catch (const BankException&) {
        return false;
    }

    return true;
}

void Admin::delemployee(Bank& bank, int id, long long National) {
    bank.delEmployee(true, id, National);
}

void Admin::give_Access(Bank& bank, int Emp_Id) {
    bank.give_Access(Emp_Id);
}

void Admin::remove_Access(Bank& bank, int Emp_Id) {
    bank.remove_Access(Emp_Id);
}

std::unordered_map<std::string, std::string> Admin::getemployee(Bank& bank, int EmpId) {
    auto myEmp = bank.getEmployee(EmpId);

    if (myEmp == nullptr)
        throw UserNotFound();

    std::unordered_map<std::string, std::string> data;
    myEmp->getInfo(data);

    return data;
}

UserInfo Admin::getCustomers(Bank& bank, std::string BankPas) {
    return bank.getCustomers(BankPas);
}

UserInfo Admin::getEmployees(Bank& bank, std::string BankPas) {
    return bank.getEmployees(BankPas);
}

UserInfo Admin::getAdmins(Bank& bank, std::string BankPas) {
    return bank.getAdmins(BankPas);
}

void Admin::addAdmin(Bank& bank, bool HighAccess, bool isAcces, std::string Name, std::string Gamil, std::string Password, std::string Jop, std::string Rank, long long National, double Salary) {
    bank.addAdmin(HighAccess, Name, Gamil, Password, Jop, Rank, National, Salary);
}

std::unordered_map<std::string, std::string> Admin::getAdmin(Bank& bank, int id) {
    auto Adm = bank.getAdmin(id);

    std::unordered_map<std::string, std::string> Info;
    Adm->getInfo(Info);

    return Info;
}

void Admin::delAdmin(Bank& bank, int id, long long National) {
    bank.delAdmin(true, id, National);
}

double Admin::getmoney(Bank& bank, std::string BankPas) {
    return bank.getMoney(BankPas);
}

void Admin::Edit_transfee(Bank& bank, double New_tf) {
    bank.Edit_transfe(New_tf);
}

void Admin::Edit_Current_Interest_Rate(Bank& bank, double New_CIR) {
    bank.Edit_Cur_Inter_Rate(New_CIR);
}
