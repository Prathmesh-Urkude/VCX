#include<bits/stdc++.h>
#include<openssl/sha.h> //compile with "-lcrypto"
#include "file-handling.h"
#include "object-db.h"
#include "hash-key.h"
using namespace std;

string sha256(string& data){
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

string getPayload(string type, string& content){
    if("blob" == type || "commit" == type){
        string payload = type + " " + to_string(content.size());
        payload.push_back('\0');
        payload += content;
        return payload;
    }
    else if("tree" == type){
        return ""; //payload for tree Object
    }
    return "";
}

string HashKey(string file, bool write){
    if(validFilePath(file)){
        try{
            string content = readFile(string(file));
            string payload = getPayload("blob", content);
            string shaKey = sha256(payload);
            
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

bool isValidHash(const string& hash){
    if(hash.length() != 64) return false;

    for(char c : hash){
        if(!isxdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}