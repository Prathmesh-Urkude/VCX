#pragma once

#include<string>

class Object {
public:
    virtual ~Object() = default;
    virtual std::string getType() const = 0;
    virtual std::string serialize() const = 0;
    std::string getPayload() const;
    std::string getHash() const;
};