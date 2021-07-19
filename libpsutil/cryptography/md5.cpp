#include <string>
#include <cell\hash\libmd5.h>
#include "cryptography/md5.hpp"

namespace libpsutil
{
	namespace cryptography
	{
		void md5(void* data, size_t length, unsigned char* out)
		{
			cellMd5Digest(data, length, out);
		}
	}
}