#include <bits/stdc++.h>
#include "code/sdes.cpp"
#include "code/ecb.cpp"
#include "code/cbc.cpp"
#include "code/blockCypher.cpp"

using namespace std;

string printHex(string b) {
    string result = "";
    for(int i = 0; i < (int)b.size(); i += 4) {
        string block = b.substr(i, 4);
        int decimal = stoi(block, nullptr, 2);
        char hexChar = (decimal < 10) ? ('0' + decimal) : ('A' + decimal - 10);
        result += hexChar;
    }
    return result;
}

string readFromFile(string path) {
    ifstream file(path);
    string res;
    file >> res;
    file.close();
    return res;
}

int main(int argc, char* argv[]) {

    bool debug = false;
    bool useEcb = false;
    bool useCbc = false;

    for(int i = 1; i < argc; i++) {
        if(string(argv[i]) == "--debug") {
            debug = true;
        } else if(string(argv[i]) == "--ecb") {
            useEcb = true;
        } else if(string(argv[i]) == "--cbc") {
            useCbc = true;
        }
    }
    
    if(!useEcb && !useCbc) {
        cout << "Please specify --ecb or --cbc\n";
        return 1;
    }

    if(useEcb && useCbc) {
        cout << "Please specify only one of --ecb or --cbc\n";
        return 1;
    }

    string key = readFromFile("data/key");
    string text = readFromFile("data/plainText");
    string iv = readFromFile("data/iv");

    if(debug) {
        cout << "Key: " << key << "\n";
        cout << "Plaintext: " << text << "\n";
        cout << "IV: " << iv << "\n";
    }

    auto sdes = SDES(key, debug);

    if(useEcb) {
        auto ecb = ECB(&sdes);
        string encrypted_text = ecb.encrypt(text);
        cout << "Encrypted text with ECB: " << encrypted_text << " -- " << printHex(encrypted_text) << "\n";
        string decrypted_text = ecb.decrypt(encrypted_text);
        assert(text == decrypted_text);
    } else { // cbc
        auto cbc = CBC(&sdes, iv);
        string encrypted_text = cbc.encrypt(text);
        cout << "Encrypted text with CBC: " << encrypted_text << " -- " << printHex(encrypted_text) << "\n";
        string decrypted_text = cbc.decrypt(encrypted_text);
        assert(text == decrypted_text);

    }

    return 0;

}