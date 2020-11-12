#pragma once

#include <string>
#include <vector>

namespace Assembler
{
	enum class SymbolType
	{
		ENTRY,
		EXTERN
	};

	class Symbol
	{
	private:
		std::string _name;
		SymbolType _type;
		unsigned int _commandNumber;

	public:
		Symbol(const std::string& name, SymbolType type, unsigned int commandNumber)
			: _name(name), _type(type), _commandNumber(commandNumber)
		{}

		const std::string& getName()
		{
			return _name;
		}

		SymbolType getType()
		{
			return _type;
		}
	};
}

