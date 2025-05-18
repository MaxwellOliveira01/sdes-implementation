#include "sdes.cpp"
#include "blockCypher.cpp"
using namespace std;

class CBC {
public:

    BlockCypher* blockCypher;
    string iv; // initialization vector

    CBC(BlockCypher* blockCypher_, string iv_): blockCypher(blockCypher_), iv(iv_)  {}

    string encrypt(string plainText) {
        assert((int)plainText.size() % blockCypher->BLOCK_SIZE == 0);

        string result = "";
        string lastBlock = iv;

        for(int i = 0; i < (int)plainText.size(); i += blockCypher->BLOCK_SIZE) {
            string b = plainText.substr(i, blockCypher->BLOCK_SIZE);
            auto block_result = blockCypher->encrypt(b ^ lastBlock);
            result += block_result;
            lastBlock = block_result;
        }

        return result;
    }

    string decrypt(string cipherText) {
        assert((int)cipherText.size() % blockCypher->BLOCK_SIZE == 0);
        string result = "";

        string lastBlock = iv;

        for(int i = 0; i < (int)cipherText.size(); i += blockCypher->BLOCK_SIZE) {
            string b = cipherText.substr(i, blockCypher->BLOCK_SIZE);
            auto block_result = blockCypher->decrypt(b) ^ lastBlock;
            result += block_result;
            lastBlock = b;
        }

        return result;
    }

};