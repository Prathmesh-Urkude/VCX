#include<bits/stdc++.h>
#include "commands/hash-object.h"
#include "utils/FileUtils.h"
#include "objects/Blob.h"
#include "core/ObjectStore.h"
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
            string filePath = args[0];
            Blob blob(FileUtils::readFile(filePath));
            cout << blob.getHash() << endl;
            return 0;
        }
    }
    else if(args.size() == 2){
        if("-w" == string(args[0])){
            string filePath = args[1];
            Blob blob(FileUtils::readFile(filePath));
            ObjectStore store;
            cout << store.write(blob) << endl;
            return 0;
        }
    }
    return 1;
}