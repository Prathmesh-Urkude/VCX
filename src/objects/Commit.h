#pragma once

#include "Object.h"
#include<string>

class Commit : public Object {
private:
    std::string treeHash;
    std::string parentHash;
    std::string author;
    std::string committer;
    std::string message;
    uint64_t timestamp;
    void deserialize(const std::string& serialized);
public:
    Commit(const std::string& treeHash, const std::string& parentHash, const std::string& author, const std::string& message);
    explicit Commit(const std::string& serialized);
    std::string getType() const override;
    std::string serialize() const override;
};