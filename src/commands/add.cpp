#include<bits/stdc++.h>
#include "add.h"
using namespace std;

void addCommand(int argc, char* argv[]){
    if(argc < 3){
        cerr << "usage: vcx add <file>" << endl;
        return;
    }
    cout << "Added " << argv[2] << " to staging area" << endl;
}