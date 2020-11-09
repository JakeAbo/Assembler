#include "pch.h"
#include "AsmFileReader.hpp"

namespace Tester
{
	namespace AsmFile
	{
		
		TEST(CantOpenFile, AsmFileModule)
		{
			try
			{
				Assembler::AsmFileReader file("\\dir\\doesntexist");
				file.openFile();
			}
			catch (const Assembler::AssemblerException& ex)
			{
				EXPECT_EQ(ex.what(), std::string("Assembler unable to open .asm file"));
			}
		}
	}
}