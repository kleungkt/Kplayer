#include "ssltool.h"
#include <vector>
#include <QByteArray>
#include <QDebug>

#ifdef WIN32
    #pragma comment(lib, "bcrypt.lib")
#endif

const char* PRIVATE_KEY =
    "-----BEGIN PRIVATE KEY-----\n"
    "MIICdwIBADANBgkqhkiG9w0BAQEFAASCAmEwggJdAgEAAoGBANcooF0WReHnC/62\n"
    "guKjo41hEwmpRZFqjrbVHKYLm9I26JgFaY93B5LJmO5zyGq+Fi6eTMW05HHOlEkK\n"
    "FBuAND08rwgBhwHz8vXTZeLGCsL9mBmWLxyu0RZxzW6YV5iZHfx69TM9erWVL+zq\n"
    "nCZp92oaHtz++BYBwHFze4gBTAW1AgMBAAECgYEAgwIwyx2BxbCqpBi7j4a2UqK2\n"
    "Nd7FBmtMpNUU0aIl6hUXAWHiScHfcaihHyiO8zf1R8OJ2aRwqT9xGRwy7B/fLgCR\n"
    "z8UZVubW6DLGPArY57Mj1ySieJFHJP8IRoY2eVoE2TzfavhpwLJ9JHWuzFkWYW9u\n"
    "luAknhuDnsufV/EuumECQQDsEAPgBSfHmWzkHNN7cx/RBC7Bn4j8Q9sOYDUSvqRB\n"
    "vRPfQw0vkG3DCrZllq/DZtjIJq0gaAMg29OvMkumGVMJAkEA6VSkYlHVjZl7Utja\n"
    "HW3tri5tLAqesDmMxVwjKWDjWcHfjt4c/0O4l7+dfd+EZI9iR0m3XGNYWSX8TNO7\n"
    "DcSsTQJAMPNpOk0XYKaKFAt+Nz06PceWQoRojZcsl6CPoOFzgkZJFqT62QAkIqvY\n"
    "AtzqeaScE3UhtXScIXY0QUI2uazKsQJBANMWANT1xaWheWD8z24aWhDe7WMPhHpW\n"
    "xhRyA1lWzrcP3oioRkFkaaXW8srCIEq9MKLffKN3OKEF7VcvoSSWjW0CQF9ML3GA\n"
    "R94YixQbnOcIr6/UzYPS/bjxkNTNL6ELvRi+hhTq6qFRdpn1cSAMOo9B8mpnTSq6\n"
    "UAVyryN65BVCclA="
    "-----END PRIVATE KEY-----\n";

const char* PUBLIC_KEY =
    "-----BEGIN PUBLIC KEY-----\n"
    "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDXKKBdFkXh5wv+toLio6ONYRMJ\n"
    "qUWRao621RymC5vSNuiYBWmPdweSyZjuc8hqvhYunkzFtORxzpRJChQbgDQ9PK8I\n"
    "AYcB8/L102XixgrC/ZgZli8crtEWcc1umFeYmR38evUzPXq1lS/s6pwmafdqGh7c\n"
    "/vgWAcBxc3uIAUwFtQIDAQAB\n"
    "-----END PUBLIC KEY-----\n";

