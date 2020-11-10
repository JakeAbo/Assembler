#include "pch.h"
#include "Word.hpp"

namespace Tester
{
	namespace Word
	{
		Assembler::Word w;
		
		/* Basic Word Tests */
		TEST(CodeTypeAbsolute, TypeAbsolute)
		{
			w.clear().setAbsolute();

			EXPECT_EQ(w.getBinaryString(), "000000000000");
		}

		TEST(CodeTypeExternal, TypeExternal)
		{
			w.clear().setExternal();
			
			EXPECT_EQ(w.getBinaryString(), "000000000001");
		}

		TEST(CodeTypeRelocateable, TypeRelocateable)
		{
			w.clear().setRelocatable();
			
			EXPECT_EQ(w.getBinaryString(), "000000000010");
		}

		TEST(DestinationLbaImmediate, DestinationImmediate)
		{
			w.clear().setDestinationImmediate();
			
			EXPECT_EQ(w.getBinaryString(), "000000000100");
		}

		TEST(DestinationLbaDirect, DestinationDirect)
		{
			w.clear().setDestinationDirect();
			
			EXPECT_EQ(w.getBinaryString(), "000000001100");
		}

		TEST(DestinationLbaDirectRegister, DestinationDirectRegister)
		{
			w.clear().setDestinationDirectRegister();

			EXPECT_EQ(w.getBinaryString(), "000000010100");
		}

		TEST(SourceLbaImmediate, SourceImmediate)
		{
			w.clear().setSourceImmediate();

			EXPECT_EQ(w.getBinaryString(), "001000000000");
		}

		TEST(SourceLbaDirect, SourceDirect)
		{
			w.clear().setSourceDirect();

			EXPECT_EQ(w.getBinaryString(), "011000000000");
		}

		TEST(SourceLbaDirectRegister, SourceDirectRegister)
		{
			w.clear().setSourceDirectRegister();

			EXPECT_EQ(w.getBinaryString(), "101000000000");
		}

		TEST(OpCodeMov, WordMov)
		{
			w.clear().setOpCodeMov();
	
			EXPECT_EQ(w.getBinaryString(), "000000000000");
		}

		TEST(OpCodeCmp, WordCmp)
		{
			w.clear().setOpCodeCmp();
			
			EXPECT_EQ(w.getBinaryString(), "000000100000");
		}

		TEST(OpCodeAdd, WordAdd)
		{
			w.clear().setOpCodeAdd();
			
			EXPECT_EQ(w.getBinaryString(), "000001000000");
		}

		TEST(OpCodeSub, WordSub)
		{
			w.clear().setOpCodeSub();

			EXPECT_EQ(w.getBinaryString(), "000001100000");
		}

		TEST(OpCodeNot, WordNot)
		{
			w.clear().setOpCodeNot();

			EXPECT_EQ(w.getBinaryString(), "000010000000");
		}

		TEST(OpCodeClr, WordClr)
		{
			w.clear().setOpCodeClr();

			EXPECT_EQ(w.getBinaryString(), "000010100000");
		}

		TEST(OpCodeLea, WordLea)
		{
			w.clear().setOpCodeLea();

			EXPECT_EQ(w.getBinaryString(), "000011000000");
		}

		TEST(OpCodeInc, WordInc)
		{
			w.clear().setOpCodeInc();

			EXPECT_EQ(w.getBinaryString(), "000011100000");
		}

		TEST(OpCodeDec, WordDec)
		{
			w.clear().setOpCodeDec();

			EXPECT_EQ(w.getBinaryString(), "000100000000");
		}

		TEST(OpCodeJmp, WordJmp)
		{
			w.clear().setOpCodeJmp();

			EXPECT_EQ(w.getBinaryString(), "000100100000");
		}

		TEST(OpCodeBne, WordBne)
		{
			w.clear().setOpCodeBne();

			EXPECT_EQ(w.getBinaryString(), "000101000000");
		}

		TEST(OpCodeRed, WordRed)
		{
			w.clear().setOpCodeRed();

			EXPECT_EQ(w.getBinaryString(), "000101100000");
		}

		TEST(OpCodePrn, WordPrn)
		{
			w.clear().setOpCodePrn();

			EXPECT_EQ(w.getBinaryString(), "000110000000");
		}

		TEST(OpCodeJsr, WordJsr)
		{
			w.clear().setOpCodeJsr();

			EXPECT_EQ(w.getBinaryString(), "000110100000");
		}

		TEST(OpCodeRts, WordRts)
		{
			w.clear().setOpCodeRts();

			EXPECT_EQ(w.getBinaryString(), "000111000000");
		}

		TEST(OpCodeStop, WordStop)
		{
			w.clear().setOpCodeStop();

			EXPECT_EQ(w.getBinaryString(), "000111100000");
		}

		/* Positive & Negative Number Test */

		TEST(Positive, WordNumber)
		{
			w.clear().setAbsolute().setNumber(312);

			EXPECT_EQ(w.getBinaryString(), "000100111000");
		}

		TEST(Negative, WordNumber)
		{
			w.clear().setAbsolute().setNumber(-312);

			EXPECT_EQ(w.getBinaryString(), "111011001000");
		}

