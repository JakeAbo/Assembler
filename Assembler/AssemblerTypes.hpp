#pragma once

#include <map>
#include <ostream>
#include <sstream>
#include <optional>

namespace Assembler
{
	class AssemblerTypes
	{
		friend class Word;
		friend class Statment;
		friend class CommandParsers;
		friend class StringUtility;

	private:
		/* Regexs */
		static constexpr auto REGEX_SYMBOL_VALIDATE_COLON	= "^[a-zA-Z][a-zA-Z0-9]{0,30}[:]$";
		static constexpr auto REGEX_SYMBOL_VALIDATE			= "^[a-zA-Z][a-zA-Z0-9]{0,30}$";
		static constexpr auto REGEX_DATA_ARG_VALIDATE		= "^[-+]?[0-9]+(,[-+]?[0-9]+)*$";
		static constexpr auto REGEX_STRING_ARG_VALIDATE		= "^\"[a-zA-Z0-9]+\"$";

		/* Assembly Code Properties */
		static constexpr auto LINE_MAX_LENGTH = 80;
		static constexpr auto LEX_COLON = ':';
		static constexpr auto LEX_COMMA = ',';
		static constexpr auto LEX_QUOTATION = '"';
		static constexpr auto LEX_COMMENT_SIGN = ';';

		/* Word Properties */
		static constexpr auto WORD_SIZE = 12;
		static constexpr auto NUMBER_SIZE = 10;
		static constexpr auto CHAR_SIZE = 12;
		static constexpr auto SYMBOL_SIZE = 10;
		static constexpr auto CODE_SIZE = 2;
		static constexpr auto OP_CODE_SIZE = 4;
		static constexpr auto OPERNAD_LBA_SIZE = 3;
		static constexpr auto REGISTER_SIZE = 5;
		static constexpr auto BASE64_CHAR_SIZE = 6;

		/* First Word */
		static constexpr auto CODE_TYPE_0 = 0;
		static constexpr auto CODE_TYPE_1 = 1;

		static constexpr auto DEST_TYPE_0 = 2;
		static constexpr auto DEST_TYPE_1 = 3;
		static constexpr auto DEST_TYPE_2 = 4;

		static constexpr auto OP_0 = 5;
		static constexpr auto OP_1 = 6;
		static constexpr auto OP_2 = 7;
		static constexpr auto OP_3 = 8;

		static constexpr auto SRC_TYPE_0 = 9;
		static constexpr auto SRC_TYPE_1 = 10;
		static constexpr auto SRC_TYPE_2 = 11;

		/* Second or Third Word */
		/* Data char and number */
		static constexpr auto DATA_NUMBER_CHAR_0 = 0;

		/*Code char and number */
		static constexpr auto CODE_NUMBER_CHAR_0 = 2;

		/* Number */
		static constexpr auto NUMBER_MIN_VALUE = -4095;
		static constexpr auto NUMBER_MAX_VALUE = 4095;

		/* Register */
		static constexpr auto DEST_REGISTER_0 = 2;
		static constexpr auto SRC_REGISTER_0 = 7;

		enum class Register
		{
			R0 = 0,
			R1,
			R2,
			R3,
			R4,
			R5,
			R6,
			R7 = 7
		};

		enum class Code
		{
			Absolute = 0,
			External = 1,
			Relocateable = 2
		};

		enum class LogicalBlockAddress
		{
			IMMEDIATE = 1,
			DIRECT = 3,
			REGISTER_DIRECT = 5
		};

		enum class Operation
		{
			MOV = 0,
			CMP,
			ADD,
			SUB,
			NOT,
			CLR,
			LEA,
			INC,
			DEC,
			JMP,
			BNE,
			RED,
			PRN,
			JSR,
			RTS,
			STOP = 15
		};

		enum class DataInstructionType
		{
			DATA = 0,
			STRING,
			ENTRY,
			EXTERN = 3
		};

		static std::optional<Register> getRegister(const std::string& reg)
		{
			static const std::map<std::string, Register> registers = {
				{"@r0", Register::R0},
				{"@r1", Register::R1},
				{"@r2", Register::R2},
				{"@r3", Register::R3},
				{"@r4", Register::R4},
				{"@r5", Register::R5},
				{"@r6", Register::R6},
				{"@r7", Register::R7},
			};

			if (registers.find(reg) != registers.end())
			{
				return registers.at(reg);
			}
				
			return {};
		}

		static std::optional<Register> checkIfSavedReg(const std::string& reg)
		{
			std::ostringstream regWithShtrudel;

			if (reg[0] != '@')
			{
				regWithShtrudel << '@';
			}

			regWithShtrudel << reg;

			return getRegister(regWithShtrudel.str());
		}

		static std::optional<Operation> getOpCode(const std::string& op)
		{
			static const std::map<std::string, Operation> operations = {
				{"mov", Operation::MOV},
				{"cmp", Operation::CMP},
				{"add", Operation::ADD},
				{"sub", Operation::SUB},
				{"not", Operation::NOT},
				{"clr", Operation::CLR},
				{"lea", Operation::LEA},
				{"inc", Operation::INC},
				{"dec", Operation::DEC},
				{"jmp", Operation::JMP},
				{"bne", Operation::BNE},
				{"red", Operation::RED},
				{"prn", Operation::PRN},
				{"jsr", Operation::JSR},
				{"rts", Operation::RTS},
				{"stop", Operation::STOP}
			};

			if (operations.find(op) != operations.end())
				return operations.at(op);

			return {};
		}

		static std::optional<DataInstructionType> getDataType(const std::string& dataInstruction)
		{
			static const std::map<std::string, DataInstructionType> dataTypes = {
				{".data", DataInstructionType::DATA},
				{".string", DataInstructionType::STRING},
				{".entry", DataInstructionType::ENTRY},
				{".extern", DataInstructionType::EXTERN}
			};

			if (dataTypes.find(dataInstruction) != dataTypes.end())
				return dataTypes.at(dataInstruction);

			return {};
		}
	};
}