#include "stdafx.h"
#include "cryptopp_aes.h"

#pragma comment(lib,"cryptlib.lib")


using namespace std;
using namespace CryptoPP;

std::string CBC_AESEncryptStr(std::string sKey, std::string sIV, const char * plainText)
{
	std::string outstr;

	//野key    
	SecByteBlock key(AES::MAX_KEYLENGTH);
	memset(key, 0x30, key.size());
	sKey.size() <= AES::MAX_KEYLENGTH ? memcpy(key, sKey.c_str(), sKey.size()) : memcpy(key, sKey.c_str(), AES::MAX_KEYLENGTH);

	//野iv    
	byte iv[AES::BLOCKSIZE];
	//memset(iv, 0, AES::BLOCKSIZE);
	memset(iv, 0x30, AES::BLOCKSIZE);
	sIV.size() <= AES::BLOCKSIZE ? memcpy(iv, sIV.c_str(), sIV.size()) : memcpy(iv, sIV.c_str(), AES::BLOCKSIZE);

	AES::Encryption aesEncryption((byte *)key, AES::MAX_KEYLENGTH);

	CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);

	StreamTransformationFilter cbcEncryptor(cbcEncryption, new HexEncoder(new StringSink(outstr)));
	cbcEncryptor.Put((byte *)plainText, strlen(plainText));
	cbcEncryptor.MessageEnd();

	return outstr;
}

std::string CBC_AESDecryptStr(std::string sKey, std::string sIV, const char * cipherText)
{
	std::string outstr;

	//野key    
	SecByteBlock key(AES::MAX_KEYLENGTH);
	memset(key, 0x30, key.size());
	sKey.size() <= AES::MAX_KEYLENGTH ? memcpy(key, sKey.c_str(), sKey.size()) : memcpy(key, sKey.c_str(), AES::MAX_KEYLENGTH);

	//野iv    
	byte iv[AES::BLOCKSIZE];
	memset(iv, 0x30, AES::BLOCKSIZE);
	sIV.size() <= AES::BLOCKSIZE ? memcpy(iv, sIV.c_str(), sIV.size()) : memcpy(iv, sIV.c_str(), AES::BLOCKSIZE);


	CBC_Mode<AES >::Decryption cbcDecryption((byte *)key, AES::MAX_KEYLENGTH, iv);

	HexDecoder decryptor(new StreamTransformationFilter(cbcDecryption, new StringSink(outstr)));
	decryptor.Put((byte *)cipherText, strlen(cipherText));
	decryptor.MessageEnd();

	return outstr;
}
