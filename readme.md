# crypto++ wrap

## 综述

这个项目用于存储对于crypto++的一些封装函数，尽可能做到一个功能一行代码直接调用完成。如下是关于封装库的使用说明，如果有任何不严谨的或错误的地方，欢迎指出。

## 函数使用说明

### AES 算法

文件为aes文件夹下的两个文件，使用头文件中声明的两个函数即可。如下是使用说明。

##### CBC_AESEncryptStr
```c++
std::string CBC_AESEncryptStr(std::string sKey, std::string sIV, const char *plainText);
```
- 描述：AES算法加密字符串
- 返回值：(std::string)加密结果

| 参数名    | 类型        | 备注           |
| --------- | ----------- | -------------- |
| sKey      | std::string | 32位长度密钥   |
| sIV       | std::string | 16位长度IV     |
| plainText | const char\* | 待加密的字符串 |

##### CBC_AESDecryptStr
```C++
std::string CBC_AESDecryptStr(std::string sKey, std::string sIV, const char *cipherText);
```
- 描述：解密AES加密后的字符串
- 返回值：(std::string)解密结果

| 参数名    | 类型        | 备注           |
| --------- | ----------- | -------------- |
| sKey      | std::string | 32位长度密钥   |
| sIV       | std::string | 16位长度IV     |
| cipherText | const char\* | 待解密的字符串 |

### RSA算法

##### GenerateKey
```C++
void GenerateKey(string & public_key, string & private_key, unsigned int key_size);
```
- 描述：生成密钥对
- 返回值：void

| 参数名    | 类型        | 备注           |
| --------- | ----------- | -------------- |
| public_key | string& | 返回生成的公钥 |
| private_key | string& | 返回生成的私钥 |
| key_size | unsigned int | 密钥长度（例如1024） |

##### RSA_Encrypt
```C++
int RSA_Encrypt(string & public_key, string source, string & encrypted);
```
- 描述：RSA解密
- 返回值：(int)加密正常返回1，返回-1为字符串过长

| 参数名    | 类型        | 备注           |
| --------- | ----------- | -------------- |
| public_key | string& | 公钥 |
| source | string | 待加密字符串 |
| encrypted | string& | 加密后字符串 |

##### RSA_Decrypt
```C++
int RSA_Decrypt(string & private_key, string source, string & decrypted);
```
- 描述：RSA加密
- 返回值：(int)解密正常返回1

| 参数名    | 类型        | 备注           |
| --------- | ----------- | -------------- |
| private_key | string& | 私钥 |
| source | string | 待解密字符串 |
| decrypted | string& | 解密后字符串 |

##### RSA_EncryptBySection
```C++
int RSA_EncryptBySection(string & public_key, string source, string & encrypted, int section_length);
```
- 描述：RSA分段加密，此函数常用于超长字符串的加密。将字符串定长地分割为若干段后进行加密，然后拼接。
- 返回值：(int)加密正常返回1

| 参数名    | 类型        | 备注           |
| --------- | ----------- | -------------- |
| public_key | string& | 公钥 |
| source | string | 待加密字符串 |
| decrypted | string& | 加密后字符串 |
|section_length|int|单段长度|

##### RSA_EncryptBySection
```C++
int RSA_DecryptBySection(string & private_key, string source, string & decrypted, int section_length);
```
- 描述：RSA分段解密，此函数常用于解密RSA_EncryptBySection加密的字符串，当然，如果是其他平台/语言使用类似的逻辑进行加密的字符串同样也可以解密。
- 返回值：(int)解密正常返回1

| 参数名    | 类型        | 备注           |
| --------- | ----------- | -------------- |
| private_key | string& | 私钥 |
| source | string | 待解密字符串 |
| decrypted | string& | 解密后字符串 |
|section_length|int|单段长度，需要注意的是，这里的单段长度程序是会直接对`source`中的字符串进行分割，需要使用者自行计算好明文单段长度加密后的密文长度来对应解密，详情请参阅本节`备注`。|

###### 备注：关于分段解密的section_length参数

关于分段加密，笔者想做下面的说明。RSA算法对明文是有长度限制的，所以我们在加密超长字符串的时候，有时候采用一种分段加密的手法。因为我们知道，密文的长度与密钥的长度是一样的。例如我们已经生成了一对1024位的密钥，假设我们使用`RSA_EncryptBySection`函数加密，并将`section_length`设置为64，那么我们在解密的时候就可以使用`RSA_EncryptBySection`函数并给`section_length`设置为256。原因很简单，我们的密文使用了十六进制来编码，所以256个字符实际上对应的是128字节，也就是1024位。用户请自行根据你的密钥长度来进行分段加密和解密。