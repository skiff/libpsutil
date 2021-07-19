#include <string>
#include <cell\hash\libsha1.h>
#include <cell\hash\libsha256.h>
#include <cell\hash\libsha512.h>
#include "cryptography/sha.hpp"

namespace libpsutil
{
	namespace cryptography
	{
		void sha1(void* data, size_t length, unsigned char* out)
		{
			cellSha1Digest(data, length, out);
		}

		void sha256(void* data, size_t length, unsigned char* out)
		{
			cellSha256Digest(data, length, out);
		}

		void sha512(void* data, size_t length, unsigned char* out)
		{
			cellSha512Digest(data, length, out);
		}
	}
}