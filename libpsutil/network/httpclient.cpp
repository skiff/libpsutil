#include <netdb.h>
#include "network/httpclient.hpp"
#include "network/socket.hpp"
#include "system/imports.hpp"

namespace libpsutil
{
	namespace network
	{
		std::string http_get(const std::string& url, std::string query, uint16_t port)
		{
			auto* host = gethostbyname(url.data());
			auto ip = *((uint32_t*)host->h_addr);

			socket* http = new socket(ip, port);

			size_t pos = 0, sent = 0;
			std::string space = " ";
			while ((pos = query.find(space, pos)) != std::string::npos)
				query.replace(pos, space.length(), "%20");

			char response[1024] = { 0 };
			char request[1024] = { 0 };
			sprintf(request, "GET %s HTTP/1.1\nHost: localhost\nContent-Length: 1024\n\r\n\r\n", query.data());

			auto success = http->send(request, 1024);
			if (success)
			{
				success = http->receive(response, 1024);
			}

			http->close();
			delete http;

			return success ? response : "";
		}
	}
}