		TEST(MaxPositive, WordNumber)
		{
			w.clear().setAbsolute().setNumber(4095);

			EXPECT_EQ(w.getBinaryString(), "111111111111");
		}

		TEST(MinNegative, WordNumber)
		{
			w.clear().setAbsolute().setNumber(-4095);

			EXPECT_EQ(w.getBinaryString(), "000000000001");
		}

		TEST(OverflowNegative, WordNumber)
		{
			try
			{
				w.clear().setAbsolute().setNumber(-1029);
			}
			catch (const Assembler::AssemblerException & ex)
			{
				EXPECT_EQ(ex.what(), std::string("Assembler is 10 bit system - means 10 bit numaric values"));
			}
		}

		TEST(OverflowPositive, WordNumber)
		{
			try
			{
				w.clear().setAbsolute().setNumber(1029);
			}
			catch (const Assembler::AssemblerException & ex)
			{
				EXPECT_EQ(ex.what(), std::string("Assembler is 10 bit system - means 10 bit numaric values"));
			}
		}
		
		/* Register Test */
		TEST(DstReg0, RegisterTest)
		{
			w.clear().setAbsolute().setDestReg0();
			EXPECT_EQ(w.getBinaryString(), "000000000000");
		}

		TEST(DstReg1, RegisterTest)
		{
			w.clear().setAbsolute().setDestReg1();
			EXPECT_EQ(w.getBinaryString(), "000000000100");
		}

		TEST(DstReg2, RegisterTest)
		{
			w.clear().setAbsolute().setDestReg2();
			EXPECT_EQ(w.getBinaryString(), "000000001000");
		}

		TEST(DstReg3, RegisterTest)
		{
			w.clear().setAbsolute().setDestReg3();
			EXPECT_EQ(w.getBinaryString(), "000000001100");
		}

		TEST(DstReg4, RegisterTest)
		{
			w.clear().setAbsolute().setDestReg4();
			EXPECT_EQ(w.getBinaryString(), "000000010000");
		}

		TEST(DstReg5, RegisterTest)
		{
			w.clear().setAbsolute().setDestReg5();
			EXPECT_EQ(w.getBinaryString(), "000000010100");
		}

		TEST(DstReg6, RegisterTest)
		{
			w.clear().setAbsolute().setDestReg6();
			EXPECT_EQ(w.getBinaryString(), "000000011000");
		}

		TEST(DstReg7, RegisterTest)
		{
			w.clear().setAbsolute().setDestReg7();
			EXPECT_EQ(w.getBinaryString(), "000000011100");
		}

		TEST(SourceReg0, RegisterTest)
		{
			w.clear().setAbsolute().setSourceReg0();
			EXPECT_EQ(w.getBinaryString(), "000000000000");
		}

		TEST(SourceReg1, RegisterTest)
		{
			w.clear().setAbsolute().setSourceReg1();
			EXPECT_EQ(w.getBinaryString(), "000010000000");
		}

		TEST(SourceReg2, RegisterTest)
		{
			w.clear().setAbsolute().setSourceReg2();
			EXPECT_EQ(w.getBinaryString(), "000100000000");
		}

		TEST(SourceReg3, RegisterTest)
		{
			w.clear().setAbsolute().setSourceReg3();
			EXPECT_EQ(w.getBinaryString(), "000110000000");
		}

		TEST(SourceReg4, RegisterTest)
		{
			w.clear().setAbsolute().setSourceReg4();
			EXPECT_EQ(w.getBinaryString(), "001000000000");
		}

		TEST(SourceReg5, RegisterTest)
		{
			w.clear().setAbsolute().setSourceReg5();
			EXPECT_EQ(w.getBinaryString(), "001010000000");
		}

		TEST(SourceReg6, RegisterTest)
		{
			w.clear().setAbsolute().setSourceReg6();
			EXPECT_EQ(w.getBinaryString(), "001100000000");
		}

		TEST(SourceReg7, RegisterTest)
		{
			w.clear().setAbsolute().setSourceReg7();
			EXPECT_EQ(w.getBinaryString(), "001110000000");
		}

		/* Full Command Tests */
		TEST(AbsImmediateMovDirect, FullCommand)
		{
			w.clear().setAbsolute().setDestinationImmediate().setOpCodeMov().setSourceDirect();

			EXPECT_EQ(w.getBinaryString(), "011000000100");
		}

		TEST(RelocateableRegisterAddRegister, FullCommand)
		{
			w.clear().setRelocatable().setDestinationDirectRegister().setOpCodeAdd().setSourceDirectRegister();

			EXPECT_EQ(w.getBinaryString(), "101001010110");
		}

		/* BASE64 Encoder Tests */
		TEST(Base64EncoderCommand1, Base64Encoder)
		{
			w.clear().setRelocatable().setDestinationDirectRegister().setOpCodeAdd().setSourceDirectRegister();

			EXPECT_EQ(w.getWordBase64(), "pW");
		}

		TEST(Base64EncoderCommand2, Base64Encoder)
		{
			w.clear().setAbsolute().setDestinationImmediate().setOpCodeMov().setSourceDirect();

			EXPECT_EQ(w.getWordBase64(), "YE");
		}
	}
}