#include<bits/stdc++.h>
#include "commands/add.h"
using namespace std;
#include "core/Repository.h"
#include "utils/FileUtils.h"
#include<filesystem>
using namespace std::filesystem;

int AddCommand::execute(const vector<string>& args){
    if(args.size() < 1){
        cerr << "usage: vcx add <file>" << endl;
        return 1;
    }
    
    Repository repo;
    Index index = repo.loadIndex();
    for(const string& path : args){
        if(path == "." || FileUtils::validDirPath(path)){
            auto files = repo.fileList(path);
            for(const auto& file : files) {
                stageFile(index, file, repo);
            }
        }
        else if(FileUtils::validFilePath(path)){
            stageFile(index, path, repo);
        }
    }
    repo.saveIndex(index);
    return 0;
}

void AddCommand::stageFile(Index& index, const string& path, Repository& repo){
    IndexEntry entry;
    entry.filePath = path;
    entry.blobhash = repo.hashFile(path, true);
    entry.mode = FileUtils::fileMode(path);
    entry.size = FileUtils::fileSize(path);
    entry.timestamp = FileUtils::lastModified(path);

    index.add(entry);
}