#pragma once

#include "Object.h"
#include<string>

class Blob : public Object {
private:
    std::string data;
public:
    explicit Blob(const std::string& data);
    std::string getType() const override;
    std::string serialize() const override;
};