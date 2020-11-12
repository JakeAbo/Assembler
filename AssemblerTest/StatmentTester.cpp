#include "pch.h"
#include "Statment.hpp"
#include "Symbol.hpp"

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

		TEST(StatmentSymbolData2, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t. data\t  \t6  \t , \t -9    , \t 15 ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getException().value(), std::string("Assembler unknwon instruction"));
		}

		TEST(StatmentSymbolData3, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.data\t  \t  \t  \t      \t 15 ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getCommand().value().getBinaryCommand(), std::string("000000001111\n"));
		}

		TEST(StatmentSymbolData4, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.data\t  \t  \t  \t      \t  ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getException().value(), std::string("Assembler invalid argument"));
		}

		TEST(StatmentSymbolData5, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.data\t  \t6  \t , \t -9    , \t 15      ; comment ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getCommand().value().getBinaryCommand(), std::string("000000000110\n111111110111\n000000001111\n"));
		}

		TEST(StatmentSymbolData6, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.data\t  \t6  \t , \t -9    ; comment, \t 15 ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getCommand().value().getBinaryCommand(), std::string("000000000110\n111111110111\n"));
		}

		TEST(StatmentSymbolData7, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.data\t  \t6  \t ,, \t -9    ,; comment \t 15 ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getException().value(), std::string("Assembler invalid argument"));
		}

		TEST(StatmentSymbolData8, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.data\t  \t6  \t , \t -9    ,; comment \t 15 ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getException().value(), std::string("Assembler invalid argument"));
		}

		TEST(StatmentSymbolData9, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.data\t  \t-6  \t , \t -9 , +15   ; comment \t 15 ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getCommand().value().getBinaryCommand(), std::string("111111111010\n111111110111\n000000001111\n"));
		}

		TEST(StatmentSymbolData10, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.data\t  \t-6  \t , \t -9 , +15-   ; comment \t 15 ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getException().value(), std::string("Assembler invalid argument"));
		}

		TEST(StatmentSymbolData11, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.data\t  \t-6  \t , \t -9- , +15   ; comment \t 15 ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getException().value(), std::string("Assembler invalid argument"));
		}

		TEST(StatmentSymbolData12, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.data\t  \t  \t  \t    ; comment \t 15 ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getException().value(), std::string("Assembler invalid argument"));
		}

		TEST(StatmentSymbolData13, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.data\t  ,\t  \t  \t    ; comment \t 15 ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getException().value(), std::string("Assembler invalid argument"));
		}

		TEST(StatmentSymbolData14, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.data\t  6,\t  \t  \t    ; comment \t 15 ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getException().value(), std::string("Assembler invalid argument"));
		}

		TEST(StatmentSymbolString, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.string\t  \t  \t  \t \"abcdef\"   ; comment \t 15 ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getCommand().value().getBinaryCommand(),
				std::string("000001100001\n000001100010\n000001100011\n000001100100\n000001100101\n000001100110\n000000000000\n"));
		}

		TEST(StatmentSymbolString1, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.string\t  \t\"  \t  \t \"abcdef\"   ; comment \t 15 ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getException().value(), std::string("Assembler invalid argument"));
		}

		TEST(StatmentSymbolString2, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.string\t  \t  \t  \t \"abcdef\" \"as\"   ; comment \t 15 ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getException().value(), std::string("Assembler invalid argument"));
		}

		TEST(StatmentSymbolString3, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.string\t  \t ;  \t  \t \"abcdef\"   ; comment \t 15 ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getException().value(), std::string("Assembler invalid argument"));
		}

		TEST(StatmentSymbolString4, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.string\t  \t \t  \t    ; comment \t 15 ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getException().value(), std::string("Assembler invalid argument"));
		}

		TEST(StatmentSymbolEntry, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.entry\t  HELLO \t \t  \t    ; comment \t 15 ");
			stmt2.parse();

			auto symbol = stmt2.getCommandSymbol().value();
			auto symbolType = symbol.getType();
			EXPECT_EQ(symbol.getName(), std::string("HELLO"));
			EXPECT_EQ(symbol.getType(), Assembler::SymbolType::ENTRY);
		}

		TEST(StatmentSymbolEntryException1, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.entry\t  HELLO \t \td  \t    ; comment \t 15 ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getException().value(), std::string("Assembler too many arguments"));
		}

		TEST(StatmentSymbolEntryException2, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.entry\t  HELLO@ \t \t  \t    ; comment \t 15 ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getException().value(), std::string("Assembler invalid argument"));
		}

		TEST(StatmentSymbolExtern, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.extern\t  HELLO \t \t  \t    ; comment \t 15 ");
			stmt2.parse();

			auto symbol = stmt2.getCommandSymbol().value();
			auto symbolType = symbol.getType();
			EXPECT_EQ(symbol.getName(), std::string("HELLO"));
			EXPECT_EQ(symbol.getType(), Assembler::SymbolType::EXTERN);
		}

		TEST(StatmentSymbolExternException1, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.entry\t  HELLO \t \td  \t    ; comment \t 15 ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getException().value(), std::string("Assembler too many arguments"));
		}

		TEST(StatmentSymbolExternException2, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.extern\t  HELLO@ \t \t  \t    ; comment \t 15 ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getException().value(), std::string("Assembler invalid argument"));
		}
		
		TEST(StatmentSymbolExternException3, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t. extern\t  HELLO@ \t \t  \t    ; comment \t 15 ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getException().value(), std::string("Assembler unknwon instruction"));
		}

		TEST(StatmentSymbolExternException4, StatmentTesterComamands)
		{
			Assembler::Statment stmt2(" \t STR \t :   \t  \t.extern\t   \t \t  \t    ; comment \t 15 ");
			stmt2.parse();

			EXPECT_EQ(stmt2.getException().value(), std::string("Assembler missing argument"));
		}
	}
}