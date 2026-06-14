#include <bits/stdc++.h>
#include "commit.h"
using namespace std;

void commitCommand(int argc, char *argv[])
{
    if (argc < 3){
        cerr << "usage: vcx commit -m <message>" << endl;
        return;
    }
    if (string(argv[2]) == "-m"){
        if (argc < 4 ||string(argv[3]).empty()){
            cerr << "Commit message cannot be empty" << endl;
            return;
        }
        else{
            cout << "Committed with message: " << argv[3] << endl;
        }
    }
}