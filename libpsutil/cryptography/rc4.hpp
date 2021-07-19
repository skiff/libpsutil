#pragma once

namespace libpsutil
{
	namespace cryptography
	{
		int rc4(char* key, char* plaintext, unsigned char* ciphertext);
	}
}
