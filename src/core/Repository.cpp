#include<bits/stdc++.h>
using namespace std;
#include "core/Repository.h"
#include <filesystem>
using namespace std::filesystem;
#include "objects/Blob.h"
#include "core/ObjectStore.h"
#include "utils/FileUtils.h"
#include "core/Index.h"
#include "objects/Commit.h"

Repository::Repository(const string& root) : 
    rootPath(root), 
    vcxPath(root + "/.vcx"), 
    objectStore(vcxPath + "/objects") {}

bool Repository::exists() const {
    return filesystem::exists(vcxPath);
}

void Repository::remove() {
    filesystem::remove_all(vcxPath);
}

void Repository::init(){
    create_directory(vcxPath);
    create_directory(vcxPath + "/objects");
    create_directories(vcxPath + "/refs/heads/");
    create_directories(vcxPath + "/refs/tags/");

    ofstream head(vcxPath + "/HEAD");
    head << "ref: refs/heads/main";
    head.close();

    ofstream main_branch(vcxPath + "/refs/heads/main");
    main_branch.close();

    ofstream indexFile(vcxPath + "/index", ios::binary);
    indexFile.close();
}

bool Repository::isInitialized() const {
    return filesystem::exists(vcxPath) && filesystem::exists(vcxPath + "/objects") 
        && filesystem::exists(vcxPath + "/HEAD") && filesystem::exists(vcxPath + "/index");
}

//Objects
string Repository::hashFile(const string& path, bool write) {
    Blob blob(FileUtils::readFile(path));
    return hashObject(blob, write);
}

string Repository::hashObject(const Object& object, bool write){
    if(write) writeObject(object);
    return object.getHash();
}

unique_ptr<Object> Repository::readObject(const string& hash){
    if(!objectStore.exists(hash)) throw runtime_error("Object doesn't exist");
    return objectStore.read(hash);
}

void Repository::writeObject(const Object& object){
    if(!isInitialized()) throw runtime_error("Repository is not initialized");
    objectStore.write(object);
}

bool Repository::objectExists(const string& hash){
    return objectStore.exists(hash);
}

unique_ptr<Commit> Repository::readCommit(const string& treeHash){
    auto obj = readObject(treeHash);
    Commit* prevCommit = dynamic_cast<Commit*>(obj.get());
    if (!prevCommit) throw runtime_error("Object is not a commit");
    obj.release(); 
    return unique_ptr<Commit>(prevCommit);
}

bool Repository::isTreeChanged(const string& treeHash){
    string current = currentCommit();
    if (current.empty()) return true; 

    auto commit = readCommit(current);
    return commit->getTreeHash() != treeHash;
}

// Index 
Index Repository::loadIndex() const{
    Index index;
    index.load();
    return index;
}

void Repository::saveIndex(Index& index) const{
    index.Index::save();
}

vector<string> Repository::fileList(const string& path) const{
    vector<string> files;

    for(const auto& entry : recursive_directory_iterator(path, directory_options::skip_permission_denied)){
        if(!entry.is_regular_file()) continue;
        if(entry.path().string().find(".vcx") != string::npos) continue;

        files.push_back(relative(entry.path(), rootPath).string());
    }
    return files;
}

//Refs
string Repository::headRef(){
    string head = FileUtils::readFile(vcxPath + "/HEAD");
    if (head.rfind("ref: ", 0) == 0) return "/" + head.substr(5);
    return "";
}

string Repository::currentCommit(){
    return readRef(headRef());
}

void Repository::updateRef(const string& ref, const string& hash) {
    if(!refExists(ref)) throw runtime_error("commit failed");
    ofstream file(vcxPath + ref);
    file << hash;
}

string Repository::readRef(const string& ref){
    return FileUtils::readFile(vcxPath + ref);
}

bool Repository::refExists(const string& ref){
    return FileUtils::validFilePath(vcxPath + ref);
}

void Repository::updateHead(const string& hash){
    updateRef(headRef(), hash);
}