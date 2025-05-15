#include <bits/stdc++.h>
#include "sdes.cpp"
#include "ecb.cpp"
#include "cbc.cpp"
#include "blockCypher.cpp"

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

int main() {

    auto sdes = SDES("1010000010");

    {
        string block = "11010111";
        auto sdesResult = sdes.encrypt(block, true);
        cout << "SDES encrypt of block " << block << " results in: " << 
            sdesResult << "(" << printHex(sdesResult) << ")\n\n";
        assert(sdes.decrypt(sdesResult) == block);
    }

    string key = "1010000010";
    string text = "11010111011011001011101011110000";
    cout << "Plaintext: " << text << "\n";

    {
        auto ecb = ECB(&sdes);
        string encrypted_text = ecb.encrypt(text);
        cout << "Encrypted text with ECB: " << encrypted_text << "(" << printHex(encrypted_text) << ")\n";
        string decrypted_text = ecb.decrypt(encrypted_text);
        assert(text == decrypted_text);
    }

    {
        auto cbc = CBC(&sdes, "01010101");
        string encrypted_text = cbc.encrypt(text);
        cout << "Encrypted text with CBC: " << encrypted_text << "(" << printHex(encrypted_text) << ")\n";
        string decrypted_text = cbc.decrypt(encrypted_text);
        assert(text == decrypted_text);
    }

    return 0;

}

// SDES encrypt block result: 10101000 A8

// Plaintext: 11010111011011001011101011110000
// Encrypted text with ECB: 10101000000011010010111001101101 A80D2E6D
// Encrypted text with CBC: 00001011101010011001101101101010 0BA99B6A