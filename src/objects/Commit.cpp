#include<bits/stdc++.h>
using namespace std;
#include "objects/Commit.h"

string Commit::getType() const {
    return "commit";
}

string Commit::serialize() const {
    ostringstream ss;

    ss << "tree " << treeHash << "\n";
    for(const auto& hash : parentHash){
        ss << "parent " << hash << "\n";
    }
    ss << "author " << authorName << " <" << authorEmail << "> " << timestamp << " +" << timezone << "\n";
    ss << "committer " << committerName << " <" << committerEmail << "> " << timestamp << " +" << timezone << "\n";
    ss << "\n" << message << "\n";  

    return ss.str();
}

Commit::Commit(const string& treeHash, const vector<string>& parentHash, const string& authorName, const string& authorEmail, const string& committerName, const string& committerEmail, const string& message){
    this->treeHash = treeHash;
    for(const auto& hash : parentHash){
        this->parentHash.push_back(hash);
    }
    this->authorName = authorName;
    this->authorEmail = authorEmail;
    this->committerName = committerName;
    this->committerEmail = committerEmail;
    this->message = message;
    this->timestamp = static_cast<uint64_t>(time(nullptr));
    this->timezone = "+0530"; // Default Indian timezone
}

Commit::Commit(const std::string& serialized){
    deserialize(serialized);
}

void Commit::deserialize(const string& serialized){
    istringstream ss(serialized);
    string line;

    while(getline(ss, line)){
        if(line.empty()) break;

        size_t spacePos = line.find(' ');
        if(spacePos == string::npos) throw runtime_error("Invalid commit format");

        string key = line.substr(0, spacePos);
        string value = line.substr(spacePos + 1);

        if("tree" == key) treeHash = value;
        else if("parent" == key){
            parentHash.push_back(value);
        }
        else if("author" == key){
            size_t start = value.find('<');
            size_t end = value.find('>');
            if(start == string::npos || end == string::npos || start >= end) throw runtime_error("Invalid author format");
            authorName = value.substr(0, start - 1);
            authorEmail = value.substr(start + 1, end - start - 1);

            istringstream iss(value.substr(end + 1));

            iss >> timestamp;
            iss >> timezone;

            if (!iss) throw std::runtime_error("Invalid author timestamp/timezone");
        }
        else if("committer" == key){
            size_t start = value.find('<');
            size_t end = value.find('>');
            if(start == string::npos || end == string::npos || start >= end) throw runtime_error("Invalid committer format");
            committerName = value.substr(0, start - 1);
            committerEmail = value.substr(start + 1, end - start - 1);
        }
        else throw runtime_error("Unknown commit field: " + key);
    }

    ostringstream msg;
    while(getline(ss, line)){
        if(!msg.str().empty()) msg << '\n';
        msg << line;
    }
    message = msg.str();
}