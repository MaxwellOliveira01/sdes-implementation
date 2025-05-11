#include "sdes.cpp"
using namespace std;

class ECB : public SDES {
public:

    ECB(string key_): SDES(key_) {}

    string encrypt(string plainText) override {
        assert((int)plainText.size() % BLOCK_SIZE == 0);
        string result = "";

        // just encript every block
        for(int i = 0; i < (int)plainText.size(); i += BLOCK_SIZE) {
            result += SDES::encrypt(plainText.substr(i, BLOCK_SIZE));
        }

        return result;
    }

    string decrypt(string cipherText) override {
        assert((int)cipherText.size() % BLOCK_SIZE == 0);
        string result = "";

        // just decrypt every block
        for(int i = 0; i < (int)cipherText.size(); i += BLOCK_SIZE) {
            result += SDES::decrypt(cipherText.substr(i, BLOCK_SIZE));
        }

        return result;
    }

};