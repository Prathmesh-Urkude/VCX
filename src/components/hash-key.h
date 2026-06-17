#pragma once
#include<bits/stdc++.h>
using namespace std;

string sha256(string& data);
string getPayload(string type, string& content);
string HashKey(string file, bool write);
bool isValidHash(const string& hash);