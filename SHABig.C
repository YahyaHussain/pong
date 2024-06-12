#include <bits/stdc++.h>
using namespace std;
typedef unsigned long int uint32;
typedef unsigned long long int uint64_t;

uint32 hexCharToInt(char hexChar) {
    return hexChar >= '0' && hexChar <= '9' ? hexChar - '0' : hexChar - 'A' + 10;
}

uint32 hexToBinary(const string &hexString) {
    uint32 binaryValue = 0;
    for (int i=0;hexString[i]!='\0';i++) {
        binaryValue = (binaryValue << 4) | hexCharToInt(hexString[i]);
    }
    return binaryValue;
}

string binaryToHex(uint32 binaryValue) {
    stringstream ss;
    ss << hex << setw(8) << setfill('0') << binaryValue;
    return ss.str();
}

uint32 rotateLeft(uint32 x, uint32 n) {
    return (x << n) | (x >> (32 - n));
}

uint32 f(uint32 t, uint32 b, uint32 c, uint32 d) {
    if (t < 20) return (b & c) | ((~b) & d);
    else if (t < 40) return b ^ c ^ d;
    else if (t < 60) return (b & c) | (b & d) | (c & d);
    else return b ^ c ^ d;
}

uint32 K(uint32 t) {
    if (t < 20) return 0x5A827999;
    else if (t < 40) return 0x6ED9EBA1;
    else if (t < 60) return 0x8F1BBCDC;
    else return 0xCA62C1D6;
}

void processBlock(uint32 *W, uint32 *H) {
    uint32 a = H[0];
    uint32 b = H[1];
    uint32 c = H[2];
    uint32 d = H[3];
    uint32 e = H[4];
    for (uint32 t = 0; t < 80; t++) {
        if (t >= 16)
            W[t] = rotateLeft(W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16], 1);
        uint32 TEMP = rotateLeft(a, 5) + f(t, b, c, d) + e + W[t] + K(t);
        e = d;
        d = c;
        c = rotateLeft(b, 30);
        b = a;
        a = TEMP;
    }
    H[0] += a;
    H[1] += b;
    H[2] += c;
    H[3] += d;
    H[4] += e;
}

int main() {
    string input;
    cout << "Enter binary string: ";
    cin >> input;

    // Padding the input
    uint64_t input_length = input.length();
    input += '1';
    while (input.length() % 512 != 448) {
        input += '0';
    }

    // Appending the original length
    string input_length_bin = bitset<64>(input_length).to_string();
    input += input_length_bin;

    uint32 H[5] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};
    uint32 W[80];
    memset(W, 0, sizeof(W));

    // Processing each 512-bit block
    for (size_t i = 0; i < input.length(); i += 512) {
        for (size_t j = 0; j < 16; j++) {
            W[j] = hexToBinary(input.substr(i + j * 32, 32));
        }
        processBlock(W, H);
    }

    for (int i = 0; i < 5; i++) {
        cout << binaryToHex(H[i]) << " ";
    }
    return 0;
}