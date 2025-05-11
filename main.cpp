#include <bits/stdc++.h>
#include "sdes.cpp"
#include "ecb.cpp"
#include "cbc.cpp"

using namespace std;

int main() {

    // TODO: mostrar tudo no console
    // geração da primeira subkey, da segunda e etc
    // como se fosse um log mesmo

    string key = "1010000010";
    string text = "11010111011011001011101011110000";
    cout << "Plaintext: " << text << "\n";

    {
        auto ecb = ECB(key);
        string encrypted_text = ecb.encrypt(text);
        cout << "Encrypted text with ECB: " << encrypted_text << "\n";
        string decrypted_text = ecb.decrypt(encrypted_text);
        // cout << "Decrypted text: " << decrypted_text << "\n";
        assert(text == decrypted_text);
    }

    {
        auto cbc = CBC(key, "01010101");
        string encrypted_text = cbc.encrypt(text);
        cout << "Encrypted text with CBC: " << encrypted_text << "\n";
        string decrypted_text = cbc.decrypt(encrypted_text);
        // cout << "Decrypted text: " << decrypted_text << "\n";
        assert(text == decrypted_text);
    }

    return 0;

}