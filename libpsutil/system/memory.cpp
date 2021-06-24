#include <string>
#include <sys/return_code.h>
#include "system/memory.hpp"
#include "system/syscalls.hpp"

namespace libpsutil
{
	namespace memory
	{
		uint8_t detour::hook_stub_section[0x10000] EXECUTABLE_SECTION;
		uint32_t detour::hook_count = 0;
		uint32_t detour::force_stub_addr = 0;

		bool get(uint32_t address, void* data, size_t length)
		{
			return sys_dbg_read_process_memory(address, data, length) == SUCCEEDED;
		}

		bool get(uint32_t address, std::vector<uint8_t>& bytes, size_t length)
		{
			bytes.resize(length);
			uint8_t* buffer = &bytes[0];
			return sys_dbg_read_process_memory(address, buffer, length) == SUCCEEDED;
		}

		bool set(uint32_t address, void* data, size_t length)
		{
			return sys_dbg_write_process_memory(address, data, length) == SUCCEEDED;
		}

		bool nop(uint32_t address)
		{
			return set<uint32_t>(address, 0x60000000) == SUCCEEDED;
		}

		bool blr(uint32_t address)
		{
			return set<uint32_t>(address, 0x4E800020) == SUCCEEDED;
		}

		void jump(uint32_t address, uint32_t destination, bool linked)
		{
			uint32_t instructions[4] = { 0 };

			instructions[0] = 0x3C000000 + ((destination >> 16) & 0xFFFF);
			instructions[1] = 0x60000000 + (destination & 0xFFFF);
			instructions[2] = 0x7C0903A6;
			instructions[3] = 0x4E800420 + (linked ? 1 : 0);

			memory::set(address, instructions, sizeof(uint32_t) * 4);
		}

		uint32_t get_game_toc()
		{
			uint32_t* entry_point = *reinterpret_cast<uint32_t**>(0x1001C); //ElfHeader->e_entry 
			return entry_point[1];
		}

		uint32_t detour::allocate_stub()
		{
			uint8_t* stub_section = this->hook_stub_section;
			if (detour::force_stub_addr != 0)
			{
				stub_section = reinterpret_cast<uint8_t*>(detour::force_stub_addr);
			}

			auto stub_address = reinterpret_cast<uint32_t>(&stub_section[this->hook_count * 0x80]);
			this->hook_count++;

			return stub_address;
		}

		uint32_t detour::resolve_branch(uint32_t instruction, uint32_t branch_address)
		{
			uint32_t offset = instruction & 0x3FFFFFC;

			if (offset & (1 << 25))
				offset |= 0xFC000000;

			return branch_address + offset;
		}

		void detour::force_stub_address(uint32_t address)
		{
			detour::force_stub_addr = address;
		}

		detour::detour(uint32_t address, void(*destination))
		{
			if (address == NULL) { return; }

			this->address = reinterpret_cast<uint32_t*>(address);
			auto* stub_address = reinterpret_cast<uint32_t*>(this->allocate_stub());

			memcpy(this->original_instructions, reinterpret_cast<void*>(address), 0x10);

			uint32_t instruction_count = 0;
			for (int i = 0; i < 4; i++)
			{
				const auto current_address = reinterpret_cast<uint32_t>(&stub_address[instruction_count]);
				if ((this->address[i] & 0xF8000000) == 0x48000000)
				{
					memory::jump(current_address, this->resolve_branch(this->address[i], (int)&this->address[i]), true);
					instruction_count += 4;
				}
				else
				{
					memory::set(current_address, &this->address[i], 4);
					instruction_count++;
				}
			}

			memory::jump(reinterpret_cast<uint32_t>(&stub_address[instruction_count]), address + 0x10, false);
			memory::jump(address, reinterpret_cast<uint32_t>(destination), false);

			this->stub_opd[0] = reinterpret_cast<uint32_t>(stub_address);
			this->stub_opd[1] = memory::get_game_toc();
		}

		detour::~detour()
		{
			memory::set(reinterpret_cast<uint32_t>(this->address), this->original_instructions, 0x10);
		}
	}
}