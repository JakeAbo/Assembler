#include <iostream>
#include <bitset>

#include "Word.hpp"
#include "AssemblerExceptions.hpp"

#include "AssemblerStreams.hpp"

#include "StringUtility.hpp"
#include "AsmFileReader.hpp"

int main()
{
	//Assembler::AsmFileReader f("C:\\Users\\Jack\\Documents\\persons\\jack\\Programming\\repo\\Assembler\\Debug\\aaa.txt");
	//f.openFile();
	//f.compileFile();

	//std::vector<std::string> vec = Assembler::StringUtility::splitBySpacesAndTabs(" \t \t     \t MAIN   \t \t :    \t \t \t    mov  \t \t    ");
	std::vector<std::string> vec = Assembler::StringUtility::splitBySpacesAndTabs(" \t \t     \t ;   \t \t :    \t \t \t    mov  \t \t    ");
	
	std::vector<std::string> vec2 = Assembler::StringUtility::splitBySpacesAndTabs(" \t \t     \t    \t \t     \t \t \t      \t \t    ");

	



}