#ifndef SSLTOOL_H
#define SSLTOOL_H

extern "C"
{
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include "openssl/pem2.h"
#include "openssl/pem.h"
#include "openssl/rsa.h"
#include "openssl/err.h"
#include "openssl/opensslv.h"
#include "openssl/bn.h"
}

#include <string>
#include <QByteArray>

using namespace std;

class BigNum
{
public:
    BigNum();
    BigNum(const BigNum& bm);
    BigNum(const string& bm, bool is_base64 = true);
    ~BigNum();
    operator BIGNUM* ();
    operator string(); // Convert to string
    BigNum& operator=(const string& bm); // Convert from string
    BigNum& operator=(const BigNum& bm);
    // Get BigNum from hex string
    BigNum& fromBase64(const string& bm);
    BigNum& fromHex(const string& bm);
    BigNum& fromBinary(const string& bm);
    string toBinary(); // Convert to binary
    static string base64Decode(const string& input, bool newline = false);
    static string base64Encode(const string& buffer, bool newline = false);

private:
    string hex2bin(const string& hex);
    BIGNUM* bignum;
};

class SslTool
{
public:
    SslTool();
    // RSA encryption
    QByteArray rsaEncode(const QByteArray& buffer);
    // RSA decryption
    QByteArray rsaDecode(const QByteArray& input);

private:
    RSA* rsa_public;
    RSA* rsa_private;
};

#endif // SSLTOOL_H
