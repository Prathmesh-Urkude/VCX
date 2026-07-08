#include<bits/stdc++.h>
using namespace std;
#include "utils/Hash.h"
#include "utils/FileUtils.h"
#include<openssl/sha.h> //compile with "-lcrypto"

string Hash::sha256(const string& data){
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256(
        reinterpret_cast<const unsigned char*>(data.data()),
        data.size(),
        hash
    );

    ostringstream oss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        oss << hex
            << setw(2)
            << setfill('0')
            << static_cast<int>(hash[i]);
    }

    return oss.str();
}

bool Hash::isValid(const string& hash){
    if(hash.length() != 64) return false;

    for(char c : hash){
        if(!isxdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

string Hash::hexToBytes(const std::string& hex){
    if(hex.length() % 2 != 0) throw invalid_argument("Hex string must have an even length");

    string res;
    res.reserve(hex.length() / 2);
    for (size_t i = 0; i < hex.size(); i += 2) {
        unsigned int value = std::stoul(hex.substr(i, 2), nullptr, 16);
        res.push_back(static_cast<char>(value));
    }
    return res;
}

string Hash::bytesToHex(const std::string& bytes){
    ostringstream ss;
    for (char c : bytes) {
        ss << hex << setw(2) << setfill('0') << static_cast<int>(static_cast<unsigned char>(c));
    }
    return ss.str();
}