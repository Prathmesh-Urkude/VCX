#include<bits/stdc++.h>
using namespace std;
#include "utils/FileUtils.h"
#include<filesystem>
using namespace std::filesystem;

bool FileUtils::validFilePath(const string& filePath){
    path p(filePath);
    return exists(p) && is_regular_file(p);
}

bool FileUtils::validDirPath(const string& filePath){
    path p(filePath);
    return exists(p) && is_directory(p);
}

string FileUtils::readFile(const string& filePath) {
    ifstream file(filePath, ios::binary);

    if (!file) throw runtime_error("Cannot open file");

    ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

uint64_t FileUtils::fileSize(const std::string& path){
    return file_size(path);
}

uint64_t FileUtils::lastModified(const std::string& path){
    auto ftime = last_write_time(path);

    auto sctp = chrono::time_point_cast<std::chrono::system_clock::duration>(
        ftime - file_time_type::clock::now()
        + std::chrono::system_clock::now());

    return static_cast<uint64_t>(
        std::chrono::system_clock::to_time_t(sctp)
    );
}