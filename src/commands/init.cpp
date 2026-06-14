#include<bits/stdc++.h>
using namespace std;
#include "init.h"
#include<filesystem>
#include <fstream>
using namespace std::filesystem;

void initCommand(){
    if(exists(".vcx")){
        cout << "vcx repository already exists in this directory." << endl;
        cout << "do you want to reinitialize the repository, (y/n)? : ";

        char choice;
        cin >> choice;
        choice = tolower(choice);
        if('y' == choice) {
            remove_all(".vcx");
            cout << "Removed existing vcx repository." << endl;
        } else return;
    }

    create_directory(".vcx");
    create_directory(".vcx/objects");
    create_directories(".vcx/refs/heads/");
    create_directories(".vcx/refs/tags/");

    ofstream head(".vcx/HEAD");
    head << "ref: refs/heads/main\n";
    head.close();

    ofstream main_branch(".vcx/refs/heads/main");
    main_branch.close();

    ofstream indexFile(".vcx/index", ios::binary);
    indexFile.close();


    cout << "Initialized empty vcx repository in ./.vcx/" << endl;
}