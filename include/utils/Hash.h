#pragma once

#include<string>

namespace Hash {
    std::string sha256(const std::string& data);
    bool isValid(const std::string& hash);
    std::string hexToBytes(const std::string& hex);
    std::string bytesToHex(const std::string& bytes);
}