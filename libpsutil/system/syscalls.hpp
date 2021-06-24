#pragma once

#include <sys/prx.h>

namespace libpsutil
{
	uint32_t read_process_memory(uint64_t address, void* data, size_t size);
	uint32_t write_process_memory(uint64_t address, void* data, size_t size);
	void sleep(uint64_t milliseconds);
}