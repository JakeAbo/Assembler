#pragma once

#include <bitset>
#include <ostream>

#include "AssemblerTypes.hpp"
#include "AssemblerExceptions.hpp"
#include "AssemblerStreams.hpp"

namespace Assembler
{
	class Word
	{
	private:
		std::bitset<AssemblerTypes::WORD_SIZE> _bits; /* initalize all bits to 0 */

	public:
		Word() 
			: _bits()
		{}

		Word& clear()
		{
			_bits.reset();
			return *this;
		}

		const std::string getBinaryString() const 
		{
			return _bits.to_string();
		}

		const std::string getWordBase64() const
		{
			static std::bitset<AssemblerTypes::WORD_SIZE> divider(0b000000111111);
			static constexpr auto base64Map = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

			std::string res;
			std::bitset<AssemblerTypes::WORD_SIZE> copyBits(_bits);

			res.push_back(base64Map[((copyBits >> AssemblerTypes::BASE64_CHAR_SIZE)& divider).to_ulong()]);
			res.push_back(base64Map[(copyBits & divider).to_ulong()]);

			return res;
		}

		friend BinaryStream& operator<<(BinaryStream& os, const Word& word)
		{
			os << word.getBinaryString();
			return os;
		}

		friend Base64Stream& operator<<(Base64Stream& os, const Word& word)
		{
			os << word.getWordBase64();
			return os;
		}

		/* Code Type */
		Word& setAbsolute()
		{
			setCodeType(AssemblerTypes::Code::Absolute);
			return *this;
		}

		Word& setExternal()
		{
			setCodeType(AssemblerTypes::Code::External);
			return *this;
		}

		Word& setRelocatable()
		{
			setCodeType(AssemblerTypes::Code::Relocateable);
			return *this;
		}

		/* Destination LBA */
		Word& setDestinationImmediate()
		{
			setDestinationLBA(AssemblerTypes::LogicalBlockAddress::IMMEDIATE);
			return *this;
		}

		Word& setDestinationDirect()
		{
			setDestinationLBA(AssemblerTypes::LogicalBlockAddress::DIRECT);
			return *this;
		}

		Word& setDestinationDirectRegister()
		{
			setDestinationLBA(AssemblerTypes::LogicalBlockAddress::REGISTER_DIRECT);
			return *this;
		}

		/* Source LBA */
		Word& setSourceImmediate()
		{
			setSourceLBA(AssemblerTypes::LogicalBlockAddress::IMMEDIATE);
			return *this;
		}

		Word& setSourceDirect()
		{
			setSourceLBA(AssemblerTypes::LogicalBlockAddress::DIRECT);
			return *this;
		}

		Word& setSourceDirectRegister()
		{
			setSourceLBA(AssemblerTypes::LogicalBlockAddress::REGISTER_DIRECT);
			return *this;
		}

		/* Op Codes */
		Word& setOpCodeMov()
		{
			setOpCode(AssemblerTypes::Operation::MOV);
			return *this;
		}

		Word& setOpCodeCmp()
		{
			setOpCode(AssemblerTypes::Operation::CMP);
			return *this;
		}

		Word& setOpCodeAdd()
		{
			setOpCode(AssemblerTypes::Operation::ADD);
			return *this;
		}

		Word& setOpCodeSub()
		{
			setOpCode(AssemblerTypes::Operation::SUB);
			return *this;
		}

		Word& setOpCodeNot()
		{
			setOpCode(AssemblerTypes::Operation::NOT);
			return *this;
		}

		Word& setOpCodeClr()
		{
			setOpCode(AssemblerTypes::Operation::CLR);
			return *this;
		}

		Word& setOpCodeLea()
		{
			setOpCode(AssemblerTypes::Operation::LEA);
			return *this;
		}

		Word& setOpCodeInc()
		{
			setOpCode(AssemblerTypes::Operation::INC);
			return *this;
		}

		Word& setOpCodeDec()
		{
			setOpCode(AssemblerTypes::Operation::DEC);
			return *this;
		}

		Word& setOpCodeJmp()
		{
			setOpCode(AssemblerTypes::Operation::JMP);
			return *this;
		}

		Word& setOpCodeBne()
		{
			setOpCode(AssemblerTypes::Operation::BNE);
			return *this;
		}

		Word& setOpCodeRed()
		{
			setOpCode(AssemblerTypes::Operation::RED);
			return *this;
		}

		Word& setOpCodePrn()
		{
			setOpCode(AssemblerTypes::Operation::PRN);
			return *this;
		}

		Word& setOpCodeJsr()
		{
			setOpCode(AssemblerTypes::Operation::JSR);
			return *this;
		}

		Word& setOpCodeRts()
		{
			setOpCode(AssemblerTypes::Operation::RTS);
			return *this;
		}

		Word& setOpCodeStop()
		{
			setOpCode(AssemblerTypes::Operation::STOP);
			return *this;
		}

