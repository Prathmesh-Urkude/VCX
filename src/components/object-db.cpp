#include<bits/stdc++.h>
#include<filesystem>
#include "file-handling.h"
#include "hash-key.h"
#include "object-db.h"
using namespace std;
using namespace std::filesystem;

void createObject(const string& shaKey, const string& payload){
    string dir = ".vcx/objects/" + shaKey.substr(0, 2);
    create_directories(dir);

    string compressedPayload = compressData(payload);

    string filePath = dir + "/" + shaKey.substr(2);

    if(exists(filePath)) return;

    ofstream objectFile(filePath, ios::binary);
    if (!objectFile) throw runtime_error("Failed to create object file");

    objectFile.write(compressedPayload.data(), compressedPayload.size());
    objectFile.close();
}

bool checkObjectExist(const string& objectId){
    if(!isValidHash(objectId)) return false;
    string filePath = ".vcx/objects/" + objectId.substr(0, 2) + "/" + objectId.substr(2);
    return validFilePath(filePath);
}

string readObject(const string& objectId){
    if(!checkObjectExist(objectId)) throw runtime_error("Object doesn't exist");

    string filePath = ".vcx/objects/" + objectId.substr(0, 2) + "/" + objectId.substr(2);
    string compressed = readFile(filePath);
    return decompressData(compressed);
}

string getObjectType(const string& payload){
    size_t pos = payload.find(' ');

    if(string::npos == pos) throw runtime_error("Invalid Object");

    return payload.substr(0, pos);
}

string getObjectSize(const string& payload){
    size_t start = payload.find(' ');
    size_t end = payload.find('\0');

    if(string::npos == start || string::npos == end || end <= start) throw runtime_error("Invalid Object");

    return payload.substr(start + 1, end - start - 1);
}

string getObjectContent(const string& payload){
    size_t pos = payload.find('\0');
    
    if(string::npos == pos) throw runtime_error("Invalid Object");

    return payload.substr(pos + 1);
}