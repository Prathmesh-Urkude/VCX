#pragma once

#include "Object.h"
#include<string>

class Commit : public Object {
private:
    std::string treeHash;
    std::vector<std::string> parentHash;

    std::string authorName;
    std::string authorEmail;

    std::string committerName;
    std::string committerEmail;

    std::string message;

    uint64_t timestamp;
    std::string timezone;

    void deserialize(const std::string& serialized);
public:
    Commit(const std::string& treeHash, const std::vector<std::string>& parentHash, const std::string& authorName, const std::string& authorEmail, const std::string& committerName, const std::string& committerEmail, const std::string& message);
    explicit Commit(const std::string& serialized);

    std::string getType() const override;
    std::string serialize() const override;
};