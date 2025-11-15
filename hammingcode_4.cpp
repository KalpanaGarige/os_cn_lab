/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

// exp4_hamming.cpp
// Hamming(7,4) encode/decode single-bit error detection & correction
// Works on ALL C++ versions

#include <bits/stdc++.h>
using namespace std;

string encode_hamming74(const string &data4) {
    vector<int> code(8, 0); // index 1..7 used

    // Place data bits (d1..d4) at positions 3,5,6,7
    code[3] = data4[0] - '0';
    code[5] = data4[1] - '0';
    code[6] = data4[2] - '0';
    code[7] = data4[3] - '0';

    // Calculate parity bits
    code[1] = code[3] ^ code[5] ^ code[7];  // p1
    code[2] = code[3] ^ code[6] ^ code[7];  // p2
    code[4] = code[5] ^ code[6] ^ code[7];  // p3

    // Convert to string
    string out = "";
    for (int i = 1; i <= 7; i++) {
        out.push_back(code[i] + '0');
    }
    return out;
}

tuple<int,string,string> decode_and_correct(const string &code7) {
    vector<int> code(8, 0);
    for (int i = 1; i <= 7; i++) {
        code[i] = code7[i-1] - '0';
    }

    // Syndrome bits
    int s1 = code[1] ^ code[3] ^ code[5] ^ code[7];
    int s2 = code[2] ^ code[3] ^ code[6] ^ code[7];
    int s3 = code[4] ^ code[5] ^ code[6] ^ code[7];

    // Convert syndrome to decimal
    int syndrome = s1 + (s2 << 1) + (s3 << 2);

    vector<int> corrected = code;

    // If syndrome is not zero, flip that bit
    if (syndrome >= 1 && syndrome <= 7) {
        corrected[syndrome] ^= 1;
    }

    // Extract original data bits
    string data = "";
    data.push_back(corrected[3] + '0');
    data.push_back(corrected[5] + '0');
    data.push_back(corrected[6] + '0');
    data.push_back(corrected[7] + '0');

    // Convert corrected codeword to string
    string corrected_codeword = "";
    for (int i = 1; i <= 7; i++) {
        corrected_codeword.push_back(corrected[i] + '0');
    }

    return make_tuple(syndrome, corrected_codeword, data);
}

int main() {
    cout << "Enter 4 data bits (e.g., 1011): ";
    string data4;
    cin >> data4;

    if (data4.size() != 4) {
        cout << "Error: Enter exactly 4 bits.\n";
        return 0;
    }

    // Encode
    string codeword = encode_hamming74(data4);
    cout << "Encoded Hamming(7,4) codeword: " << codeword << "\n";

    cout << "Enter error position to simulate (0 for no error, 1..7): ";
    int pos;
    cin >> pos;

    string received = codeword;
    if (pos >= 1 && pos <= 7) {
        received[pos-1] = (received[pos-1] == '0') ? '1' : '0';
        cout << "Received with error: " << received << "\n";
    } else {
        cout << "Received (no error): " << received << "\n";
    }

    // Decode
    int syndrome;
    string corrected_code, decoded_data;

    tie(syndrome, corrected_code, decoded_data) = decode_and_correct(received);

    if (syndrome == 0) {
        cout << "Syndrome = 0 → No error detected.\n";
    } else {
        cout << "Error detected at position: " << syndrome << "\n";
        cout << "Corrected codeword: " << corrected_code << "\n";
    }

    cout << "Decoded data bits: " << decoded_data << "\n";

    return 0;
}
