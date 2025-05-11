#include <bits/stdc++.h>
#include "sdes.cpp"
using namespace std;

int main() {

    string key = "1010000010"; // TESTE!!!!! copiar a certa do pdf do trabalho
    // cout << get_first_subkey(key) << endl;
    // cout << get_second_subkey(key) << endl;
    // string x = "12345678";
    // assert(x == apply_inverse_of_identity_permutation(apply_identity_permutation(x)));
    // cout << apply_fk("1011", "1101", "0000") << "\n";
    // cout << sbox_lookup(s0, "00", "10") << "\n";

    auto sdes = SDES(key);

    string text = "10101010";
    cout << "Plaintext: " << text << "\n";

    string encrypted_text = sdes.encrypt(text);
    cout << "Encrypted text: " << encrypted_text << "\n";

    string decrypted_text = sdes.decrypt(encrypted_text);
    cout << "Decrypted text: " << decrypted_text << "\n";
    
    assert(text == decrypted_text);

    return 0;

}