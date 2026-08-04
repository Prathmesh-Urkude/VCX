#include<bits/stdc++.h>
using namespace std;
#include "objects/Tree.h"
#include "utils/Hash.h"

Tree::Tree(const std::vector<TreeEntry>& entries) : entries(entries) {}

string Tree::getType() const {
    return "tree";
}

string Tree::serialize() const {
    string res;

    for(const auto& entry : entries){
        res += entry.mode;
        res += ' ';
        res += entry.name;
        res += '\0';
        res += Hash::hexToBytes(entry.hash);
    }
    return res;
}

Tree::Tree(const std::string& serialized){
    deserialize(serialized);
}

void Tree::deserialize(const string& serialized){
    entries.clear();
    size_t i = 0;
    while(i < serialized.size()){
        TreeEntry entry;

        size_t spacePos = serialized.find(' ', i);
        if(spacePos == string::npos) throw std::runtime_error("Invalid tree object");

        entry.mode = serialized.substr(i, spacePos - i);

        i = spacePos + 1;
        size_t nullPos = serialized.find('\0', i);
        if(nullPos == string::npos) throw std::runtime_error("Invalid tree object");

        entry.name = serialized.substr(i, nullPos - i);

        i = nullPos + 1;
        if(i + Hash::HASH_SIZE > serialized.size()) throw std::runtime_error("Corrupted tree object");

        entry.hash = Hash::bytesToHex(serialized.substr(i, Hash::HASH_SIZE));

        entries.push_back(entry);
        i += Hash::HASH_SIZE;
    }
}

vector<TreeEntry> Tree::getEntries() const {
    return entries;
}