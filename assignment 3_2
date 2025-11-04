#include <bits/stdc++.h>
using namespace std;

string findXor(string a, string b) {
    string result = "";
    for (int i = 1; i < b.length(); i++)
        result += (a[i] == b[i]) ? '0' : '1';
    return result;
}

string mod2div(string dividend, string divisor) {
    int pick = divisor.length();
    string tmp = dividend.substr(0, pick);
    while (pick < dividend.length()) {
        if (tmp[0] == '1')
            tmp = findXor(divisor, tmp) + dividend[pick];
        else
            tmp = findXor(string(pick, '0'), tmp) + dividend[pick];
        pick++;
    }
    if (tmp[0] == '1')
        tmp = findXor(divisor, tmp);
    else
        tmp = findXor(string(pick, '0'), tmp);
    return tmp;
}

string encodeData(string data, string key) {
    int n = key.length();
    string appended = data + string(n - 1, '0');
    string remainder = mod2div(appended, key);
    return data + remainder;
}

int receiver(string code, string key) {
    string remainder = mod2div(code, key);
    return remainder.find('1') == string::npos;
}

int main() {
    string data = "10011101";
    string key = "1001"; // x^3 + 1

    cout << "Sender Side:\n";
    string code = encodeData(data, key);
    cout << "Data: " << data << "\n";
    cout << "Key: " << key << "\n";
    cout << "Transmitted (Encoded) Data: " << code << "\n\n";

    cout << "Receiver Side:\n";
    if (receiver(code, key))
        cout << "Data is correct (No errors)\n";
    else
        cout << "Data is incorrect (Error detected)\n";

    // Simulate bit error (flip 3rd bit)
    string corrupted = code;
    corrupted[2] = (corrupted[2] == '1') ? '0' : '1';
    cout << "\nCorrupted Data: " << corrupted << "\n";
    if (receiver(corrupted, key))
        cout << "Receiver: No error detected\n";
    else
        cout << "Receiver: Error detected!\n";

    return 0;
}
