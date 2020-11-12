#pragma once

#include "StringUtility.hpp"
#include "Symbol.hpp"

namespace Assembler
{
	class CommandParsers
	{
		friend class Statment;

	private:
		static Command parseDataInstruction(std::vector<std::string> tokens)
		{
			tokens.erase(tokens.begin());

			auto unitedArguemts = StringUtility::unionTokens(tokens);
			if (!std::regex_match(unitedArguemts, std::regex(AssemblerTypes::REGEX_DATA_ARG_VALIDATE)))
				throw AssemblerExceptionInvalidArgument();
			
			tokens = StringUtility::splitByDelimeter<AssemblerTypes::LEX_COMMA>(unitedArguemts);
						
			std::vector<int> res = StringUtility::vecStoi(tokens);

			Command cmd;

			std::for_each(res.begin(), res.end(), [&cmd](int element) {
				cmd.addWord(std::move(Word().setNumber(element)));
				});

			return std::move(cmd);
		}

		static Command parseStringInstruction(std::vector<std::string> tokens)
		{
			tokens.erase(tokens.begin());

			auto unitedArguemts = StringUtility::unionTokens(tokens);
			if (!std::regex_match(unitedArguemts, std::regex(AssemblerTypes::REGEX_STRING_ARG_VALIDATE)))
				throw AssemblerExceptionInvalidArgument();

			tokens = StringUtility::splitByDelimeter<AssemblerTypes::LEX_QUOTATION>(unitedArguemts);

			Command cmd;

			std::for_each(tokens[1].begin(), tokens[1].end(), [&cmd](char element) {
				cmd.addWord(std::move(Word().setAscii(element)));
				});

			cmd.addWord(std::move(Word().setAscii('\0')));

			return std::move(cmd);
		}

		static Symbol parseEntryInstruction(std::vector<std::string> tokens)
		{
			tokens.erase(tokens.begin());
			
			if (tokens.size() < 1)
				throw AssemblerExceptionMissingArgument();
			else if(tokens.size() > 1)
				throw AssemblerExceptionTooManyArguments();
			
			if (!std::regex_match(tokens[0], std::regex(AssemblerTypes::REGEX_SYMBOL_VALIDATE)))
				throw AssemblerExceptionInvalidArgument();

			return Symbol(tokens[0], SymbolType::ENTRY, -1);
		}

		static Symbol parseExternInstruction(std::vector<std::string> tokens)
		{
			tokens.erase(tokens.begin());

			if (tokens.size() < 1)
				throw AssemblerExceptionMissingArgument();
			else if (tokens.size() > 1)
				throw AssemblerExceptionTooManyArguments();

			if (!std::regex_match(tokens[0], std::regex(AssemblerTypes::REGEX_SYMBOL_VALIDATE)))
				throw AssemblerExceptionInvalidArgument();

			return Symbol(tokens[0], SymbolType::EXTERN, -1);
		}
	};
}
