# Cryptography
RC4
```
void encrypt_text(char* text, char* key, char* output)
{
    libpsutil::encryption::rc4(key, text, (unsigned char*)output);
}
```

SHA1,SHA256,SHA512
```
void hash_text(char* text)
{
	char output1[CELL_SHA1_DIGEST_SIZE] = { 0 };
    libpsutil::encryption::sha1(text, strlen(text) + 1, output1);
	
	char output256[CELL_SHA256_DIGEST_SIZE] = { 0 };
    libpsutil::encryption::sha256(text, strlen(text) + 1, output256);
	
	char output512[CELL_SHA512_DIGEST_SIZE] = { 0 };
    libpsutil::encryption::sha512(text, strlen(text) + 1, output512);
}
```

MD5
```
void hash_text(char* text)
{
	char output[CELL_MD5_DIGEST_SIZE] = { 0 };
    libpsutil::encryption::md5(text, strlen(text) + 1, output);
}
```
