#pragma once
#include <string>
#include <iostream>

using namespace std;

//RSA生成密钥对
//public_key:返回生成的公钥
//private_key:返回生成的私钥
//key_size:密钥长度
void GenerateKey(string & public_key, string & private_key, unsigned int key_size);

//RSA加密
//public_key:公钥
//source:待加密字符串
//encrypted:加密后字符串
//加密正常返回1，返回-1为字符串过长
int RSA_Encrypt(string & public_key, string source, string & encrypted);

//RSA加密
//private_key:公钥
//source:待解密字符串
//decrypted:解密后字符串
//解密正常返回1
int RSA_Decrypt(string & private_key, string source, string & decrypted);

int RSA_EncryptBySection(string & public_key, string source, string & encrypted, int section_length);

int RSA_DecryptBySection(string & private_key, string source, string & decrypted, int section_length);
