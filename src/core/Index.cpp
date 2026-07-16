#include<bits/stdc++.h>
using namespace std;
#include "core/Index.h"
#include "utils/FileUtils.h"

Index::Index(){
    copy_n("VCXI", 4, header.magic);
    header.version = 1;
    header.numEntries = 0;
}

void Index::load(){
    if(!FileUtils::validFilePath(".vcx/index")) throw runtime_error("index file missing.");

    ifstream in(".vcx/index", ios::binary);
    if (!in) throw runtime_error("Failed to open index file.");

    in.read(reinterpret_cast<char*>(&header), sizeof(header));
    if(strncmp(header.magic, "VCXI", 4) != 0) throw runtime_error("invalid index file");
    if(header.version != 1) throw runtime_error("Unsupported index version.");

    entries.clear();

    for(uint32_t i = 0; i < header.numEntries; i++){
        uint32_t pathLength;
        in.read(reinterpret_cast<char*>(&pathLength), sizeof(pathLength));
        string path(pathLength, '\0');
        in.read(path.data(), pathLength);

        uint32_t blobLength;
        in.read(reinterpret_cast<char*>(&blobLength), sizeof(blobLength));
        string hash(blobLength, '\0');
        in.read(hash.data(), blobLength);

        uint64_t size;
        uint64_t timestamp;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        in.read(reinterpret_cast<char*>(&timestamp), sizeof(timestamp));

        IndexEntry entry;
        entry.filePath = move(path);
        entry.blobhash = move(hash);
        entry.size = move(size);
        entry.timestamp = move(timestamp);

        entries.push_back(move(entry));
    }
}

void Index::save(){
    if(!FileUtils::validFilePath(".vcx/index")) throw runtime_error("index file missing.");

    ofstream out(".vcx/index", ios::binary);
    if (!out) throw runtime_error("Failed to open index file.");

    header.numEntries = entries.size();
    out.write(reinterpret_cast<char*>(&header), sizeof(header));

    for(const auto& e : entries){
        uint32_t fileLength = e.filePath.size();
        out.write(reinterpret_cast<char*>(&fileLength), sizeof(fileLength));
        out.write(e.filePath.data(), fileLength);

        uint32_t blobLength = e.blobhash.size();
        out.write(reinterpret_cast<char*>(&blobLength), sizeof(blobLength));
        out.write(e.blobhash.data(), blobLength);

        out.write(reinterpret_cast<const char*>(&e.size), sizeof(e.size));
        out.write(reinterpret_cast<const char*>(&e.timestamp), sizeof(e.timestamp));
    }
    out.close();
}

void Index::add(const IndexEntry& entry){
    auto* e = Index::findEntry(entry.filePath);
    if(e != nullptr){
        *e = entry;
        return;
    }
    entries.push_back(entry);
    header.numEntries = entries.size();
}

void Index::remove(const string& filePath){
    auto* e = Index::findEntry(filePath);
    if(e == nullptr) return;

    auto it = entries.begin() + distance(entries.data(), e);
    entries.erase(it);
    header.numEntries = entries.size();
}

const vector<IndexEntry>& Index::getEntries() const {
    return entries;
}

IndexEntry* Index::findEntry(const string& filePath) const {
    for(const auto& entry : entries){
        if(filePath == entry.filePath){
            return const_cast<IndexEntry*>(&entry);
        }
    }
    return nullptr;
}