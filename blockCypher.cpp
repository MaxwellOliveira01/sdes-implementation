#ifndef BLOCK_CYPHER_H
#define BLOCK_CYPHER_H


#include <bits/stdc++.h>
using namespace std;

class BlockCypher {
public:
    int BLOCK_SIZE;
    virtual string encrypt(string plainText) = 0;
    virtual string decrypt(string cipherText) = 0;
};


#endif