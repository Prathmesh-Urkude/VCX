#pragma once

#include "core/Repository.h"
#include <string>
#include <vector>

class TreeBuilder {
private:
    Repository& repo;
    std::string buildNode(const std::string& currentPath, const std::vector<IndexEntry>& entries);
public:
    explicit TreeBuilder(Repository& repo);
    std::string build();
};