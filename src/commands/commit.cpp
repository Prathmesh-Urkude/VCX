#include <bits/stdc++.h>
#include "commit.h"
using namespace std;

int CommitCommand::execute(const vector<string>& args)
{
    if (args.size() < 1){
        cerr << "usage: vcx commit -m <message>" << endl;
        return 1;
    }
    if (string(args[0]) == "-m"){
        if (args.size() < 2 || string(args[1]).empty()){
            cerr << "Commit message cannot be empty" << endl;
            return 1;
        }
        else{
            cout << "Committed with message: " << args[1] << endl;
        }
    }
    return 0;
}