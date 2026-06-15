#pragma once
#include<bits/stdc++.h>
using namespace std;

bool validFilePath(string filePath);
string readFile(const string& filePath);
void createObject(string& shaKey, string& payload);
string compressData(const string& input);
string decompressData(const string& input);