#include<bits/stdc++.h>
using namespace std;
#include "utils/FileUtils.h"
#include<filesystem>
using namespace std::filesystem;

bool FileUtils::validPath(const string& filePath){
    path p(filePath);
    return exists(p) && is_regular_file(p);
}

string FileUtils::readFile(const string& filePath) {
    ifstream file(filePath, ios::binary);

    if (!file) throw runtime_error("Cannot open file");

    ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}