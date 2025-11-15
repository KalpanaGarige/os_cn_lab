/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

// exp3_crc.cpp
// CRC Error Detection in C++
// Compile: g++ -std=c++17 exp3_crc.cpp -o exp3_crc

#include <bits/stdc++.h>
using namespace std;

// Perform XOR between two binary strings
string xor_op(string a, string b) {
    string result = "";
    for (int i = 1; i < b.size(); i++)
        result += (a[i] == b[i]) ? '0' : '1';
    return result;
}

// Modulo-2 division
string mod2div(string dividend, string divisor) {
    int pick = divisor.length();
    string tmp = dividend.substr(0, pick);

    while (pick < dividend.length()) {
        if (tmp[0] == '1')
            tmp = xor_op(tmp, divisor) + dividend[pick];
        else
            tmp = xor_op(tmp, string(pick, '0')) + dividend[pick];

        pick++;
    }

    // Final step
    if (tmp[0] == '1')
        tmp = xor_op(tmp, divisor);
    else
        tmp = xor_op(tmp, string(pick, '0'));

    return tmp;
}

string encodeData(string data, string generator) {
    int l = generator.length();
    string appended_data = data + string(l - 1, '0');
    string remainder = mod2div(appended_data, generator);
    return data + remainder;  // codeword
}

int main() {
    string data, generator;

    cout << "Enter data bits: ";
    cin >> data;

    cout << "Enter generator polynomial: ";
    cin >> generator;

    string codeword = encodeData(data, generator);

    cout << "\nCRC Remainder (checksum): "
         << mod2div(data + string(generator.length() - 1, '0'), generator) << endl;

    cout << "Transmitted Codeword: " << codeword << endl;

    // Receiver side
    cout << "\nEnter received codeword: ";
    string received;
    cin >> received;

    string check = mod2div(received, generator);

    if (check == string(generator.length() - 1, '0'))
        cout << "No Error Detected.\n";
    else
        cout << "Error Detected! Remainder = " << check << "\n";

    return 0;
}
