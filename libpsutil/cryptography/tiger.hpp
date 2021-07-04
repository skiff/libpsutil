#pragma once

namespace libpsutil
{
	namespace cryptography
	{
		void tiger64(char* str, size_t length, uint64_t* res);
		void tiger128(char* str, size_t length, uint64_t res[2]);
		void tiger192(char* str, size_t length, uint64_t res[3]);
	}
}
