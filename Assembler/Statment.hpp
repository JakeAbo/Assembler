#pragma once

#include <regex>
#include <optional>
#include <map>
#include <functional>
#include <memory>
#include <utility>
#include <variant>

#include "Command.hpp"
#include "StringUtility.hpp"
#include "CommandParser.hpp"
#include "Symbol.hpp"

namespace Assembler
{
	class Statment
	{
	private:
		std::variant<Command, Symbol> _result;
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

			std::regex reg(AssemblerTypes::REGEX_SYMBOL_VALIDATE_COLON);
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
			typedef std::function<std::variant<Command, Symbol>(const std::vector<std::string>&)> instructionFunctor;
			static std::map<std::string, instructionFunctor> commandParsers;
			if(commandParsers.empty())
			{
				commandParsers[".data"] = std::bind(&CommandParsers::parseDataInstruction, std::placeholders::_1);
				commandParsers[".string"] = std::bind(&CommandParsers::parseStringInstruction, std::placeholders::_1);
				commandParsers[".entry"] = std::bind(&CommandParsers::parseEntryInstruction, std::placeholders::_1);
				commandParsers[".extern"] = std::bind(&CommandParsers::parseExternInstruction, std::placeholders::_1);
				commandParsers["mov"] = std::bind(&CommandParsers::parseDataInstruction, std::placeholders::_1);
				commandParsers["cmp"] = std::bind(&CommandParsers::parseDataInstruction, std::placeholders::_1);
				commandParsers["add"] = std::bind(&CommandParsers::parseDataInstruction, std::placeholders::_1);
				commandParsers["sub"] = std::bind(&CommandParsers::parseDataInstruction, std::placeholders::_1);
				commandParsers["not"] = std::bind(&CommandParsers::parseDataInstruction, std::placeholders::_1);
				commandParsers["clr"] = std::bind(&CommandParsers::parseDataInstruction, std::placeholders::_1);
				commandParsers["lea"] = std::bind(&CommandParsers::parseDataInstruction, std::placeholders::_1);
				commandParsers["inc"] = std::bind(&CommandParsers::parseDataInstruction, std::placeholders::_1);
				commandParsers["dec"] = std::bind(&CommandParsers::parseDataInstruction, std::placeholders::_1);
				commandParsers["jmp"] = std::bind(&CommandParsers::parseDataInstruction, std::placeholders::_1);
				commandParsers["bne"] = std::bind(&CommandParsers::parseDataInstruction, std::placeholders::_1);
				commandParsers["red"] = std::bind(&CommandParsers::parseDataInstruction, std::placeholders::_1);
				commandParsers["prn"] = std::bind(&CommandParsers::parseDataInstruction, std::placeholders::_1);
				commandParsers["jsr"] = std::bind(&CommandParsers::parseDataInstruction, std::placeholders::_1);
				commandParsers["rts"] = std::bind(&CommandParsers::parseDataInstruction, std::placeholders::_1);
				commandParsers["stop"] = std::bind(&CommandParsers::parseDataInstruction, std::placeholders::_1);
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
			
			try
			{
				_result = commandParsers.at(tokens[0])(tokens);
			} 
			catch (const AssemblerException & ex)
			{
				_exception = ex.what();
				return;
			}
		}

	public:
		Statment(const std::string asmStmt)
			: _asmStmt(asmStmt)
		{

		}

		void parse()
		{
			try
			{
				if (_asmStmt.length() > AssemblerTypes::LINE_MAX_LENGTH)
					throw AssemblerExceptionLineOverflow();

				_asmStmt = StringUtility::deleteComments(_asmStmt);
				std::vector<std::string> tokens = StringUtility::splitBySpacesAndTabs(_asmStmt);

				if (isEmptyStmt(tokens.size())) return;
				if (isCommentStmt(tokens[0])) return;

				checkForLabel(tokens);

				if (_symbol.has_value())
				{
					tokens = StringUtility::splitByDelimeter<AssemblerTypes::LEX_COLON>(_asmStmt);

					if (tokens.size() == 1)
					{
						_symbol = {};
						return;
					}

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

		const std::optional<Command> getCommand()
		{
			try
			{
				return { std::get<Command>(_result) };
			}
			catch (const std::bad_variant_access&)
			{
				return {};
			}
		}

		const std::optional<Symbol> getCommandSymbol()
		{
			try
			{
				return { std::get<Symbol>(_result) };
			}
			catch (const std::bad_variant_access&)
			{
				return {};
			}
		}

		bool isEmptyOrComment()
		{
			return !_cmd.has_value();
		}
	};
}
