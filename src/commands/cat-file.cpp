#include<bits/stdc++.h>
#include "../components/object-db.h"
#include "cat-file.h"
using namespace std;

void catFileCommand(int argc, char* argv[]){
    if(argc < 4){
        cerr << "usage : vcx cat-file [-e | -p | -t | -s] <object>" << endl;
        return;
    }
    string hash = string(argv[3]);
    string flag = string(argv[2]);
    if(argc == 4 && !hash.empty()){
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
}