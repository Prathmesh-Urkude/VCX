#include<bits/stdc++.h>
#include "../components/hash-key.h"
#include "hash-object.h"
using namespace std;

int HashObjectCommand::execute(const vector<string>& args){
    if(args.size() < 1) {
        cerr << "usage: vcx hash-object <file-path>" << endl;
        return 1;
    }
    else if(args.size() == 1){
        if("-w" == string(args[0])){
            cerr << "usage: vcx hash-object -w <file-path>" << endl;
            return 1;
        }
        else {
            cout << HashKey(string(args[0]), false) << endl;
            return 0;
        }
    }
    else if(args.size() == 2){
        if("-w" == string(args[0])){
            cout << HashKey(string(args[1]), true) << endl;
            return 0;
        }
    }
    return 1;
}