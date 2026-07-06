#include<bits/stdc++.h>
using namespace std;
#include "Tree.h"
#include "../utils/Hash.h"

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