#include<bits/stdc++.h>
#include "../components/hash-key.h"
#include "hash-object.h"
using namespace std;

void hashObjectCommand(int argc, char* argv[]){
    if(argc < 3) {
        cerr << "usage: vcx hash-object <file-path>" << endl;
        return;
    }
    else if(argc == 3){
        if("-w" == string(argv[2])){
            cerr << "usage: vcx hash-object -w <file-path>" << endl;
            return;
        }
        else {
            cout << HashKey(string(argv[2]), false) << endl;
            return;
        }
    }
    else if(argc == 4){
        if("-w" == string(argv[2])){
            cout << HashKey(string(argv[3]), true) << endl;
            return;
        }
    }
}