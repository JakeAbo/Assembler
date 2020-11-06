#pragma once

#include <exception>

namespace Assembler
{
	class AssemblerException : public std::exception
	{
	protected:
		static constexpr auto EXCEPTION_GENERAL = "Assembler exception";
		static constexpr auto EXCEPTION_OVERFLOW = "Assembler is 10 bit system - means 10 bit numaric values";

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
}