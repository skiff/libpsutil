#pragma once
#include <string>
#ifdef vector
#undef vector
#endif
#include <vector>

namespace libpsutil
{
	namespace string
	{
		const char* va(const char* fmt, ...);

		std::string to_lower(const std::string& text);
		std::string to_upper(const std::string& text);
		bool begins_with(const std::string& text, const std::string& search);
		bool ends_with(const std::string& text, const std::string& search);
		std::vector<std::string> split(const std::string& text, char delimiter);
	};
}