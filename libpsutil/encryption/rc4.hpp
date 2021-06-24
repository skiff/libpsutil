#pragma once

namespace libpsutil
{
	namespace encryption
	{
		int RC4(char* key, char* plaintext, unsigned char* ciphertext);
	}
}
