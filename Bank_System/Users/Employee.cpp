#include "Employee.hpp"
#include "../Bank/Bank.hpp"
#include "Customer.hpp"
#include "../Bank/BankExcepsion.hpp"
#include "../Accounts/Account.hpp"

void Employee::getInfo(std::unordered_map<std::string, std::string>& Info) {
    User::getInfo(Info);
    Info["IsHighAccess"] = Access ? "Yes" : "No";
    Info["Jop"] = Jop;
    Info["Salary"] = std::to_string(Salary);
    Info["Rank"] = Rank;
}

bool Employee::is_Access() { return Access; }

double Employee::getSalary() { return Salary; }

std::string Employee::getJop() { return Jop; }

std::string Employee::getRank() { return Rank; }

std::string Employee::addCustomer(Bank* BANK, std::string Name, std::string Gamil, std::string AccountType,
                                   std::string UserPas, long long National_Number, std::string AccPas,
                                   double StartBalance, double LimitOrODL) {
    if (!Access)
        throw AccessRequired();

    try {
        BANK->addCustomer(Access, Name, Gamil, AccountType, UserPas, National_Number, AccPas, StartBalance, LimitOrODL);
    }
    catch (const FailedSignUp&) {
        return "The Type Of Account Is wrong type\n";
    }

    return "Customer Added!";
}

void Employee::addAc(Bank& bank, int userid, std::string type, std::string AcPas, double FirstBalance, double Other) {
    if (!Access)
        throw AccessRequired();

    auto mycus = bank.getCustomer(userid);

    type = Bisto::strings::Upper(type);

    if (type == "SAVING_ACCOUNT")
        mycus->makeSA(AcPas, FirstBalance, Other);
    else if (type == "CHECKING_ACCOUNT")
        mycus->makeCA(AcPas, FirstBalance, Other);
    else
        throw FailedSignUp();
}

bool Employee::delAc(Bank& bank, int userid, int Acid, int transid, int Actransid, std::string Accpas, std::string UPas) {
    if (!Access)
        throw AccessRequired();

    auto mycus = bank.getCustomer(userid);
    auto mycus2 = bank.getCustomer(transid);

    auto tranAc = mycus2->getaccount(Actransid);

    if (tranAc == nullptr)
        throw AccountNotFound();

    try {
        mycus->delAc(bank, Acid, true, tranAc, Accpas, UPas);
    }
    catch (const BankException&) {
        return false;
    }

    return true;
}

std::unordered_map<std::string, std::string> Employee::getdata(Bank& bank, int CusId) {
    if (!Access)
        throw AccessRequired();

    auto it = bank.getCustomer(CusId);
    std::unordered_map<std::string, std::string> data;
    it->getInfo(data);

    return data;
}

std::unordered_map<std::string, std::string> Employee::checkAcc(Bank& bank, int CusId, int Accinfo) {
    if (!Access)
        throw AccessRequired();

    auto it = bank.getCustomer(CusId);
    auto Acc = it->getaccount(Accinfo);

    if (Acc == nullptr)
        throw AccountNotFound();

    std::unordered_map<std::string, std::string> data;
    Acc->getinfo(data);

    return data;
}

int Employee::get_Num_Of_users(Bank& bank) {
    return bank.get_Num_Of_Users(Access);
}

int Employee::get_Num_Of_Accounts(Bank& bank) {
    return bank.get_Num_Of_Accounts(Access);
}

double Employee::get_CIR(Bank& bank) {
    return bank.get_CIR();
}

double Employee::get_tf(Bank& bank) {
    return bank.get_transFee();
}

std::string Employee::colling_Acc(Bank& bank, int User_Id, int Acc_Id, std::string reason) {
    if (!Access)
        throw AccessRequired();
    bank.colling_Acc(User_Id, Acc_Id);
    return reason;
}

std::string Employee::un_colling_Acc(Bank& bank, int User_Id, int Acc_Id, std::string reason) {
    if (!Access)
        throw AccessRequired();
    bank.un_colling_Acc(User_Id, Acc_Id);
    return reason;
}
