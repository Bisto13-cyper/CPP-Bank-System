#include "User.hpp"

std::unordered_set<int> User::IDS;

int User::genrateuniqe_id() {
    int newId;
    do {
        newId = ID.randomInt(0, 1000000);
    } while (IDS.count(newId));
    IDS.insert(newId);
    return newId;
}

void User::resetpas(std::string OldPas, const std::string& NewPas) {
    if (OldPas != Password) throw InvalidPasException();
    if (!Bisto::logger::isStrongPassword(NewPas)) throw WeakPasswordException();
    Password = NewPas;
}

void User::resetpas(long long Nat, int I, const std::string& NewPas) {
    if (I != U_Id || Nat != National_Number) throw InvalidPasException();
    if (!Bisto::logger::isStrongPassword(NewPas)) throw WeakPasswordException();
    Password = NewPas;
}

void User::getInfo(std::unordered_map<std::string, std::string>& info) {
    info["Name"] = Name;
    info["Gamil"] = Gamil;
    info["National_Number"] = std::to_string(National_Number);
    info["Id"] = std::to_string(U_Id);
}

std::string User::getName() { return Name; }

User::~User() {
    IDS.erase(U_Id);
    Bank::minus_User();
}
