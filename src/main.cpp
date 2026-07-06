#include<bits/stdc++.h>
#include "commands/init.h"
#include "commands/add.h"
#include "commands/commit.h"
#include "commands/hash-object.h"
#include "commands/cat-file.h"
#include "commands/commands.h"
using namespace std;

int main(int argc, char* argv[]){
    if(argc == 1){
        cerr << "usage: vcx <command> [options]" << endl;
        return 1;
    }

    unordered_map<string, unique_ptr<Commands>> commands;
    commands["init"] = make_unique<InitCommand>();
    commands["add"] = make_unique<AddCommand>();
    commands["commit"] = make_unique<CommitCommand>();
    commands["hash-object"] = make_unique<HashObjectCommand>();
    commands["cat-file"] = make_unique<CatFileCommand>();

    string command = argv[1];
    auto it = commands.find(command);

    if(it != commands.end()){
        vector<string> args(argv + 2, argv + argc);
        return it->second->execute(args);
    }
    
    cerr << "Unknown command: " << argv[1] << endl;
    return 1;
}