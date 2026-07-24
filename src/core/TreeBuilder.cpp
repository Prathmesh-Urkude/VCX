#include<bits/stdc++.h>
using namespace std;
#include "core/TreeBuilder.h"
#include "core/Repository.h"
#include "core/Index.h"
#include "objects/Tree.h"

TreeBuilder::TreeBuilder(Repository& repo) : repo(repo) {}

string TreeBuilder::build(){
    Index index = repo.loadIndex();
    vector<IndexEntry> entries = index.getEntries();
    return buildNode("", entries);
}

string TreeBuilder::buildNode(const string& currentPath, const vector<IndexEntry>& entries){
    vector<TreeEntry> treeEntries;
    set<string> subdirs;

    for(const auto& entry : entries){
        string relativePath = entry.filePath;
        if(!currentPath.empty()){
            if(entry.filePath.rfind(currentPath + "/", 0) != 0) continue;
            relativePath = entry.filePath.substr(currentPath.size() + 1);
        }

        size_t slash = relativePath.find('/');
        if(slash != string::npos){
            string subD = relativePath.substr(0, slash);

            if (!subdirs.insert(subD).second) continue;

            string childPath = currentPath.empty() ? subD : currentPath + "/" + subD;
            treeEntries.push_back({
                "040000",
                subD,
                buildNode(childPath, entries)
            });
        }
        else {
            treeEntries.push_back({
                entry.mode,
                relativePath,
                entry.blobhash
            });
        }
    }

    Tree tree(treeEntries);
    
    return repo.hashObject(tree, true);
}