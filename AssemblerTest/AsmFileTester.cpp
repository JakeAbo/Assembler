#include "pch.h"
#include "AsmFileReader.hpp"

namespace Tester
{
	namespace AsmFile
	{
		TEST(CantOpenFile, AsmFileModule)
		{
			Assembler::SymbolPool::Instance().clear();
			Assembler::AsmFileReader file("\\dir\\doesntexist");
			file.openFile();

			EXPECT_EQ(file.getException().value(), std::string("Assembler unable to open .asm file"));
		}

		TEST(CantCompileUnopenFile, AsmFileModule)
		{
			Assembler::SymbolPool::Instance().clear();
			Assembler::AsmFileReader file("\\dir\\doesntexist");
			file.compileFile();

			EXPECT_EQ(file.getException().value(), std::string("Assembler unable to open .asm file"));
		}

		TEST(CompileAsmFile, AsmFileModule)
		{
			Assembler::SymbolPool::Instance().clear();
			Assembler::AsmFileReader file(".\\example2.asm");
			file.openFile();
			file.compileFile();

			Assembler::BinaryStream os;
			os << file;
			EXPECT_EQ(os.str(), "101000001100\n000110000000\n000111110110\n000111000110\n000110000100\n111111101100\n000101001100\n000000000001\n101001110100\n000010010000\n000101001100\n000000000001\n000011101100\n001000000010\n000100101100\n000000000001\n000111100000\n000001100001\n000001100010\n000001100011\n000001100100\n000001100101\n000001100110\n000000000000\n000000000110\n111111110111\n000000001111\n000000010110");
		}
	}
}