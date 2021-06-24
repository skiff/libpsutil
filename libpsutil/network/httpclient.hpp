#pragma once
#include <string>

namespace libpsutil
{
	namespace network
	{
		std::string http_get(const std::string& url, std::string query, uint16_t port = 80);
	}
}