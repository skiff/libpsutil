#include <sys/process.h>
#include <sys/syscall.h>
#include "system/syscalls.hpp"

namespace libpsutil
{
	uint32_t sys_dbg_read_process_memory(uint64_t address, void* data, size_t size)
	{
		system_call_6(8, 0x7777, 0x31, (uint64_t)sys_process_getpid(), address, (uint64_t)data, size);
		return_to_user_prog(uint32_t);
	}

	uint32_t sys_dbg_write_process_memory(uint64_t address, void* data, size_t size)
	{
		system_call_6(8, 0x7777, 0x32, (uint64_t)sys_process_getpid(), address, (uint64_t)data, size);
		return_to_user_prog(uint32_t);
	}

	void sleep(uint64_t milliseconds)
	{
		system_call_1(SYS_TIMER_USLEEP, milliseconds * 1000);
	}
}