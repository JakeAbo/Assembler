#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <map>

#include "Statment.hpp"

namespace Assembler
{
	class AsmFileReader
	{
	private:
		std::string _filePath;
		std::fstream _file;
		std::vector<Statment> _stmts;
		std::optional<std::string> _exceptionFile;

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
			try
			{
				_file.open(_filePath);
				if (!isFileOpen())
					throw AssemblerExceptionUnableOpen();
			} 
			catch (const AssemblerException & ex)
			{
				_exceptionFile = ex.what();
			}
		}

		void compileFile()
		{
			try
			{
				if (!isFileOpen())
					throw AssemblerExceptionUnableOpen();

				std::string line;

				while (std::getline(_file, line))
				{
					Statment currentStmt(line);
					currentStmt.parse();
					if(!currentStmt.isEmptyOrComment()) _stmts.emplace_back(std::move(currentStmt));
				}

				//Second iterate - update symbols according to symbol table
				for (auto& s : _stmts)
				{
					s.updateSymbols();
				}
			}
			catch (const AssemblerException & ex)
			{
				_exceptionFile = ex.what();
			}
		}

		friend BinaryStream& operator<<(BinaryStream& os, const AsmFileReader& file)
		{
			for (const auto& s : file._stmts)
				os << s;

			return os;
		}

		friend Base64Stream& operator<<(Base64Stream& os, const AsmFileReader& file)
		{
			for (const auto& s : file._stmts)
				os << s;

			return os;
		}

		const std::optional<std::string>& getException()
		{
			return _exceptionFile;
		}
	};
}