#pragma once
#include <aes.h>
#include <modes.h>
#include <hex.h>
#include <string>


std::string CBC_AESEncryptStr(std::string sKey, std::string sIV, const char *plainText);

std::string CBC_AESDecryptStr(std::string sKey, std::string sIV, const char *cipherText);
