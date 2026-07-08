#include<bits/stdc++.h>
using namespace std;
#include "commands/init.h"
#include "commands/commands.h"
#include<filesystem>
#include<fstream>
using namespace std::filesystem;
#include "core/Repository.h"

int InitCommand::execute(const vector<string>&) {
    Repository repo(".");

    if(repo.exists()){
        cout << "vcx repository already exists in this directory." << endl;
        cout << "do you want to reinitialize the repository, (y/n)? : ";

        char choice;
        cin >> choice;
        choice = tolower(choice);
        if('y' == choice){
            repo.remove();
            cout << "Removed existing vcx repository." << endl;
        } 
        else return 0;
    }

    repo.init();

    cout << "Initialized empty .vcx repository" << endl;
    return 0;
}