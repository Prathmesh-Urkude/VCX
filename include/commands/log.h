#pragma once

#include "commands.h"
using namespace std;

class LogCommand : public Commands {
public:
    int execute(const vector<string>& args) override;
};