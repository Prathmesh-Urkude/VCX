#include <bits/stdc++.h>
#include "commands/log.h"
#include "core/Repository.h"
using namespace std;

int LogCommand::execute(const vector<string>& args){
    if(args.size() < 1){
        Repository repo;
        string hash = repo.currentCommit();

        while(!hash.empty()){
            unique_ptr<Commit> commit = repo.readCommit(hash);
            cout << "commit " << hash << endl;
            cout << "Author: " << commit->getAuthor() << " <" << commit->getAuthorEmail() << ">" << endl;
            cout << "Date: " << commit->getTimestamp() << " " << commit->getTimezone() << endl;
            cout << endl;
            cout << "\t" << commit->getMessage() << endl;
            cout << endl;

            if(commit->getParentHash().empty()) break;
            hash = commit->getParentHash()[0];
        }
        return 0;
    }
    return 1;
}