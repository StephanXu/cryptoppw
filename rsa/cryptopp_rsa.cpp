#include "stdafx.h"
#include <iostream>
#include <string>
#include "../CryptoPP/Include/hex.h"
#include "../CryptoPP/Include/rsa.h"
#include "../CryptoPP/Include/randpool.h"
#include "../CryptoPP/Include/osrng.h"
#include <sstream>
#include <iomanip>

#include "cryptopp_rsa.h"

#pragma comment(lib, "../CryptoPP/Release/cryptlib.lib")

using namespace CryptoPP;
using namespace std;

//RSA������Կ��
//public_key:�������ɵĹ�Կ
//private_key:�������ɵ�˽Կ
//key_size:��Կ����
void GenerateKey(string& public_key, string& private_key, unsigned int key_size)
{
	public_key = "";
	private_key = "";
	AutoSeededRandomPool _rng;
	InvertibleRSAFunction _rsa_params;
	_rsa_params.GenerateRandomWithKeySize(_rng, key_size);

	RSA::PrivateKey key_private(_rsa_params);
	RSA::PublicKey key_public(_rsa_params);

	key_private.DEREncode(HexEncoder(new StringSink(private_key)));
	key_public.DEREncode(HexEncoder(new StringSink(public_key)));
	return;
}

//RSA����
//public_key:��Կ
//source:�������ַ���
//encrypted:���ܺ��ַ���
//������������1������-1Ϊ�ַ�������
int RSA_Encrypt(string& public_key, string source, string &encrypted)
{
	encrypted = "";
	AutoSeededRandomPool _rng;
	RSAES_OAEP_SHA_Encryptor encryptor(StringSource(public_key, true, new HexDecoder));
	if (source.length() > encryptor.FixedMaxPlaintextLength())
		return -1;
	StringSource(source, true, new PK_EncryptorFilter(_rng, encryptor, new HexEncoder(new StringSink(encrypted))));
	return 1;
}

//RSA����
//private_key:��Կ
//source:�������ַ���
//decrypted:���ܺ��ַ���
//������������1
int RSA_Decrypt(string& private_key, string source, string &decrypted)
{
	decrypted = "";
	AutoSeededRandomPool _rng;
	RSAES_OAEP_SHA_Decryptor decryptor(StringSource(private_key, true, new HexDecoder));
	StringSource(source, true, new HexDecoder(new PK_DecryptorFilter(_rng, decryptor, new StringSink(decrypted))));
	return 1;
}

int RSA_EncryptBySection(string& public_key, string source, string &encrypted, int section_length)
{
	encrypted = "";
	stringstream ss(source);
	stringstream outss;
	string tem{};
	string re{};
	for (int i{}; i < (source.length() / section_length + (source.length() % section_length ? 1 : 0)); i++)
	{
		ss >> setw(section_length) >> tem;
		if (-1 == RSA_Encrypt(public_key, tem, re))
			return -1;
		outss << re;
	}

	encrypted = outss.str();

	return 1;
}

int RSA_DecryptBySection(string& private_key, string source, string &decrypted, int section_length)
{
	decrypted = "";
	stringstream ss(source);
	stringstream outss;
	string tem{};
	string re{};
	for (int i{}; i < (source.length() / section_length + (source.length() % section_length ? 1 : 0)); i++)
	{
		ss >> setw(section_length) >> tem;
		//OutputDebugStringA(("[okokok]" + tem).c_str());
		if (-1 == RSA_Decrypt(private_key, tem, re))
			return -1;
		outss << re;
	}

	decrypted = outss.str();

	return 1;
}
