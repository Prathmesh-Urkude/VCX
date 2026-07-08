#pragma once

#include<string>
#include<memory>
#include "../objects/Object.h"

class ObjectStore {
private:
    std::string objectsPath;
    std::string objectPath(const std::string& hash) const;

    std::string compress(const std::string& data) const;
    std::string decompress(const std::string& data) const;
public:
    explicit ObjectStore(const std::string& objectsPath = ".vcx/objects");

    std::string write(const Object& object);
    std::unique_ptr<Object> read(const std::string& hash);
    bool exists(const std::string& hash);
    void remove(const std::string& hash);
};