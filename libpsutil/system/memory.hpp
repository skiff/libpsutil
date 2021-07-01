#pragma once
#include <sys/prx.h>
#ifdef vector
#undef vector
#endif
#include <vector>

namespace libpsutil
{
	namespace memory
	{
		bool get(uint32_t address, void* data, size_t length);
		bool get(uint32_t address, std::vector<uint8_t>& bytes, size_t length);
		bool set(uint32_t address, void* data, size_t length);

		bool nop(uint32_t address);
		bool blr(uint32_t address);

		void jump(uint32_t address, uint32_t destination, bool linked = false);
		void jump_safe(uint32_t address, uint32_t destination, bool linked = false);

		uint32_t get_game_toc();

		template<class T> T get(uint32_t address)
		{
			T data;
			get(address, &data, sizeof(T));
			return data;
		}

		template<class T> std::vector<T> get(uint32_t address, size_t length)
		{
			std::vector<T> data;
			data.resize(length * sizeof(T));
			get(address, &data[0], length * sizeof(T));
			return data;
		}

		template<class T> bool set(uint32_t address, T data)
		{
			return set(address, &data, sizeof(T));
		}

		template<class T> bool set(uint32_t address, std::initializer_list<T> list)
		{
			return set(address, reinterpret_cast<void*>(list.data()), list.size() * sizeof(T));
		}

		template <typename T> T byte_swap(T u)
		{
			union
			{
				T u;
				unsigned char u8[sizeof(T)];
			} source, dest;

			source.u = u;

			for (size_t k = 0; k < sizeof(T); k++)
				dest.u8[k] = source.u8[sizeof(T) - k - 1];

			return dest.u;
		}

		class detour
		{
		private:
			static uint8_t hook_stub_section[0x10000] __attribute__((section(".text")));
			static uint32_t hook_count;
			static uint32_t force_stub_addr;

			uint32_t* address;
			uint32_t stub_opd[2];
			uint32_t original_instructions[4];

			uint32_t allocate_stub();
			uint32_t resolve_branch(uint32_t instruction, uint32_t branch_address);
			void setup_detour(uint32_t address, void* destination, uint32_t toc_override);

		public:
			template<class T> detour(uint32_t address, T(*destination), uint32_t toc_override = 0)
			{
				this->setup_detour(address, reinterpret_cast<void*>(destination), toc_override);
			}

			~detour();

			static void force_stub_address(uint32_t address);

			template<typename T = void, typename... params> T invoke(params... parameters)
			{
				T(*original)(params...) = (T(*)(params...))this->stub_opd;
				return original(parameters...);
			}
		};
	}
}