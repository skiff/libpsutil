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
			unsigned char* digest = new unsigned char[CELL_SHA1_DIGEST_SIZE];
			cellSha1Digest(data, length, digest);

			memcpy(out, digest, CELL_SHA1_DIGEST_SIZE);

			delete[] digest;
		}

		void sha256(void* data, size_t length, unsigned char* out)
		{
			unsigned char* digest = new unsigned char[CELL_SHA256_DIGEST_SIZE];
			cellSha256Digest(data, length, digest);

			memcpy(out, digest, CELL_SHA256_DIGEST_SIZE);

			delete[] digest;
		}

		void sha512(void* data, size_t length, unsigned char* out)
		{
			unsigned char* digest = new unsigned char[CELL_SHA512_DIGEST_SIZE];
			cellSha512Digest(data, length, digest);

			memcpy(out, digest, CELL_SHA512_DIGEST_SIZE);

			delete[] digest;
		}
	}
}