#include <ppu_intrinsics.h>
#include <sys/process.h>
#include <sys/syscall.h>
#include "system/syscalls.hpp"

namespace libpsutil
{
	bool use_hen_syscalls = false;

	uint32_t sys_hen_read_process_memory(uint64_t address, void* data, size_t size)
	{
		system_call_6(8, 0x7777, 0x31, (uint64_t)sys_process_getpid(), address, (uint64_t)data, size);
		return_to_user_prog(uint32_t);
	}

	uint32_t sys_hen_write_process_memory(uint64_t address, void* data, size_t size)
	{
		system_call_6(8, 0x7777, 0x32, (uint64_t)sys_process_getpid(), address, (uint64_t)data, size);
		return_to_user_prog(uint32_t);
	}

	uint32_t sys_dbg_read_process_memory(uint64_t address, void* data, size_t size)
	{
		system_call_4(904, (uint64_t)sys_process_getpid(), address, size, (uint64_t)data);
		return_to_user_prog(uint32_t);
	}

	uint32_t sys_dbg_write_process_memory(uint64_t address, void* data, size_t size)
	{
		system_call_4(905, (uint64_t)sys_process_getpid(), address, size, (uint64_t)data);
		return_to_user_prog(uint32_t);
	}

	uint32_t read_process_memory(uint64_t address, void* data, size_t size)
	{
		if (!use_hen_syscalls)
		{
			uint32_t read = sys_dbg_read_process_memory(address, data, size);
			if (read == SUCCEEDED)
			{
				return read;
			}
		}

		use_hen_syscalls = true;
		return sys_hen_read_process_memory(address, data, size);
	}

	uint32_t write_process_memory(uint64_t address, void* data, size_t size)
	{
		if (!use_hen_syscalls)
		{
			uint32_t write = sys_dbg_write_process_memory(address, data, size);
			if (write == SUCCEEDED)
			{
				return write;
			}
		}

		use_hen_syscalls = true;
		return sys_hen_write_process_memory(address, data, size);
	}

	void sleep(uint64_t milliseconds)
	{
		system_call_1(SYS_TIMER_USLEEP, milliseconds * 1000);
	}
}