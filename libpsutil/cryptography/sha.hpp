#pragma once

namespace libpsutil
{
	namespace cryptography
	{
		void sha1(void* data, size_t length, unsigned char* out);
		void sha256(void* data, size_t length, unsigned char* out);
		void sha512(void* data, size_t length, unsigned char* out);
	}
}
