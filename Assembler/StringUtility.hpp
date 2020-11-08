#pragma once

#include <vector>
#include <string>
#include <istream>
#include <iterator>

namespace Assembler
{
	class StringUtility
	{
		friend class Statment;

	private:
		static constexpr auto REGEX_SYMBOL_VALIDATE = "^[a-zA-Z][a-zA-Z0-9]{0,30}[:]$"; 

		static std::vector<std::string> splitBySpacesAndTabs(std::string const& input) {
			std::istringstream buffer(input);
			std::vector<std::string> ret((std::istream_iterator<std::string>(buffer)),
				std::istream_iterator<std::string>());
			return ret;
		}

		static std::vector<std::string> splitByDelimeter(const std::string& str, const std::string& delim)
		{
			std::vector<std::string> tokens;
			size_t prev = 0, pos = 0;
			do
			{
				pos = str.find(delim, prev);
				if (pos == std::string::npos) pos = str.length();
				std::string token = str.substr(prev, pos - prev);
				if (!token.empty()) tokens.push_back(token);
				prev = pos + delim.length();
			} while (pos < str.length() && prev < str.length());
			return tokens;
		}
	};
}
