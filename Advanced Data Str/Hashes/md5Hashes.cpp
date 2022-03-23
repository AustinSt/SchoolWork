#include <iostream>
#include <openssl/md5.h>

using namespace std;

void md5Hash(void)
{
    string input = "potatoes are awesome";
    MD5_CTX context;
    unsigned char *u_MD5Digest;
    int i = 0;

    u_MD5Digest = new unsigned char[MD5_DIGEST_LENGTH];

    cout << "Creating MD5 hash of string: '"<<input<<"'"<<endl;
    MD5_Init(&context);
    MD5_Update(&context, input.c_str(), input.length());
    MD5_Final(u_MD5Digest, &context);

    for(int i = 0; i < MD5_DIGEST_LENGTH; ++i)
    {
        printf("%02x", u_MD5Digest[i]);
    }
    cout <<endl;
}

int main(int argc, char *argv[])
{
    md5Hash();

    return 0;
}