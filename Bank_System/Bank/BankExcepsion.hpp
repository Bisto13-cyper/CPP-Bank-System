#pragma once

#include <stdexcept>
#include <string>

class BankException : public std::runtime_error {
public:
    explicit BankException(const std::string& message)
        : std::runtime_error(message) {}
};

class InvalidPasException : public BankException {
public:
    InvalidPasException() : BankException("Security Error: Invalid password provided!") {}
};

class InsufficientFundsException : public BankException {
public:
    InsufficientFundsException() : BankException("Transaction Error: Insufficient balance in the account!") {}
};

class WeakPasswordException : public BankException {
public:
    WeakPasswordException() : BankException("Security Error: Password must be at least 6 characters long and contain letters and digits!") {}
};

class InvalidAmountException : public BankException {
public:
    InvalidAmountException() : BankException("Transaction Error: Amount must be greater than zero!") {}
};

class ExceededLimitException : public BankException {
public:
    ExceededLimitException() : BankException("Transaction Error: Withdrawal amount exceeds the allowed account limit!") {}
};

class FaildAccess : public BankException {
public:
    FaildAccess() : BankException("This User isn't accessible! Trust Error") {}
};

class OutstandingBalance : public BankException {
public:
    OutstandingBalance() : BankException("User must return money to bank before any action!") {}
};

class FailedSignUp : public BankException {
public:
    FailedSignUp() : BankException("Error when signing up! Check your parameters.") {}
};

class AccessRequired : public BankException {
public:
    AccessRequired() : BankException("Failed! Not accessible - insufficient permissions.") {}
};

class UserNotFound : public BankException {
public:
    UserNotFound() : BankException("Failed! The user you searched for isn't here.") {}
};

class AccountNotFound : public BankException {
public:
    AccountNotFound() : BankException("Failed! The account you searched for isn't here.") {}
};

class WrongProcess : public BankException {
public:
    WrongProcess() : BankException("Failed! You're trying to make a wrong transaction, please check your action.") {}
};
