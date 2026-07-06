#include<bits/stdc++.h>
using namespace std;
#include "Hash.h"
#include "FileUtils.h"
#include<openssl/sha.h> //compile with "-lcrypto"
// #include "../components/object-db.h"

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

string Hash::HashKey(string file, bool write){
    if(FileUtils::validPath(file)){
        try{
            string content = FileUtils::readFile(string(file));
            string payload = getPayload("blob", content);
            string shaKey = Hash::sha256(payload);

            if(shaKey.empty()){
                throw runtime_error("Failed to generate hash key");
            }
            if(write){
                createObject(shaKey, payload);
            }
            return shaKey;
        }
        catch (const exception& e) {
            cerr << string(file) << ": " << e.what() << '\n';
        }
    }
    else {
        cerr << "Invalid file\n";
    }
    return "";
}

bool Hash::isValid(const string& hash){
    if(hash.length() != 64) return false;

    for(char c : hash){
        if(!isxdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

string hexToBytes(const std::string& hex){
    if(hex.length() % 2 != 0) throw invalid_argument("Hex string must have an even length");

    string res;
    res.reserve(hex.length() / 2);
    for (size_t i = 0; i < hex.size(); i += 2) {
        unsigned int value = std::stoul(hex.substr(i, 2), nullptr, 16);
        res.push_back(static_cast<char>(value));
    }
    return res;
}

string bytesToHex(const std::string& bytes){
    ostringstream ss;
    for (char c : bytes) {
        ss << hex << setw(2) << setfill('0') << static_cast<int>(static_cast<unsigned char>(c));
    }
    return ss.str();
}