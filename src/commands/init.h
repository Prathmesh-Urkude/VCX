#pragma once

#include "commands.h"
using namespace std;

class InitCommand : public Commands {
public:
    int execute(const vector<string>& args) override;
};