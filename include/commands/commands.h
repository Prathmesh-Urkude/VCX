#pragma once

#include<bits/stdc++.h>
using namespace std;

class Commands {
public:
    virtual ~Commands() = default;
    virtual int execute(const vector<string>& args) = 0;
};