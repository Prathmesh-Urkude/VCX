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

Commit::Commit(const string& treeHash, const string& parentHash, const string& author, const string& message){
    this->treeHash = treeHash;
    this->parentHash = parentHash;
    this->author = author;
    this->committer = author; // For simplicity, committer is the same as author
    this->message = message;
    this->timestamp = static_cast<uint64_t>(time(nullptr));
}

Commit::Commit(const std::string& serialized){
    deserialize(serialized);
}

void Commit::deserialize(const string& serialized){

}