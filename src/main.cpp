#include<bits/stdc++.h>
#include "commands/init.h"
#include "commands/add.h"
#include "commands/commit.h"
#include "commands/hash-object.h"
#include "commands/cat-file.h"
using namespace std;

int main(int argc, char* argv[]){
    if(argc == 1){
        cerr << "usage: vcx <command> [options]" << endl;
        return 1;
    }

    if("init" == string(argv[1])){
        initCommand();
    }
    else if("add" == string(argv[1])){
        addCommand(argc, argv);
    }
    else if("commit" == string(argv[1])){
        commitCommand(argc, argv);
    }
    else if("hash-object" == string(argv[1])){
        hashObjectCommand(argc, argv);
    }
    else if("cat-file" == string(argv[1])){
        catFileCommand(argc, argv);
    }
    else{
        cerr << "Unknown command: " << argv[1] << endl;
        return 1;
    }

    return 0;
}