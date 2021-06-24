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

			size_t pos = 0;
			std::string space = " ";
			while ((pos = query.find(space, pos)) != std::string::npos)
				query.replace(pos, space.length(), "%20");

			char response[1024] = { 0 };
			char request[1024] = { 0 };
			sprintf(request, "GET %s HTTP/1.1\nHost: %s\r\n\r\n", query.data(), url.data());

			socket* http = new socket(ip, port);
			auto success = http->connect();
			if (success)
			{
				success = http->send(request, strlen(request) + 1);
				if (success)
				{
					success = http->receive(response, 1024);
				}
			}

			http->close();
			delete http;

			return success ? response : "";
		}
	}
}