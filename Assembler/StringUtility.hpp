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
		friend class CommandParsers;

	private:	
		template<char delimeter>
		class WordDelimitedBy : public std::string
		{
			friend std::istream& operator>>(std::istream& is, WordDelimitedBy& output)
			{
				std::getline(is, output, delimeter);
				return is;
			}
		};

		static std::vector<std::string> splitBySpacesAndTabs(std::string const& input)
		{
			std::istringstream buffer(input);
			std::vector<std::string> ret((std::istream_iterator<std::string>(buffer)),
				std::istream_iterator<std::string>());
			return ret;
		}

		template<char delimeter>
		static std::vector<std::string> splitByDelimeter(const std::string& input)
		{
			std::istringstream buffer(input);
			std::vector<std::string> ret((std::istream_iterator<WordDelimitedBy<delimeter>>(buffer)),
				std::istream_iterator<WordDelimitedBy<delimeter>>());
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
		
		static std::string unionTokens(const std::vector<std::string>& tokens)
		{
			std::ostringstream os;
			for (const auto& token : tokens)
			{
				os << token;
			}

			return os.str();
		}

		static std::vector<int> vecStoi(const std::vector<std::string>& tokens)
		{
			std::vector<int> res;

			for (const auto& token : tokens)
			{
				int value;
				try
				{
					value = std::stoi(token);
				} 
				catch (const std::invalid_argument&)
				{
					throw AssemblerExceptionInvalidArgument();
				}
				res.emplace_back(std::move(value));
			}

			return res;
		}
	
		static std::string deleteComments(const std::string& stmt)
		{
			auto res = splitByDelimeter<AssemblerTypes::LEX_COMMENT_SIGN>(stmt);
			return (res.empty() ? stmt : res[0]);
		}
	};
}
