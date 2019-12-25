#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

#include <openssl/sha.h>
string sha256(const string str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for(int i = 0; i < 32; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

int main() {
    cout << sha256("Курлык") << endl;
    cout << sha256("йоцатЦОУА ОФМ ОФМОФЫР МОФ МОФАМОФ МАОФА МОФВА ОМФВА ИОФВАТ ИОФВТА ИОФВТА ИОТАВОА") << endl;
    cout << sha256("1234567890_3") << endl;
    cout << sha256("1234567890_4") << endl;
    return 0;
}
