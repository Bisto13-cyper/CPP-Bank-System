#!/bin/bash
set -e
g++ -std=c++17 -Wall -Wextra main.cpp Bank/*.cpp Users/*.cpp Accounts/*.cpp helper/*.cpp -o BankSystem
./BankSystem
