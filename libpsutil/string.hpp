#pragma once
#include <string>
#ifdef vector
#undef vector
#endif
#include <vector>

namespace libpsutil
{
	class string : public std::string
	{
	public:
		static const char* va(const char* fmt, ...);

		static std::string to_lower(const std::string& text);
		static std::string to_upper(const std::string& text);
		static bool begins_with(const std::string& text, const std::string& search);
		static bool ends_with(const std::string& text, const std::string& search);
		static std::vector<std::string> split(const std::string& text, char delimiter);

		std::string to_lower();
		std::string to_upper();
		bool begins_with(const std::string& search);
		bool ends_with(const std::string& search);
		std::vector<std::string> split(char delimiter);
	};
}