//D:\Program Files (x86)\OpenSSL\bin\server_private.key
const char* SERVER_PRIVATE =
    "-----BEGIN PRIVATE KEY-----\n"
    "MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQDMm6nulkJuA3pV\n"
    "kSKcjIDGIuL9ywPtP4APiryzwWY6CIxX2P9RyXQHaSwUKJObtW21q1Zl1J99enQd\n"
    "TQJTUx++ZCjmGGgxhfL5eaWfGyCAQ82GqK3RiCpawRc0u6okCo6LktHUbGKwAiaO\n"
    "L1qgyZAAiJVEdegJeFLrAh4LY9j0nkH78q8CIzrcJbJmOJv5Bbivg4S/lupXcGUx\n"
    "nb2JVGsnPeasZmnoPw20mTDLcYHcIC0J/HoERmjXwe3Ppsa7b9szcd5qgh3hkJzP\n"
    "cXXKrXx1FmUY57WquZy4YzeBG73kTobxtV9d7KzYA09AZZzjeI9iL+50b6ip6hk4\n"
    "cX4JNYOdAgMBAAECggEAE0ayDIB6+y7YMmIFQv7oreIBBRyAfvQ9zhkJvJyikyKV\n"
    "iDwxF6U1SXJy3OZSu7dswdIFxnuw1+s2r8D+0FdTNQZuJPlVLZ87PB4mCJaPag4Z\n"
    "OY/AKm6b4Odylnz8oz8cXVFkc9EPPhpBxCD5do7uwmIbv/KkvOmpVCsjpfqO6MKp\n"
    "/xeTrhOZ3obK8qf13uTbmy4qJsVR2SEQVJtr00Ig/YSBJx23ukppQvKYgNnzrGqb\n"
    "RoSDDelxNsZa6ESFjrwPQl+hBhiAwzFKAuiz1trfqdepQP3XnrXfNPOvkz5kXHxT\n"
    "CLDQ6aeTQKDAXC8HFne94SgNn88xALZB9HDkB9f5aQKBgQDorLWKVFszJUqmjz4d\n"
    "6ACNP2fFYxUoYKDAUEIlC1e3JTCtWHQBSWlvWHrXb/NoFIRO1k8MXK2hWfGGmGtx\n"
    "EIDNp3FTiiq2R3gZmnISk0MkbMtH4VonIJx+EI9jsZzUaIud8AMeCiR7aDDiNJMg\n"
    "2YIHP8wS7ZoLGhs6VjXWSLYaSQKBgQDhHqmWbMb29+9KmGz60AICFnx8jrrDgr2M\n"
    "Hr407DzlxxeXxkkCd4BhPVQDktjPLwkvs6EXGtTnsudq7pJXM5mMDUQkGiZBumnl\n"
    "H3g9k5Pox4vtKnz/jcXtb75T9BEqsDbRX1MtZTet6MSb7BkAQ1quM38DoxP7n52A\n"
    "qYoX211+tQKBgQC3vNMrZowSaot11j4eTbxJzl07AZCOryeiVn61VCyzYvn6mZQa\n"
    "BAfvtrZi9HQJp9IHk7Metv0iIq3ZNPn7ciXUwTp71ur9wJh114Hna0UlOYiZvbp8\n"
    "lYMfBiLFflezYM+ILCW6DhZbIZ8gspXQ5hKJePbFp73ysG359mRTUF4FiQKBgQCW\n"
    "7/0ay4I3spLxe/ON0wuVpMgAp54XWkCGg1Jan45RLcTm0V7AValxCTKcVsghWdMZ\n"
    "9aFroWTgmPZKnvzllMY9veNTJWlDJp67rfbrqlhAehKaiKNYoRD1GrgNCBa+fXmz\n"
    "tetKA5RqeSfht1In+AEDzak6ogvS6PksfAAH8N/mBQKBgCRxJxRPIUmKe9SVLRdG\n"
    "91DqDFkMW1JvHkh6lg0u9hJI2VOaUjISUV0DoGaGbJFA5uk0bN5e2/og7E5S+ran\n"
    "V+uqqHS5yZvntLn+Dst8WoszFf5NZyPZrHc5a3ckbLn741BKtCpt/lGMJVP0IB76\n"
    "4jgCV5SCS4TjwVHaLyPHH745\n"
    "-----END PRIVATE KEY-----\n";

//D:\Program Files (x86)\OpenSSL\bin\server_public.key
const char* SERVER_PUBLIC =
    "-----BEGIN PUBLIC KEY-----\n"
    "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAzJup7pZCbgN6VZEinIyA\n"
    "xiLi/csD7T+AD4q8s8FmOgiMV9j/Ucl0B2ksFCiTm7VttatWZdSffXp0HU0CU1Mf\n"
    "vmQo5hhoMYXy+XmlnxsggEPNhqit0YgqWsEXNLuqJAqOi5LR1GxisAImji9aoMmQ\n"
    "AIiVRHXoCXhS6wIeC2PY9J5B+/KvAiM63CWyZjib+QW4r4OEv5bqV3BlMZ29iVRr\n"
    "Jz3mrGZp6D8NtJkwy3GB3CAtCfx6BEZo18Htz6bGu2/bM3HeaoId4ZCcz3F1yq18\n"
    "dRZlGOe1qrmcuGM3gRu95E6G8bVfXeys2ANPQGWc43iPYi/udG+oqeoZOHF+CTWD\n"
    "nQIDAQAB\n"
    "-----END PUBLIC KEY-----\n";

//openssl.exe genrsa -out ca.key 1024
//openssl.exe rsa -in ca.key -pubout -out rsa_pub.key

SslTool::SslTool()
{
    BIO* bio = BIO_new_mem_buf(SERVER_PUBLIC, -1);
    if(bio == NULL)
    {
        throw "load public key failed!";
    }
    rsa_public = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL);
    BIO_free(bio);
    bio = BIO_new_mem_buf(SERVER_PRIVATE, -1);
    if(bio == NULL)
    {
        throw "load private key failed!";
    }
    rsa_private = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL);
}

