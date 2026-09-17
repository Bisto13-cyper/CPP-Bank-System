#pragma once
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "../helper/bisto.h"
#include "../Bank/BankExcepsion.hpp"
#include "../Bank/Bank.hpp"

// Customer, Employee, Admin
class User {
private:
    Bisto::randoms ID;
    static std::unordered_set<int> IDS;
    int genrateuniqe_id();

protected:
    std::string Password;
    std::string Name;
    std::string Gamil;
    long long National_Number;
    int U_Id;

public:
    User(std::string N, std::string G, long long NI)
        : Password("0000"), Name(N), Gamil(G), National_Number(NI) {
        U_Id = genrateuniqe_id();
        Bank::plus_User();
    }

    User(std::string N, std::string G, std::string P, long long NI)
        : Password(P), Name(N), Gamil(G), National_Number(NI) {
        U_Id = genrateuniqe_id();
        Bank::plus_User();
    }

    User(const User&) = delete;
    User& operator=(const User&) = delete;

    int getId(std::string Pas) {
        if (Pas != Password)
            throw InvalidPasException();
        return U_Id;
    }

    void resetpas(std::string OldPas, const std::string& NewPas);

    void resetpas(long long Nat, int I, const std::string& NewPas);

    std::string getName();

    virtual void getInfo(std::unordered_map<std::string, std::string>& Info);

    virtual ~User();
};
