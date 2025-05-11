#include <bits/stdc++.h>
using namespace std;

// xor operator for strings - 1011 ^ 1101 = 0101
string operator ^ (const string& str, string p) { //
    assert((int)str.size() == (int)p.size());
    string ans = str;
    for(int i = 0; i < (int)str.size(); i++) {
        ans[i] = (str[i] == p[i] ? '0' : '1'); 
    }
    return ans;
}

class SDES {
public:
    const int BLOCK_SIZE = 8; // bits
    
    string key;
    
    string encrypt(string block) {
        assert((int)block.size() == BLOCK_SIZE);
        assert((int)key.size() == 10);

        auto subkey1 = get_first_subkey(key);
        auto subkey2 = get_second_subkey(key);

        auto permuted_text = apply_identity_permutation(block);
        auto permuted_with_subkey1 = apply_fk(permuted_text.substr(0, 4), permuted_text.substr(4), subkey1);
        auto switched = switch_function(permuted_with_subkey1);
        auto permuted_with_subkey2 = apply_fk(switched.substr(0, 4), switched.substr(4), subkey2);

        return apply_inverse_of_identity_permutation(permuted_with_subkey2);
    }

    string decrypt(string block) {
        assert((int)block.size() == BLOCK_SIZE);
        assert((int)key.size() == 10);

        auto subkey1 = get_first_subkey(key);
        auto subkey2 = get_second_subkey(key);

        auto permuted_text = apply_identity_permutation(block);
        auto permuted_with_subkey2 = apply_fk(permuted_text.substr(0, 4), permuted_text.substr(4), subkey2);
        auto switched = switch_function(permuted_with_subkey2);
        auto permuted_with_subkey1 = apply_fk(switched.substr(0, 4), switched.substr(4), subkey1);

        return apply_inverse_of_identity_permutation(permuted_with_subkey1);
    }

protected:

    const vector<int> p10 = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};    // p10 permutation
    const vector<int> p8 = {6, 3, 7, 4, 8, 5, 10, 9};           // p8 permutation
    const vector<int> ip = {2, 6, 3, 1, 4, 8, 5, 7};            // identity permutation
    const vector<int> ip_inv = {4, 1, 3, 5, 7, 2, 8, 6};        // inverse of ip
    const vector<int> ep = {4, 1, 2, 3, 2, 3, 4, 1};            // expansion/permutation
    const vector<int> sbox_permutation = {2, 4, 3, 1};          // S-box permutation

    const vector<vector<int>> s0 = {
        {1, 0, 3, 2},
        {3, 2, 1, 0},
        {0, 2, 1, 3},
        {3, 1, 3, 2}
    };

    const vector<vector<int>> s1 = {
        {0, 1, 2, 3},
        {2, 0, 1, 3},
        {3, 0, 1, 0},
        {2, 1, 0, 3}
    };

    int sbox_lookup(vector<vector<int>> sbox, string row, string col) {
        // cout << "sbox_lookup " << row << " " << col << endl;
        assert((int)row.size() == 2);
        assert((int)col.size() == 2);
        int row_num = (row[0] - '0') * 2 + (row[1] - '0');
        int col_num = (col[0] - '0') * 2 + (col[1] - '0');
        return s0[row_num][col_num];
    }

    int sbox0_lookup(string row, string col) {
        return sbox_lookup(s0, row, col);
    }

    int sbox1_lookup(string row, string col) {
        return sbox_lookup(s1, row, col);
    }

    string expand_and_permute(string mask) {
        assert((int)mask.size() == 4);
        // E/P (4, 1, 2, 3, 2, 3, 4, 1)
        string ans = string(8, '0');

        for(int i = 0; i < (int)ans.size(); i++) {
            ans[i] = mask[ep[i] - 1];
        }

        return ans;
    }

    string switch_function(string mask) {
        assert((int)mask.size() == 8);
        return mask.substr(4, 4) + mask.substr(0, 4);
    }

    string apply_permutation(string mask, vector<int> p) {
        assert((int)mask.size() == (int)p.size());
        string ans = string((int)mask.size(), '0');
        for(int i = 0; i < (int)mask.size(); i++) {
            ans[i] = mask[p[i] - 1];
        }
        return ans;
    }

    string F(string mask, string subkey) {
        assert((int)mask.size() == 4);
        auto expanded_mask = expand_and_permute(mask);
        auto pos_mapping = expanded_mask ^ subkey;

        string s0_row = { pos_mapping[0], pos_mapping[3] };
        string s0_col = { pos_mapping[1], pos_mapping[2] };

        string s1_row = { pos_mapping[4], pos_mapping[7] };
        string s1_col = { pos_mapping[5], pos_mapping[6] };

        // cout << "pos_mapping: " << pos_mapping << endl;
        // cout << "expanded_mask: " << expanded_mask << endl;
        // cout << "s0_row: " << s0_row << endl;
        // cout << "s0_col: " << s0_col << endl;
        // cout << "s1_row: " << s1_row << endl;
        // cout << "s1_col: " << s1_col << endl;

        int s0_val = sbox_lookup(s0, s0_row, s0_col);
        int s1_val = sbox_lookup(s1, s1_row, s1_col);

        bitset<2> s0_bitset(s0_val);
        bitset<2> s1_bitset(s1_val);

        string s0_str = s0_bitset.to_string();
        string s1_str = s1_bitset.to_string();

        string r = s0_str + s1_str;

        return apply_permutation(r, sbox_permutation);
    }

    string apply_fk(string l, string r, string subkey) {
        return (l ^ F(r, subkey)) + r;
    }

    string apply_identity_permutation(string mask) {
        return apply_permutation(mask, ip);
    }

    string apply_inverse_of_identity_permutation(string mask) {
        return apply_permutation(mask, ip_inv);
    }

    // (1010000010) -> (1000001100).
    string permute10(string input) {
        // P10(k1, k2, k3, k4, k5, k6 , k7, k8, k9, k10) 
        //  = (k3, k5, k2, k7, k4, k10, k1, k9, k8, k6)
        return apply_permutation(input, p10);
    }

    // 0000111000 -> 10100100
    string pick_and_permute8(string input) {
        assert(int(input.size()) == 10);
        //P8 (1, 2, 3, 4, 5, 6, 7, 8, 0, 10)
        // = (6 3 7 4 8 5 10 9)
        string ans = string(8, '0');
        for(int i = 0; i < (int)ans.size(); i++) {
            ans[i] = input[p8[i] - 1];
        }
        return ans;
    }

    // 10000 -> 00001
    // 01100 -> 11000
    string left_shift(string s) {
        int size = (int)s.size();
        return s.substr(1, size - 1) + s[0];
    }

    string get_first_subkey(string key) {
        int size = (int)key.size();
        assert(size % 2 == 0);
        auto permuted_key = permute10(key);

        auto l = permuted_key.substr(0, size / 2);
        auto r = permuted_key.substr(size / 2, size / 2);

        auto shifted_l = left_shift(l);
        auto shifted_r = left_shift(r);

        return pick_and_permute8(shifted_l + shifted_r);
    }

    string get_second_subkey(string key) {
        int size = (int)key.size();
        assert(size % 2 == 0);
        auto permuted_key = permute10(key);

        auto l = permuted_key.substr(0, size / 2);
        auto r = permuted_key.substr(size / 2, size / 2);

        string shifted_l = l, shifted_r = r;

        for(int i = 0; i < 3; i++) { // 1 + 2 shifts
            shifted_l = left_shift(shifted_l);
            shifted_r = left_shift(shifted_r);
        }

        return pick_and_permute8(shifted_l + shifted_r);
    }

};