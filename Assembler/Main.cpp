#include <iostream>
#include <bitset>

#include "Word.hpp"
#include "AssemblerExceptions.hpp"

int main()
{
	try 
	{
		throw Assembler::AssemblerExceptionOverflow();
	}
	catch (const Assembler::AssemblerException& ex)
	{
		std::cout << ex.what() << std::endl;
	}


}