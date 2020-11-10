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

		TEST(SymbolTestWithoutSymbol, StatmentTesterSavedNames)
		{
			Assembler::Statment stmt(" \t \t    \t  \t\t .data -103 \t, \t 15 \t , 2\t");
			stmt.parse();

			EXPECT_EQ(stmt.getException().has_value(), false);
		}

		TEST(SymbolTestUnknownCommand, StatmentTesterComamands)
		{
			Assembler::Statment stmt(" \t \t    \t SYMBOL: \tdt\t  \t \t  \t \t");
			stmt.parse();

			EXPECT_EQ(stmt.getException().value(), std::string("Assembler unknwon instruction"));
		}

		TEST(SymbolTestUnknownSymbol, StatmentTesterComamands)
		{
			Assembler::Statment stmt(" \t \t    \t : \tdt\t  \t \t  \t \t");
			stmt.parse();

			EXPECT_EQ(stmt.getException().value(), std::string("Assembler symbol must start with alpha letter and contain only alphanumeric characters with max length of 31. Also can't be any of registers or operator names."));
		}

		TEST(SymbolTestUnknownCommand3, StatmentTesterComamands)
		{
			Assembler::Statment stmt(" \t \t    \t  \tdt\t  \t \t  \t \t");
			stmt.parse();

			EXPECT_EQ(stmt.getException().value(), std::string("Assembler unknwon instruction"));
		}

		TEST(StatmentSymbolData, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.data\t  \t6  \t , \t -9    , \t 15 ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getCommand().value().getBinaryCommand(), std::string("000000000110\n111111110111\n000000001111\n"));
		}
	}
}