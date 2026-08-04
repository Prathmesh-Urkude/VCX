#include<bits/stdc++.h>
using namespace std;
#include "core/TreeBuilder.h"
#include "core/Repository.h"
#include "core/Index.h"
#include "objects/Tree.h"

TreeBuilder::TreeBuilder(Repository& repo) : repo(repo) {}

string TreeBuilder::build(){
    Index index = repo.loadIndex();
    const vector<IndexEntry>& entries = index.getEntries();

    auto it = entries.begin();
    return buildNode("", it, entries.end());
}

string TreeBuilder::buildNode(const string& currentPath, vector<IndexEntry>::const_iterator& it, const vector<IndexEntry>::const_iterator end){
    vector<TreeEntry> treeEntries;

    while(it != end){
        if(!belongsToCurrentDir(currentPath, it->filePath)) break;
        
        string relativePath = currentPath.empty() ? it->filePath : it->filePath.substr(currentPath.size() + 1);

        size_t slash = relativePath.find('/');
        if(slash != string::npos){
            string dir = relativePath.substr(0, slash);
            string childDir = currentPath.empty() ? dir : currentPath + "/" + dir;
            treeEntries.push_back({
                "040000",
                dir,
                buildNode(childDir, it, end)
            });
        }
        else {
            treeEntries.push_back({
                it->mode,
                relativePath,
                it->blobhash
            });

            ++it;
        } 
    }

    Tree tree(treeEntries);
    return repo.hashObject(tree, true);
}

bool TreeBuilder::belongsToCurrentDir(const string& currentDir, const string& path) const {
    if(currentDir.empty()) return true;
    return path.rfind(currentDir + "/", 0) == 0;
}