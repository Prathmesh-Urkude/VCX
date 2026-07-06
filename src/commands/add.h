#pragma once

#include "commands.h"
using namespace std;

class AddCommand : public Commands {
public:
    int execute(const vector<string>& args) override;
};