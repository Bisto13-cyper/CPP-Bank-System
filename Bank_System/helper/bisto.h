#pragma once
#include <string>



namespace Bisto {

class randoms {
public:
    int randomInt(int min, int max);
};

namespace strings {
    std::string Upper(std::string s);
}

namespace logger {
    bool isStrongPassword(const std::string& pas);
}

} // namespace Bisto
