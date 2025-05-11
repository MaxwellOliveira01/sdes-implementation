#include "sdes.cpp"
using namespace std;

class CBC : public SDES {
public:

    string iv; // initialization vector

    CBC(string key_, string iv_): SDES(key_), iv(iv_) {}

    string encrypt(string plainText) override {
        assert((int)plainText.size() % BLOCK_SIZE == 0);

        string result = "";
        string lastBlock = iv;

        for(int i = 0; i < (int)plainText.size(); i += BLOCK_SIZE) {
            string b = plainText.substr(i, BLOCK_SIZE);
            auto block_result = SDES::encrypt(b ^ lastBlock);
            result += block_result;
            lastBlock = block_result;
        }

        return result;
    }

    string decrypt(string cipherText) override {
        assert((int)cipherText.size() % BLOCK_SIZE == 0);
        string result = "";

        string lastBlock = iv;

        for(int i = 0; i < (int)cipherText.size(); i += BLOCK_SIZE) {
            string b = cipherText.substr(i, BLOCK_SIZE);
            auto block_result = SDES::decrypt(b) ^ lastBlock;
            result += block_result;
            lastBlock = b;
        }

        return result;
    }

};