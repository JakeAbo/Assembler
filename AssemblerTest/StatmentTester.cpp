#include "pch.h"
#include "Statment.hpp"

namespace Tester
{
	namespace Statment
	{
		TEST(StatmentLenOver80, StatmentTesterLen)
		{
			Assembler::Statment stmt("aasdasdfasfsdfsdfsdfsdfsfdsfdsfaaaaaasdasdfasfsdfsdfsdfsdfsfdsfdsfaaaaaaavsdfgssa");
			stmt.parse();

			EXPECT_EQ(stmt.getException().value(), std::string("Assembler line until 80 characters"));
		}

		TEST(SymbolTestGood, StatmentTester)
		{
			Assembler::Statment stmt(" \t \t  SYMBOL  \t : \t\t mov -103 \t, \t @r2 \t \t");
			stmt.parse();

			EXPECT_EQ(stmt.getSymbol().value(), "SYMBOL");
		}

		TEST(SymbolTestMissColon, StatmentTesterSyntax)
		{
			Assembler::Statment stmt(" \t \t  SYMBOL  \t  \t\t mov -103 \t, \t @r2 \t \t");
			stmt.parse();

			EXPECT_EQ(stmt.getException().value(), std::string("Assembler symbol must start with alpha letter and contain only alphanumeric characters with max length of 31. Also can't be any of registers or operator names."));
		}

		TEST(SymbolTestStartWithNum, StatmentTesterSyntax)
		{
			Assembler::Statment stmt(" \t \t  7YMBOL  \t : \t\t mov -103 \t, \t @r2 \t \t");
			stmt.parse();

			EXPECT_EQ(stmt.getException().value(), std::string("Assembler symbol must start with alpha letter and contain only alphanumeric characters with max length of 31. Also can't be any of registers or operator names."));
		}

		TEST(SymbolTestOver31, StatmentTesterSyntax)
		{
			Assembler::Statment stmt(" \t \t  SYMBOLSYMBOLSYMBOLSYMBOLSYMBOLLL  \t : \t\t mov -103 \t, \t @r2 \t \t");
			stmt.parse();

			EXPECT_EQ(stmt.getException().value(), std::string("Assembler symbol must start with alpha letter and contain only alphanumeric characters with max length of 31. Also can't be any of registers or operator names."));
		}

		TEST(SymbolTestGoodShort, StatmentTesterSyntax)
		{
			Assembler::Statment stmt(" \t \t  x  \t : \t\t mov -103 \t, \t @r2 \t \t");
			stmt.parse();

			EXPECT_EQ(stmt.getSymbol().value(), std::string("x"));
		}

		TEST(SymbolTestGoodLong, StatmentTesterSyntax)
		{
			Assembler::Statment stmt(" \t \t  SYMBOLSYMBOLSYMBOLSYMBOLSYMBOLx  \t : \t\t mov -103 \t, \t @r2 \t \t");
			stmt.parse();

			EXPECT_EQ(stmt.getSymbol().value(), std::string("SYMBOLSYMBOLSYMBOLSYMBOLSYMBOLx"));
		}

		TEST(SymbolTestDuplicateSymbol, StatmentTesterSyntax)
		{
			Assembler::Statment stmt(" \t \t  SYMBOLSYMBOLS Y: MBOLSYMBOLSYMBOLx  \t : \t\t mov -103 \t, \t @r2 \t \t");
			stmt.parse();

			EXPECT_EQ(stmt.getException().value(), std::string("Assembler symbol must start with alpha letter and contain only alphanumeric characters with max length of 31. Also can't be any of registers or operator names."));
		}
		
		TEST(SymbolTestSavedName1, StatmentTesterSavedNames)
		{
			Assembler::Statment stmt(" \t \t  r0  \t : \t\t mov -103 \t, \t @r2 \t \t");
			stmt.parse();

			EXPECT_EQ(stmt.getSymbol().has_value(), false);
		}

		TEST(SymbolTestSavedName2, StatmentTesterSavedNames)
		{
			Assembler::Statment stmt(" \t \t  @r0  \t : \t\t mov -103 \t, \t @r2 \t \t");
			stmt.parse();

			EXPECT_EQ(stmt.getSymbol().has_value(), false);
		}

		TEST(SymbolTestSavedName3, StatmentTesterSavedNames)
		{
			Assembler::Statment stmt(" \t \t  mov  \t : \t\t mov -103 \t, \t @r2 \t \t");
			stmt.parse();

			EXPECT_EQ(stmt.getSymbol().has_value(), false);
		}

		TEST(SymbolTestSavedName4, StatmentTesterSavedNames)
		{
			Assembler::Statment stmt(" \t \t  dec  \t : \t\t mov -103 \t, \t @r2 \t \t");
			stmt.parse();

			EXPECT_EQ(stmt.getSymbol().has_value(), false);
		}

		TEST(SymbolTestSavedName5, StatmentTesterSavedNames)
		{
			Assembler::Statment stmt(" \t \t  sy  \t : \t\t mov -103 \t, \t @r2 \t \t");
			stmt.parse();

			EXPECT_EQ(stmt.getSymbol().has_value(), false);
		}
	}
}