#pragma once

#include "Object.h"
#include<string>

struct TreeEntry {
    std::string mode;
    std::string name;
    std::string hash;
};

class Tree : public Object {
private:
    std::vector<TreeEntry> entries;
public:
    explicit Tree(const std::vector<TreeEntry>& entries);
    std::string getType() const override;
    std::string serialize() const override;
};