#include<bits/stdc++.h>
using namespace std;
#include "objects/Blob.h"

Blob::Blob(const std::string& data) : data(data) {}

string Blob::getType() const {
    return "blob";
}

string Blob::serialize() const {
    return data;
}