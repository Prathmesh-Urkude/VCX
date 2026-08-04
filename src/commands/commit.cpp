#include <bits/stdc++.h>
#include "commands/commit.h"
using namespace std;
#include "core/Repository.h"
#include "core/TreeBuilder.h"
#include "objects/Commit.h"

int CommitCommand::execute(const vector<string>& args)
{
    if (args.size() < 1){
        cerr << "usage: vcx commit -m <message>" << endl;
        return 1;
    }
    if (string(args[0]) == "-m"){
        if (args.size() < 2 || string(args[1]).empty()){
            cerr << "Commit message cannot be empty" << endl;
            return 1;
        }
        else{
            Repository repo;
            TreeBuilder builder(repo);

            string treeHash = builder.build();
            vector<string> parents;
            string current = repo.currentCommit();

            if (!current.empty()) parents.push_back(current);

            if (!parents.empty() && !repo.isTreeChanged(treeHash)) throw runtime_error("nothing to commit");    

            string author = "Perserix";
            string authorEmail = "Perserix@mail.com";
            string committer = author;
            string committerEmail = authorEmail;
            string message = args[1];

            Commit commit(
                treeHash,
                parents,
                author,
                authorEmail,
                committer,
                committerEmail,
                message             
            );
            string commitHash = repo.hashObject(commit, true);
            repo.updateHead(commitHash);
        }
    }
    return 0;
}