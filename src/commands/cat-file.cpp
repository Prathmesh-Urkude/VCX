#include<bits/stdc++.h>
#include "../components/object-db.h"
#include "cat-file.h"
using namespace std;

int CatFileCommand::execute(const vector<string>& args){
    if(args.size() < 2){
        cerr << "usage : vcx cat-file [-e | -p | -t | -s] <object>" << endl;
        return 1;
    }
    string flag = string(args[0]);
    string hash = string(args[1]);
    if(args.size() == 2 && !hash.empty()){
        if("-e" == flag){
            if(checkObjectExist(hash)){
                cout << "true" << endl;
            }
            else cout << "false" << endl;
        }
        else if("-p" == flag){
            string payload = readObject(hash);
            cout << getObjectContent(payload) << endl;
        }
        else if("-t" == flag){
            string payload = readObject(hash);
            cout << getObjectType(payload) << endl;
        }
        else if("-s" == flag){
            string payload = readObject(hash);
            cout << getObjectSize(payload) << endl;
        }
    }
    else {
        cerr << "Invalid hash object" << endl;
    }
    return 0;
}