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
		std::optional<Command> _cmd;
		std::optional<std::string> _symbol;
		std::optional<std::string> _exception;

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
			return (AssemblerTypes::checkIfSavedReg(token).has_value() || 
				AssemblerTypes::getOpCode(token).has_value());
		}

		void checkForLabel(const std::vector<std::string>& tokens)
		{
			bool flag = true;

			std::ostringstream os;

			os << tokens[0];

			if (tokens[0][tokens[0].length() - 1] != ':' && tokens.size() > 1)
			{
				os << tokens[1][0];
			}

			std::regex reg(StringUtility::REGEX_SYMBOL_VALIDATE);
			if (std::regex_match(os.str(), reg))
			{
				std::string labelWithoutColon = os.str();
				labelWithoutColon.pop_back();
				if (!isSavedWord(labelWithoutColon))
				{
					_symbol = labelWithoutColon;
					flag = false;
				}
			}
			else
			{
				flag = (os.str().back() == ':');
			}
			
			if(flag)
			{
				throw AssemblerExceptionSyntaxSymbol();
			}
		}

		void checkForDataInstructionCommand(const std::vector<std::string>& tokens)
		{
			if(!AssemblerTypes::getDataType(tokens[0]).has_value()) 
				return;
			
			AssemblerTypes::DataInstructionType dit = AssemblerTypes::getDataType(tokens[0]).value();
			if (dit == AssemblerTypes::DataInstructionType::DATA)
			{
				std::ostringstream os;
				for (int i = 1; i < tokens.size(); i++)
				{
					os << tokens[i];
				}

				std::vector<std::string> tokensData = StringUtility::splitByDelimeter(os.str(), ",");

			}
		}

	public:
		Statment(const std::string asmStmt)
			: _asmStmt(asmStmt), _cmd()
		{

		}

		void parse()
		{
			try
			{
				if (_asmStmt.length() > AssemblerTypes::LINE_MAX_LENGTH)
					throw AssemblerExceptionLineOverflow();

				std::vector<std::string> tokens = StringUtility::splitBySpacesAndTabs(_asmStmt);

				if (isEmptyStmt(tokens.size())) return;
				if (isCommentStmt(tokens[0])) return;

				checkForLabel(tokens);

				if (_symbol.has_value())
				{
					tokens = StringUtility::splitByDelimeter(_asmStmt, ":");

					if (tokens.size() > 1)
						tokens = StringUtility::splitBySpacesAndTabs(tokens[1]);
				}

				checkForDataInstructionCommand(tokens);
			} 
			catch (const AssemblerException & ex)
			{
				_exception = ex.what();
			}
		}

		const std::optional<std::string>& getSymbol()
		{
			return _symbol;
		}

		const std::optional<std::string>& getException()
		{
			return _exception;
		}

		bool isEmptyOrComment()
		{
			return !_cmd.has_value();
		}
	};
}
