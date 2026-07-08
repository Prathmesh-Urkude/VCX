#pragma once

#include "commands.h"
using namespace std;

class CatFileCommand : public Commands {
public:
    int execute(const vector<string>& args) override;
};