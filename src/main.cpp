#include<bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]){
    if(argc == 1){
        cerr << "usage: vcx <command> [options]" << endl;
        return 1;
    }

    if("init" == string(argv[1])){
        cout << "Initialized empty vcx repository in ./.vcx/" << endl;
    }
    else if("add" == string(argv[1])){
        if(argc < 3){
            cerr << "usage: vcx add <file>" << endl;
            return 1;
        }
        cout << "Added " << argv[2] << " to staging area" << endl;
    }
    else if("commit" == string(argv[1])){
        if(argc < 3){
            cerr << "usage: vcx commit -m <message>" << endl;
            return 1;
        }
        if(string(argv[2]) == "-m"){
            if(string(argv[3]).empty()){
                cerr << "Commit message cannot be empty" << endl;
                return 1;
            }
            else {
                cout << "Committed with message: " << argv[3] << endl;
            }
        }
    }
    else{
        cerr << "Unknown command: " << argv[1] << endl;
        return 1;
    }

    return 0;
}