#include <string>
#include <cell\hash\libmd5.h>
#include "cryptography/md5.hpp"

namespace libpsutil
{
	namespace cryptography
	{
		void md5(void* data, size_t length, unsigned char* out)
		{
			CellMd5WorkArea workArea;

			unsigned char* digest = new unsigned char[CELL_MD5_DIGEST_SIZE];
			cellMd5BlockInit(&workArea);
			cellMd5BlockUpdate(&workArea, data, length);
			cellMd5BlockResult(&workArea, digest);

			memcpy(out, digest, CELL_MD5_DIGEST_SIZE);

			delete[] digest;
		}
	}
}