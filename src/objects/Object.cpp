#include<bits/stdc++.h>
using namespace std;
#include "Object.h"
#include "../utils/Hash.h"

string Object::getPayload() const {
    string payload = getType() + " " + to_string(serialize().size());
    payload.push_back('\0');
    payload += serialize();
    return payload;
}

string Object::getHash() const {
    return Hash::sha256(getPayload());
}