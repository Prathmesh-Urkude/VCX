#pragma once

#include "core/Repository.h"
#include <string>
#include <vector>

class TreeBuilder {
private:
    Repository& repo;
    std::string buildNode(const std::string& currentPath, std::vector<IndexEntry>::const_iterator& it, const std::vector<IndexEntry>::const_iterator end);
    bool belongsToCurrentDir(const std::string& currentPath, const std::string& path) const; 
public:
    explicit TreeBuilder(Repository& repo);
    std::string build();
};