#pragma once

#include <regex>
#include <optional>
#include <map>
#include <functional>
#include <memory>
#include <utility>

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
	
		void parseCommand(const std::vector<std::string>& tokens)
		{
			typedef std::function<void(const std::vector<std::string>&)> instructionFunctor;
			static std::map<std::string, instructionFunctor> commandParsers;
			if(commandParsers.empty())
			{
				commandParsers[".data"] = std::bind(&Statment::parseDataInstruction, this, std::placeholders::_1);
				commandParsers[".string"] = std::bind(&Statment::parseStringInstruction, this, std::placeholders::_1);
				commandParsers[".entry"] = std::bind(&Statment::parseDataInstruction, this, std::placeholders::_1);
				commandParsers[".extern"] = std::bind(&Statment::parseDataInstruction, this, std::placeholders::_1);
				commandParsers["mov"] = std::bind(&Statment::parseDataInstruction, this, std::placeholders::_1);
				commandParsers["cmp"] = std::bind(&Statment::parseDataInstruction, this, std::placeholders::_1);
				commandParsers["add"] = std::bind(&Statment::parseDataInstruction, this, std::placeholders::_1);
				commandParsers["sub"] = std::bind(&Statment::parseDataInstruction, this, std::placeholders::_1);
				commandParsers["not"] = std::bind(&Statment::parseDataInstruction, this, std::placeholders::_1);
				commandParsers["clr"] = std::bind(&Statment::parseDataInstruction, this, std::placeholders::_1);
				commandParsers["lea"] = std::bind(&Statment::parseDataInstruction, this, std::placeholders::_1);
				commandParsers["inc"] = std::bind(&Statment::parseDataInstruction, this, std::placeholders::_1);
				commandParsers["dec"] = std::bind(&Statment::parseDataInstruction, this, std::placeholders::_1);
				commandParsers["jmp"] = std::bind(&Statment::parseDataInstruction, this, std::placeholders::_1);
				commandParsers["bne"] = std::bind(&Statment::parseDataInstruction, this, std::placeholders::_1);
				commandParsers["red"] = std::bind(&Statment::parseDataInstruction, this, std::placeholders::_1);
				commandParsers["prn"] = std::bind(&Statment::parseDataInstruction, this, std::placeholders::_1);
				commandParsers["jsr"] = std::bind(&Statment::parseDataInstruction, this, std::placeholders::_1);
				commandParsers["rts"] = std::bind(&Statment::parseDataInstruction, this, std::placeholders::_1);
				commandParsers["stop"] = std::bind(&Statment::parseDataInstruction, this, std::placeholders::_1);
			}

			/* Check if there is no command declared */
			if (tokens.size() == 0)
			{
				_symbol = {};
				return;
			}

			if (commandParsers.find(tokens[0]) == commandParsers.end())
			{
				_symbol = {};
				throw AssemblerExceptionUnknownInstruction();
			}
			
			commandParsers.at(tokens[0])(tokens);
		}

		void parseDataInstruction(const std::vector<std::string>& tokens)
		{
			std::ostringstream os;
			for (int i = 1; i < tokens.size(); i++)
			{
				os << tokens[i];
			}

			std::vector<std::string> tokensData = StringUtility::splitByDelimeter(os.str(), ",");
		}

		void parseStringInstruction(const std::vector<std::string>& tokens)
		{

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

				parseCommand(tokens);
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
