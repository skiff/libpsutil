#pragma once

#include <netinet/in.h>
#include <stdarg.h>
#include <string>
#include <sys/prx.h>
#ifdef vector
#undef vector
#endif
#include <vector>

extern "C"
{
	int	_sys_printf(const char* format, ...);
	int	_sys_sprintf(char* s, const char* format, ...);
	int	_sys_vsprintf(char* s, const char* format, va_list arg);

	void* _sys_malloc(size_t n);
	void _sys_free(void* ptr);
}

#define printf			_sys_printf
#define sprintf			_sys_sprintf
#define vsprintf		_sys_vsprintf

namespace libpsutil
{
	uint32_t sys_dbg_read_process_memory(uint64_t address, void* data, size_t size);
	uint32_t sys_dbg_write_process_memory(uint64_t address, void* data, size_t size);
	void sleep(uint64_t milliseconds);
	
	namespace string
	{
		const char* va(const char* fmt, ...);

		std::string to_lower(const std::string& text);
		std::string to_upper(const std::string& text);
		bool begins_with(const std::string& text, const std::string& search);
		bool ends_with(const std::string& text, const std::string& search);
		std::vector<std::string> split(const std::string& text, char delimiter);
	};
	
	namespace cryptography
	{
		int rc4(char* key, char* plaintext, unsigned char* ciphertext);
		void md5(void* data, size_t length, unsigned char* digest);
		void sha1(void* data, size_t length, unsigned char* out);
		void sha256(void* data, size_t length, unsigned char* out);
		void sha512(void* data, size_t length, unsigned char* out);
		void tiger64(char* str, size_t length, uint64_t* res);
		void tiger128(char* str, size_t length, uint64_t res[2]);
		void tiger192(char* str, size_t length, uint64_t res[3]);
	}
	
	namespace filesystem
    {
		bool read_file(const std::string& file_name, void* data, size_t size);
		std::string read_file(const std::string& file_name);
		bool write_file(const std::string& file_name, void* data, size_t size);
		bool write_file(const std::string& file_name, const std::string& data);
        int64_t get_file_size(const std::string& file_name);

        bool directory_exists(const std::string& directory_name);
        bool file_exists(const std::string& file_name);

        void create_directory(const std::string& directory_name);
    }
	
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
			return set(address, (void*)list.data(), list.size() * sizeof(T));
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
	
	namespace network
	{
		std::string http_get(const std::string& url, std::string query, uint16_t port = 80);
		
		enum socket_type
		{
			SOCKET_TYPE_TCP,
			SOCKET_TYPE_UDP
		};

		class socket
		{
		private:
			int socket_;
			bool connected_;
			uint32_t ip_;
			uint16_t port_;
			socket_type type_;
			sockaddr_in server_addr;

		public:
			socket(const std::string& ip, uint16_t port, socket_type type = SOCKET_TYPE_TCP);
			socket(uint32_t ip, uint16_t port, socket_type type = SOCKET_TYPE_TCP);

			void close();
			bool connect();
			bool receive(void* data, size_t length);
			bool send(const void* data, size_t length);
		};
	}
	
	namespace math
	{
		int atoi(char* str);
		float atof(char* str);

		void srand(uint32_t seed);
		uint32_t rand();

		class vec2_t
		{
		public:
			float x, y;

			vec2_t();
			vec2_t(float x, float y);
			vec2_t(float vec[2]);

			vec2_t operator+(const vec2_t vec);
			vec2_t operator+(const float* vec);
			vec2_t operator-(const vec2_t vec);
			vec2_t operator-(const float* vec);
			vec2_t operator-() const;
			vec2_t operator*(const vec2_t vec);
			vec2_t operator*(const float scalar);

			void operator-=(const vec2_t vec);
			void operator+=(const vec2_t vec);
			void operator*=(const vec2_t vec);
			void operator*=(const float scalar);

			bool operator==(const vec2_t vec);
			bool operator==(const float value);
			bool operator!=(const vec2_t vec);
			bool operator!=(const float value);

			operator float* ();
		};

		class vec3_t
		{
		public:
			float x, y, z;

			vec3_t();
			vec3_t(float x, float y, float z);
			vec3_t(float vec[3]);

			vec3_t operator+(const vec3_t vec);
			vec3_t operator+(const float* vec);
			vec3_t operator-(const vec3_t vec);
			vec3_t operator-(const float* vec);
			vec3_t operator-() const;
			vec3_t operator*(const vec3_t vec);
			vec3_t operator*(const float scalar);

			void operator-=(const vec3_t vec);
			void operator+=(const vec3_t vec);
			void operator*=(const vec3_t vec);
			void operator*=(const float scalar);

			bool operator==(const vec3_t vec);
			bool operator==(const float value);
			bool operator!=(const vec3_t vec);
			bool operator!=(const float value);

			operator float* ();

			vec3_t forward(float x = 1.0f);
			vec3_t normalize();
			float distance(vec3_t vec);
			float length();
			void vectors(vec3_t* forward, vec3_t* right, vec3_t* up);
		};

		class vec4_t
		{
		public:
			float x, y, z, w;

			vec4_t();
			vec4_t(float x, float y, float z, float w);
			vec4_t(float vec[4]);

			vec4_t operator+(const vec4_t vec);
			vec4_t operator+(const float* vec);
			vec4_t operator-(const vec4_t vec);
			vec4_t operator-(const float* vec);
			vec4_t operator-() const;
			vec4_t operator*(const vec4_t vec);
			vec4_t operator*(const float scalar);

			void operator-=(const vec4_t vec);
			void operator+=(const vec4_t vec);
			void operator*=(const vec4_t vec);
			void operator*=(const float scalar);

			bool operator==(const vec4_t vec);
			bool operator==(const float value);
			bool operator!=(const vec4_t vec);
			bool operator!=(const float value);

			operator float* ();
		};
	}
	
    namespace symbol_helper
    {
        void* get_symbol(unsigned int address);
    }

    template<typename T> class symbol
    {
    public:
        operator T* ()
        {
            T* type = *reinterpret_cast<T*>(this->mp_object_);
            return (decltype(type))symbol_helper::get_symbol(this->mp_object_);
        }

        T* get()
        {
            return this->mp_object_;
        }

        int mp_object_;
    };
}