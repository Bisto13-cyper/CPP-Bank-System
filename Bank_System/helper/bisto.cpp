#include "bisto.h"
#include <random>
#include <algorithm>
#include <cctype>

namespace Bisto {

int randoms::randomInt(int min, int max) {
    static thread_local std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

namespace strings {
    std::string Upper(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(),
                        [](unsigned char c) { return std::toupper(c); });
        return s;
    }
}

namespace logger {
    bool isStrongPassword(const std::string& pas) {
        if (pas.size() < 6) return false;
        bool hasDigit = false, hasAlpha = false;
        for (unsigned char c : pas) {
            if (std::isdigit(c)) hasDigit = true;
            if (std::isalpha(c)) hasAlpha = true;
        }
        return hasDigit && hasAlpha;
    }
}

} // namespace Bisto