string BigNum::base64Encode(const string& buffer, bool newline)
{
    BIO* bmem = NULL;
    BIO* b64 = NULL;
    BUF_MEM* bptr;
    b64 = BIO_new(BIO_f_base64());
    if (!newline)
    {
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, buffer.c_str(), (int)buffer.size());
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);
    BIO_set_close(b64, BIO_NOCLOSE);
    string buff;
    buff.resize(bptr->length + 1);
    memcpy((char*)buff.c_str(), bptr->data, bptr->length);
    buff[bptr->length] = 0;
    BIO_free_all(b64);
    return buff;
}

QByteArray SslTool::rsaEncode(const QByteArray& buffer)
{
    QByteArray result;
    //qDebug() << __FILE__ << "(" << __LINE__ << "):" << buffer.size();
    result.resize(buffer.size() * 3);//Because it needs to be aligned, it may be a lot longer
    memset(result.data(), 0, result.size());
    //qDebug() << __FILE__ << "(" << __LINE__ << "):" << buffer;
    int ret = RSA_public_encrypt(
                  (int)buffer.size(),
                  (const unsigned char*)buffer.data(),
                  (unsigned char*)result.data(),
                  rsa_public, RSA_PKCS1_PADDING);
    //qDebug() << __FILE__ << "(" << __LINE__ << "):ret=" << ret;
    if(ret == -1)
    {
        result.clear();
        return result;
    }
    result.resize(ret);
    //qDebug() << __FILE__ << "(" << __LINE__ << "):" << result;
    return result;
}

QByteArray SslTool::rsaDecode(const QByteArray& input)
{
    QByteArray result;
    result.resize(input.size());
    int ret = RSA_private_decrypt(
                  input.size(),
                  (const unsigned char*)input.data(),
                  (unsigned char*)result.data(),
                  rsa_private, RSA_PKCS1_PADDING);
    if(ret == -1)
    {
        result.clear();
        return result;
    }
    return result;
}

BigNum::BigNum()
{
    bignum = BN_new();
}

BigNum::BigNum(const BigNum& bm)
{
    bignum = BN_new();
    BN_copy(bignum, bm.bignum);
}

BigNum::BigNum(const string& bm, bool is_base64/* = true*/)
{
    string key;
    if(is_base64)
    {
        key = base64Decode(bm);
    }
    else
    {
        key = hex2bin(bm);
    }
    BN_bin2bn((const unsigned char*)key.c_str(), (int)key.size(), bignum);
}

BigNum::~BigNum()
{
    if(bignum != NULL)
    {
        BN_free(bignum);
        bignum = NULL;
    }
}

BigNum& BigNum::operator=(const BigNum& bm)
{
    bignum = BN_new();
    BN_copy(bignum, bm.bignum);
    return *this;
}

BigNum& BigNum::fromBase64(const string& bm)
{
    string key = base64Decode(bm);
    BN_bin2bn((const unsigned char*)key.c_str(), (int)key.size(), bignum);
    return *this;
}

BigNum& BigNum::fromHex(const string& bm)
{
    string key = hex2bin(bm);
    BN_bin2bn((const unsigned char*)key.c_str(), (int)key.size(), bignum);
    return *this;
}

BigNum& BigNum::fromBinary(const string& bm)
{
    BN_bin2bn((const unsigned char*)bm.c_str(), (int)bm.size(), bignum);
    return *this;
}

string BigNum::toBinary()
{
    string result;
    result.resize(4096);
    int len = BN_bn2bin(bignum, (unsigned char*)result.c_str());
    result.resize(len);
    return result;
}

string BigNum::hex2bin(const string& hex)
{
    string result;
    string h = hex;
    size_t i = h.find(" ");
    while(i != string::npos)
    {
        h.replace(i, 1, "");
        i = h.find(" ", i);
    }
    if(h.size() % 2)//Alignment
    {
        h = "0" + h;
    }
    for(size_t i = 0; i < h.size(); i += 2)
    {
        char data[3] = "";
        memcpy(data, h.c_str() + i, 2);
        result += (char)strtol(data, NULL, 16);
    }
    return result;
}

BigNum& BigNum::operator=(const string& bm)
{
    fromHex(bm);
    return *this;
}

BigNum::operator string()
{
    return string(BN_bn2hex(bignum));
}

BigNum::operator BIGNUM* ()
{
    return bignum;
}

string BigNum::base64Decode(const string& input, bool newline)
{
    BIO* b64 = NULL;
    BIO* bmem = NULL;
    string strBuffer;
    strBuffer.resize(input.size());
    char* buffer = (char*)strBuffer.c_str();
    memset(buffer, 0, strBuffer.size());
    b64 = BIO_new(BIO_f_base64());
    if (!newline)
    {
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }
    bmem = BIO_new_mem_buf(input.c_str(), (int)strBuffer.size());
    bmem = BIO_push(b64, bmem);
    BIO_read(bmem, buffer, (int)strBuffer.size());
    BIO_free_all(bmem);
    return strBuffer;
}
