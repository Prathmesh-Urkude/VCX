#include<bits/stdc++.h>
using namespace std;
#include "Commit.h"

string Commit::getType() const {
    return "commit";
}

string Commit::serialize() const {
    ostringstream ss;

    ss << "tree " << treeHash << "\n";

    if(!parentHash.empty()){
        ss << "parent " << parentHash << "\n";
    }
    ss << "author " << author << "\n";
    ss << "committer " << committer << "\n";
    ss << "timestamp " << timestamp << "\n";
    ss << "\n" << message << "\n";  

    return ss.str();
}