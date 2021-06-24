#pragma once
#include <netinet/in.h>
#include <string>
#include <sys/prx.h>

#define INVALID_SOCKET -1
#define SOCKET_TIME_OUT 7000
#define min(a,b) (((a) < (b)) ? (a) : (b))

namespace libpsutil
{
	namespace network
	{
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
}