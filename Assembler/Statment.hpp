#pragma once

#include <regex>
#include <optional>

#include "Command.hpp"
#include "StringUtility.hpp"

namespace Assembler
{
	class Statment
	{
	private:
		std::string _asmStmt;
		Command _cmd;
		std::optional<std::string> _symbol;

		bool isEmptyStmt(size_t len)
		{
			return !len;
		}

		bool isCommentStmt(const std::string& firstToken)
		{
			return firstToken[0] == ';';
		}

		bool isSavedWord(const std::string& token)
		{
			return (!AssemblerTypes::getRegister(token).has_value() && 
				!AssemblerTypes::getOpCode(token).has_value());
		}

		void checkForLabel(const std::vector<std::string>& tokens)
		{
			std::ostringstream os;

			os << tokens[0];

			if (tokens[0][tokens[0].length() - 1] != ':')
			{
				os << tokens[1][0];
			}

			std::regex reg(StringUtility::REGEX_SYMBOL_VALIDATE);
			if (std::regex_match(os.str(), reg) && isSavedWord(os.str()))
			{
				_symbol = os.str();
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
				throw AssemblerExceptionLineOverflow();

			std::vector<std::string> tokens = StringUtility::splitBySpacesAndTabs(_asmStmt);

			if (isEmptyStmt(tokens.size())) return;
			if (isCommentStmt(tokens[0])) return;
			
			checkForLabel(tokens);

			if (_symbol.has_value())
			{
				tokens = StringUtility::splitByDelimeter(_asmStmt, ":");
				
				if(tokens.size() > 1)
					tokens = StringUtility::splitBySpacesAndTabs(tokens[1]);
			}
			
		}
	};
}
