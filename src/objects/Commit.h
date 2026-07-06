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
    long timestamp;
public:
    std::string getType() const override;
    std::string serialize() const override;
};