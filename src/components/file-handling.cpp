#include<bits/stdc++.h>
#include<filesystem>
#include <zlib.h> //compile with "-lz"
#include "file-handling.h"
using namespace std;
using namespace std::filesystem;

string compressData(const string& input){
    z_stream zs{};
    if (deflateInit(&zs, Z_DEFAULT_COMPRESSION) != Z_OK) throw runtime_error("deflateInit failed");

    zs.next_in = (Bytef*)input.data();
    zs.avail_in = input.size();

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

string decompressData(const string& input) {
    z_stream zs{};

    if (inflateInit(&zs) != Z_OK) throw runtime_error("inflateInit failed");

    zs.next_in = (Bytef*)input.data();
    zs.avail_in = input.size();

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

bool validFilePath(string filePath){
    path p(filePath);
    return exists(p) && is_regular_file(p);
}

string readFile(const string& filePath) {
    ifstream file(filePath, ios::binary);

    if (!file) throw runtime_error("Cannot open file");

    ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void createObject(string& shaKey, string& payload){
    string dir = ".vcx/objects/" + shaKey.substr(0, 2);
    create_directories(dir);

    string compressedPayload = compressData(payload);

    string filePath = dir + "/" + shaKey.substr(2);

    if(exists(filePath)) return;

    ofstream objectFile(filePath, ios::binary);
    if (!objectFile) throw runtime_error("Failed to create object file");

    objectFile.write(compressedPayload.data(), compressedPayload.size());
    objectFile.close();
}