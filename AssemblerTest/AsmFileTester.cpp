#include "pch.h"
#include "AsmFileReader.hpp"

namespace Tester
{
	namespace AsmFile
	{
		TEST(CantOpenFile, AsmFileModule)
		{
			Assembler::AsmFileReader file("\\dir\\doesntexist");
			file.openFile();

			EXPECT_EQ(file.getException().value(), std::string("Assembler unable to open .asm file"));
		}

		TEST(CantCompileUnopenFile, AsmFileModule)
		{
			Assembler::AsmFileReader file("\\dir\\doesntexist");
			file.compileFile();

			EXPECT_EQ(file.getException().value(), std::string("Assembler unable to open .asm file"));
		}
	}
}