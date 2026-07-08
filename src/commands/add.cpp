#include<bits/stdc++.h>
#include "commands/add.h"
using namespace std;

int AddCommand::execute(const vector<string>& args){
    if(args.size() < 1){
        cerr << "usage: vcx add <file>" << endl;
        return 1;
    }
    cout << "Added " << args[0] << " to staging area" << endl;
    return 0;
}