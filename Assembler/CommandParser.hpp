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

		static Command parse2OperandOperation(std::vector<std::string> tokens)
		{
			Command res;
			Word opt, opr1, opr2;
			bool isFirstOperandReg, isSecondOperandReg;
			
			isFirstOperandReg = isSecondOperandReg = false;
			AssemblerTypes::Operation op = AssemblerTypes::getOpCode(tokens[0]).value();

			opt.setAbsolute().setOpCodeAny(AssemblerTypes::getOpCode(tokens[0]).value());

			tokens.erase(tokens.begin());

			auto unitedArguemts = StringUtility::unionTokens(tokens);
			tokens = StringUtility::splitByDelimeter<AssemblerTypes::LEX_COMMA>(unitedArguemts);

			if (tokens.size() < 2)
				throw AssemblerExceptionMissingArgument();
			if(tokens.size() > 2)
				throw AssemblerExceptionTooManyArguments();

			auto srcReg = AssemblerTypes::getRegister(tokens[0]);
			if (srcReg.has_value())
			{
				if (op == AssemblerTypes::Operation::LEA)
					throw AssemblerExceptionInvalidArgument();

				opt.setSourceDirectRegister();
				opr1.setAbsolute().setSourceRegisterAny(srcReg.value());
				isFirstOperandReg = true;
			}
			else
			{
				if (std::regex_match(tokens[0], std::regex(AssemblerTypes::REGEX_DATA_ARG_VALIDATE)))
				{
					if (op == AssemblerTypes::Operation::LEA)
						throw AssemblerExceptionInvalidArgument();

					opt.setSourceImmediate();
					try
					{
						opr1.setAbsolute().setNumber(std::stoi(tokens[0]));
					} 
					catch (const std::invalid_argument&)
					{
						throw AssemblerExceptionInvalidArgument();
					}
				}
				else
				{
					if (std::regex_match(tokens[0], std::regex(AssemblerTypes::REGEX_SYMBOL_VALIDATE)))
					{
						opt.setSourceDirect();
						opr1.setSymbol(tokens[0]);
					}
					else
					{
						throw AssemblerExceptionInvalidArgument();
					}
				}
			}

			auto destReg = AssemblerTypes::getRegister(tokens[1]);
			if (destReg.has_value())
			{
				opt.setDestinationDirectRegister();
				if (isFirstOperandReg)
					opr1.setDestRegisterAny(destReg.value());
				else
					opr2.setDestRegisterAny(destReg.value());
				isSecondOperandReg = true;
			}
			else
			{
				if (std::regex_match(tokens[1], std::regex(AssemblerTypes::REGEX_DATA_ARG_VALIDATE)))
				{
					if (op != AssemblerTypes::Operation::CMP) 
						throw AssemblerExceptionInvalidArgument();

					opt.setDestinationImmediate();
					try
					{
						opr2.setAbsolute().setNumber(std::stoi(tokens[1]));
					}
					catch (const std::invalid_argument&)
					{
						throw AssemblerExceptionInvalidArgument();
					}
				}
				else
				{
					if (std::regex_match(tokens[1], std::regex(AssemblerTypes::REGEX_SYMBOL_VALIDATE)))
					{
						opt.setDestinationDirect();
						opr2.setSymbol(tokens[1]);
					}
					else
					{
						throw AssemblerExceptionInvalidArgument();
					}
				}
			}
			
			res.addWords({ opt, opr1 });
			if (!isFirstOperandReg || !isSecondOperandReg)
				res.addWord(std::move(opr2));
			
			return res;
		}
	};
}
