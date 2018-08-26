#pragma once
#include <string>
#include <iostream>

using namespace std;

//RSA������Կ��
//public_key:�������ɵĹ�Կ
//private_key:�������ɵ�˽Կ
//key_size:��Կ����
void GenerateKey(string & public_key, string & private_key, unsigned int key_size);

//RSA����
//public_key:��Կ
//source:�������ַ���
//encrypted:���ܺ��ַ���
//������������1������-1Ϊ�ַ�������
int RSA_Encrypt(string & public_key, string source, string & encrypted);

//RSA����
//private_key:��Կ
//source:�������ַ���
//decrypted:���ܺ��ַ���
//������������1
int RSA_Decrypt(string & private_key, string source, string & decrypted);

int RSA_EncryptBySection(string & public_key, string source, string & encrypted, int section_length);

int RSA_DecryptBySection(string & private_key, string source, string & decrypted, int section_length);
