#pragma once

#include <string>
#include "core/ObjectStore.h"
#include "core/Index.h"
#include "objects/Commit.h"

class Repository {
private:
    std::string rootPath;
    std::string vcxPath;
    ObjectStore objectStore;
public:
    Repository(const std::string& root = ".");

    bool exists() const;
    void remove();
    void init();
    bool isInitialized() const;
    //Objects
    std::string hashFile(const std::string& path, bool write);
    std::string hashObject(const Object& object, bool write = true);
    unique_ptr<Object> readObject(const std::string& hash);
    void writeObject(const Object& object);
    bool objectExists(const std::string& hash);
    unique_ptr<Commit> readCommit(const std::string& treeHash);
    bool isTreeChanged(const std::string& treeHash);
    //Index
    Index loadIndex() const;
    void saveIndex(Index& index) const;
    std::vector<std::string> fileList(const std::string& path = ".") const;
    //Refs
    std::string headRef();
    std::string currentCommit();
    void updateRef(const std::string& ref, const std::string& hash);
    std::string readRef(const std::string& ref);
    bool refExists(const std::string& ref);
    void updateHead(const std::string& hash);
};