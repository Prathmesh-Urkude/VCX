#pragma once

#include "commands.h"
using namespace std;
#include "core/Index.h"
#include "core/Repository.h"

class AddCommand : public Commands {
private:
    void stageFile(Index& index, const string& path, Repository& repo);
public:
    int execute(const vector<string>& args) override;
};