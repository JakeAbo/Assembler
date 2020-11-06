#pragma once

namespace Assembler
{
	class AssemblerTypes
	{
		friend class Word;

	private:
		/* Word Properties */
		static constexpr auto WORD_SIZE = 12;
		static constexpr auto NUMBER_SIZE = 10;
		static constexpr auto CODE_SIZE = 2;
		static constexpr auto OP_CODE_SIZE = 4;
		static constexpr auto OPERNAD_LBA_SIZE = 3;
		static constexpr auto REGISTER_SIZE = 5;

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
		/* Number */
		static constexpr auto NUMBER_0 = 2;
		static constexpr auto NUMBER_MIN_VALUE = -1023;
		static constexpr auto NUMBER_MAX_VALUE = 1023;

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
	};
}