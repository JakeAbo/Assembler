#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include "Statment.hpp"

namespace Assembler
{
	class AsmFileReader
	{
	private:
		std::string _filePath;
		std::fstream _file;
		std::vector<Statment> _stmts;
	
		bool isFileOpen()
		{
			return _file.is_open();
		}

	public:
		AsmFileReader(const std::string& filePath)
			: _filePath(filePath)
		{

		}

		~AsmFileReader()
		{
			_file.close();
		}

		void openFile()
		{
			_file.open(_filePath);

			if (!isFileOpen())
				throw new AssemblerExceptionUnableOpen();
		}

		void compileFile()
		{
			if (!isFileOpen())
				throw new AssemblerExceptionUnableOpen();
			
			std::string line;

			while (std::getline(_file, line))
			{
				Statment currentStmt(line);
				currentStmt.parse();
				_stmts.emplace_back(std::move(currentStmt));
			}

			//Second iterate - update symbols according to symbol table
		}
	};
}