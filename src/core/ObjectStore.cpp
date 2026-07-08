#include<bits/stdc++.h>
using namespace std;
#include "core/ObjectStore.h"
#include "utils/Hash.h"
#include "utils/FileUtils.h"
#include <zlib.h> //compile with "-lz"
#include <filesystem>
#include "objects/Blob.h"
#include "objects/Commit.h"
#include "objects/Tree.h"

ObjectStore::ObjectStore(const std::string& objectsPath) : objectsPath(objectsPath) {}

string ObjectStore::objectPath(const std::string& hash) const {
    return objectsPath + "/" + hash.substr(0, 2) + "/" + hash.substr(2);
}

string ObjectStore::write(const Object& object){
    string shaKey = object.getHash();
    string payload = object.getPayload();

    string dir = objectsPath + "/" + shaKey.substr(0, 2);
    filesystem::create_directories(dir);

    string compressedData = compress(payload);

    string filePath = dir + "/" + shaKey.substr(2);

    if(filesystem::exists(filePath)) return shaKey;

    ofstream objectFile(filePath, ios::binary);
    if (!objectFile) throw runtime_error("Failed to create object file");

    objectFile.write(compressedData.data(), compressedData.size());
    objectFile.close();

    return shaKey;
}

unique_ptr<Object> ObjectStore::read(const string& hash){
    if(!ObjectStore::exists(hash)) throw runtime_error("Object doesn't exist");

    string filePath = ObjectStore::objectPath(hash);
    string compressed = FileUtils::readFile(filePath);
    string payload =  decompress(compressed);

    size_t nullPos = payload.find('\0');
    if (nullPos == string::npos) throw runtime_error("Invalid payload format");
    string header = payload.substr(0, nullPos);
    string content = payload.substr(nullPos + 1);
    
    size_t spacePos = header.find(' ');
    if(spacePos == string::npos) throw runtime_error("Invalid header format");
    string type = header.substr(0, spacePos);

    if(header.substr(spacePos + 1) != to_string(content.size())) throw runtime_error("Content size mismatch");

    if("blob" == type){
        return make_unique<Blob>(content);
    }
    if("commit" == type){
        return make_unique<Commit>(content);
    }
    if("tree" == type){
        return make_unique<Tree>(content);
    }
    throw runtime_error("Unknown object type: " + type);
}

bool ObjectStore::exists(const string& hash){
    if(!Hash::isValid(hash)) return false;
    string filePath = ObjectStore::objectPath(hash);
    return FileUtils::validFilePath(filePath);
}

void ObjectStore::remove(const string& hash){
    cout << "Removing object with hash: " << hash << endl;
}

string ObjectStore::compress(const std::string& data) const {
    z_stream zs{};
    if (deflateInit(&zs, Z_DEFAULT_COMPRESSION) != Z_OK) throw runtime_error("deflateInit failed");

    zs.next_in = (Bytef*)data.data();
    zs.avail_in = data.size();

    char buffer[4096];
    string output;

    int ret;
    do {
        zs.next_out = reinterpret_cast<Bytef*>(buffer);
        zs.avail_out = sizeof(buffer);

        ret = deflate(&zs, Z_FINISH);
        output.append(buffer, sizeof(buffer) - zs.avail_out);
    } while (ret == Z_OK);

    deflateEnd(&zs);

    if (ret != Z_STREAM_END) throw runtime_error("deflate failed");

    return output;
}

string ObjectStore::decompress(const std::string& data) const {
    z_stream zs{};

    if (inflateInit(&zs) != Z_OK) throw runtime_error("inflateInit failed");

    zs.next_in = (Bytef*)data.data();
    zs.avail_in = data.size();

    char buffer[4096];
    string output;

    int ret;
    do {
        zs.next_out = reinterpret_cast<Bytef*>(buffer);
        zs.avail_out = sizeof(buffer);

        ret = inflate(&zs, 0);
        output.append(buffer, sizeof(buffer) - zs.avail_out);
    } while (ret == Z_OK);

    inflateEnd(&zs);

    if (ret != Z_STREAM_END) throw runtime_error("inflate failed");

    return output;
}