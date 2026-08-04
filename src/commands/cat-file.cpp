#include<bits/stdc++.h>
#include "commands/cat-file.h"
#include "core/Repository.h"
#include "objects/Tree.h"
using namespace std;

int CatFileCommand::execute(const vector<string>& args){
    if(args.size() != 2){
        cerr << "usage : vcx cat-file [-e | -p | -t | -s] <object>" << endl;
        return 1;
    }

    string flag = string(args[0]);
    string hash = string(args[1]);

    Repository repo;
    if("-e" == flag){
        cout << boolalpha << repo.objectExists(hash) << '\n';
        return 0;
    }

    auto object = repo.readObject(hash);
    if("-p" == flag){
        if (object->getType() == "tree") {
            auto* tree = dynamic_cast<Tree*>(object.get());

            for (const auto& entry : tree->getEntries()) {
                cout << entry.mode << " "
                    << entry.name << " "
                    << entry.hash << '\n';
            }
        }
        else {
            cout << object->serialize() << endl;
        }
    }
    else if("-t" == flag){
        cout << object->getType() << endl;
    }
    else if("-s" == flag){
        cout << object->serialize().size() << endl;
    }
    
    return 0;
}