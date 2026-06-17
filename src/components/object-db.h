#pragma once
#include<bits/stdc++.h>
using namespace std;

void createObject(const string& shaKey, const string& payload);
bool checkObjectExist(const string& objectId);
string readObject(const string& objectId);
string getObjectType(const string& payload);
string getObjectSize(const string& payload);
string getObjectContent(const string& payload);