#include "pch.h"
#include "Command.hpp"

namespace Tester
{
	namespace Command
	{
		Assembler::Command cmd;

		TEST(CommandOf2Words, CommandModule)
		{
			Assembler::Word w1, w2;
			w1.setAbsolute();
			w1.setDestinationImmediate();
			w1.setOpCodeMov();
			w1.setSourceDirect();

			w2.clear();
			w2.setRelocatable();
			w2.setDestinationDirectRegister();
			w2.setOpCodeAdd();
			w2.setSourceDirectRegister();

			cmd.clear();
			cmd.addWords({ w1, w2 });
			cmd.addWord(w1);
			
			EXPECT_EQ(cmd.getBinaryCommand(), "011000000100\n101001010110\n011000000100\n");
		}

	}
}