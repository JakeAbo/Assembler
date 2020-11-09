#pragma once

#include <exception>

namespace Assembler
{
	class AssemblerException : public std::exception
	{
	protected:
		static constexpr auto EXCEPTION_GENERAL			= "Assembler exception";
		static constexpr auto EXCEPTION_OVERFLOW		= "Assembler is 10 bit system - means 10 bit numaric values";
		static constexpr auto EXCEPTION_UNABLE_OPEN		= "Assembler unable to open .asm file";
		static constexpr auto EXCEPTION_LINE_ABOVE_80	= "Assembler line until 80 characters";
		static constexpr auto EXCEPTION_SYNTAX_SYMBOL	= "Assembler symbol must start with alpha letter and contain only alphanumeric characters with max length of 31. Also can't be any of registers or operator names.";

	public:
		virtual const char* what() const throw()
		{
			return EXCEPTION_GENERAL;
		}
	};

	class AssemblerExceptionOverflow : public AssemblerException
	{
	public:
		virtual const char* what() const throw()
		{
			return EXCEPTION_OVERFLOW;
		}
	};

	class AssemblerExceptionUnableOpen : public AssemblerException
	{
	public:
		virtual const char* what() const throw()
		{
			return EXCEPTION_UNABLE_OPEN;
		}
	};

	class AssemblerExceptionLineOverflow : public AssemblerException
	{
	public:
		virtual const char* what() const throw()
		{
			return EXCEPTION_LINE_ABOVE_80;
		}
	};

	class AssemblerExceptionSyntaxSymbol : public AssemblerException
	{
	public:
		virtual const char* what() const throw()
		{
			return EXCEPTION_SYNTAX_SYMBOL;
		}
	};
}