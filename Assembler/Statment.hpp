#pragma once

#include "Command.hpp"
#include "StringUtility.hpp"
#include <regex>

namespace Assembler
{
	class Statment
	{
	private:
		std::string _asmStmt;
		Command _cmd;

		bool isEmptyStmt(size_t len)
		{
			return !len;
		}

		bool isCommentStmt(const std::string& firstToken)
		{
			return firstToken[0] == ';';
		}

		bool isFirstTokenLabel(const std::vector<std::string>& tokens)
		{
			std::ostringstream os;

			os << tokens[0];

			if (tokens[0][tokens[0].length()] != ':')
			{
				os << tokens[1][0];
			}


			std::regex reg("^[a-zA-Z][a-zA-Z0-9]{1,31}$");
			std::regex reg1("^[a-zA-Z][a-zA-Z0-9]{1,32}[:]$");
			if (std::regex_match(tokens[0], reg))
			{
				if (tokens.size() > 2)
				{
					std::regex reg2("^[:]$");
					if (std::regex_match(tokens[1], reg2))
					{
						return true;
					}
				}
			}
		}

	public:
		Statment(const std::string asmStmt)
			: _asmStmt(asmStmt), _cmd()
		{

		}

		void parse()
		{
			if (_asmStmt.length() > 80)
				throw new AssemblerExceptionLineOverflow();

			std::vector<std::string> tokens = StringUtility::splitBySpacesAndTabs(_asmStmt);

			if (isEmptyStmt(tokens.size())) return;
			if (isCommentStmt(tokens[0])) return;
			
			if (isFirstTokenLabel(tokens))
			{

			}


			for (const auto& token : tokens)
			{

			}
		}
	};
}
