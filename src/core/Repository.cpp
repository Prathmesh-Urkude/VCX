#include<bits/stdc++.h>
using namespace std;
#include "core/Repository.h"
#include <filesystem>
using namespace std::filesystem;
#include "objects/Blob.h"
#include "core/ObjectStore.h"
#include "utils/FileUtils.h"

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
    head << "ref: refs/heads/main\n";
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

string Repository::hashObject(const string& path, bool write){
    Blob blob(FileUtils::readFile(path));
    if(write) writeObject(blob);
    return blob.getHash();
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