		/* Set Number in 10 last bits */
		Word& setNumber(int num)
		{
			if (num < AssemblerTypes::NUMBER_MIN_VALUE || num > AssemblerTypes::NUMBER_MAX_VALUE)
				throw AssemblerExceptionOverflow();

			size_t i;
			std::bitset<AssemblerTypes::NUMBER_SIZE> opBits(static_cast<int>(num));

			for (i = 0; i < AssemblerTypes::NUMBER_SIZE; ++i)
			{
				_bits.set(i + AssemblerTypes::NUMBER_0, opBits[i]);
			}

			return *this;
		}

		/* Set Register */
		Word& setDestReg0()
		{
			setDestinationRegister(AssemblerTypes::Register::R0);
			return *this;
		}

		Word& setDestReg1()
		{
			setDestinationRegister(AssemblerTypes::Register::R1);
			return *this;
		}

		Word& setDestReg2()
		{
			setDestinationRegister(AssemblerTypes::Register::R2);
			return *this;
		}

		Word& setDestReg3()
		{
			setDestinationRegister(AssemblerTypes::Register::R3);
			return *this;
		}

		Word& setDestReg4()
		{
			setDestinationRegister(AssemblerTypes::Register::R4);
			return *this;
		}

		Word& setDestReg5()
		{
			setDestinationRegister(AssemblerTypes::Register::R5);
			return *this;
		}

		Word& setDestReg6()
		{
			setDestinationRegister(AssemblerTypes::Register::R6);
			return *this;
		}

		Word& setDestReg7()
		{
			setDestinationRegister(AssemblerTypes::Register::R7);
			return *this;
		}

		Word& setSourceReg0()
		{
			setSourceRegister(AssemblerTypes::Register::R0);
			return *this;
		}

		Word& setSourceReg1()
		{
			setSourceRegister(AssemblerTypes::Register::R1);
			return *this;
		}

		Word& setSourceReg2()
		{
			setSourceRegister(AssemblerTypes::Register::R2);
			return *this;
		}

		Word& setSourceReg3()
		{
			setSourceRegister(AssemblerTypes::Register::R3);
			return *this;
		}

		Word& setSourceReg4()
		{
			setSourceRegister(AssemblerTypes::Register::R4);
			return *this;
		}

		Word& setSourceReg5()
		{
			setSourceRegister(AssemblerTypes::Register::R5);
			return *this;
		}

		Word& setSourceReg6()
		{
			setSourceRegister(AssemblerTypes::Register::R6);
			return *this;
		}

		Word& setSourceReg7()
		{
			setSourceRegister(AssemblerTypes::Register::R7);
			return *this;
		}
		
	private:
		void setCodeType(AssemblerTypes::Code code)
		{
			int i;
			std::bitset<AssemblerTypes::CODE_SIZE> codeBits(static_cast<unsigned int>(code));

			for (i = 0; i < AssemblerTypes::CODE_SIZE; ++i)
			{
				_bits.set(i + static_cast<int>(AssemblerTypes::CODE_TYPE_0), codeBits[i]);
			}
		}

		void setOpCode(AssemblerTypes::Operation op)
		{
			int i;
			int check = 1;
			std::bitset<AssemblerTypes::OP_CODE_SIZE> opBits(static_cast<unsigned int>(op));

			for (i = 0; i < AssemblerTypes::OP_CODE_SIZE; ++i)
			{
				_bits.set(i + static_cast<size_t>(AssemblerTypes::OP_0), opBits[i]);
			}
		}

		void setDestinationLBA(AssemblerTypes::LogicalBlockAddress lba)
		{
			int i;
			std::bitset<AssemblerTypes::OPERNAD_LBA_SIZE> lbaBits(static_cast<unsigned int>(lba));

			for (i = 0; i < AssemblerTypes::OPERNAD_LBA_SIZE; ++i)
			{
				int temp = 1;
				_bits.set(i + static_cast<size_t>(AssemblerTypes::DEST_TYPE_0), lbaBits[i]);
			}
		}

		void setSourceLBA(AssemblerTypes::LogicalBlockAddress lba)
		{
			int i;
			std::bitset<AssemblerTypes::OPERNAD_LBA_SIZE> lbaBits(static_cast<unsigned int>(lba));

			for (i = 0; i < AssemblerTypes::OPERNAD_LBA_SIZE; ++i)
			{
				_bits.set(i + static_cast<size_t>(AssemblerTypes::SRC_TYPE_0), lbaBits[i]);
			}
		}

		void setDestinationRegister(AssemblerTypes::Register reg)
		{
			int i;
			std::bitset<AssemblerTypes::REGISTER_SIZE> regBits(static_cast<unsigned int>(reg));

			for (i = 0; i < AssemblerTypes::REGISTER_SIZE; ++i)
			{
				_bits.set(i + static_cast<size_t>(AssemblerTypes::DEST_REGISTER_0), regBits[i]);
			}
		}

		void setSourceRegister(AssemblerTypes::Register reg)
		{
			int i;
			std::bitset<AssemblerTypes::REGISTER_SIZE> regBits(static_cast<unsigned int>(reg));

			for (i = 0; i < AssemblerTypes::REGISTER_SIZE; ++i)
			{
				_bits.set(i + static_cast<size_t>(AssemblerTypes::SRC_REGISTER_0), regBits[i]);
			}
		}
	};
}