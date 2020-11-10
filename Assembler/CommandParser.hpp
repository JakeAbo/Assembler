#pragma once

#include "StringUtility.hpp"

namespace Assembler
{
	class CommandParsers
	{
		friend class Statment;

	private:
		static Command parseDataInstruction(std::vector<std::string> tokens)
		{
			tokens.erase(tokens.begin());

			tokens = StringUtility::splitByDelimeter<AssemblerTypes::LEX_COMMA>(StringUtility::unionTokens(tokens));

			std::vector<int> res = StringUtility::vecStoi(tokens);

			Command cmd;

			std::for_each(res.begin(), res.end(), [&cmd](int element) {
				cmd.addWord(std::move(Word().setNumber(element)));
				});

			return std::move(cmd);
		}

		static Command parseStringInstruction(const std::vector<std::string>& tokens)
		{
			return {};
		}
	};
}
