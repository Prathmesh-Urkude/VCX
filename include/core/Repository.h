#pragma once

#include <string>
#include "core/ObjectStore.h"
#include "core/Index.h"

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

    std::string hashFile(const std::string& path, bool write);
    std::string hashObject(const Object& object, bool write = true);
    unique_ptr<Object> readObject(const std::string& hash);
    void writeObject(const Object& object);
    bool objectExists(const std::string& hash);

    Index loadIndex() const;
    void saveIndex(Index& index) const;
    std::vector<std::string> fileList(const std::string& path = ".") const;
};