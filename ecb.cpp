#include "sdes.cpp"
using namespace std;

class ECB{
public:

    BlockCypher* blockCypher;

    ECB(BlockCypher* blockCypher_): blockCypher(blockCypher_) {}

    string encrypt(string plainText) {
        assert((int)plainText.size() % blockCypher->BLOCK_SIZE == 0);
        string result = "";

        // just encript every block
        for(int i = 0; i < (int)plainText.size(); i += blockCypher->BLOCK_SIZE) {
            result += blockCypher->encrypt(plainText.substr(i, blockCypher->BLOCK_SIZE));
        }

        return result;
    }

    string decrypt(string cipherText) {
        assert((int)cipherText.size() % blockCypher->BLOCK_SIZE == 0);
        string result = "";

        // just decrypt every block
        for(int i = 0; i < (int)cipherText.size(); i += blockCypher->BLOCK_SIZE) {
            result += blockCypher->decrypt(cipherText.substr(i, blockCypher->BLOCK_SIZE));
        }

        return result;
    }

};