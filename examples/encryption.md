# Encryption
Currently, the only encryption algorithm support is RC4

```
void encrypt_text(char* text, char* key, char* output)
{
    libpsutil::encryption::RC4(key, text, (unsigned char*)output);
}
```
