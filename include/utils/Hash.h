#pragma once

#include<string>

namespace Hash {
    constexpr size_t HASH_SIZE = 32;    // bytes
    constexpr size_t HASH_HEX_SIZE = 64;    // characters

    std::string sha256(const std::string& data);
    bool isValid(const std::string& hash);
    std::string hexToBytes(const std::string& hex);
    std::string bytesToHex(const std::string& bytes);
}