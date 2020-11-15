#pragma once

#include <string>
#include <vector>

namespace Assembler
{
	enum class SymbolType
	{
		CODE,
		DATA,
		ENTRY,
		EXTERN
	};

	class Symbol
	{
	private:
		std::string _name;
		SymbolType _type;
		std::optional<size_t> _commandNumber;

	public:
		Symbol(const std::string& name, SymbolType type, size_t commandNumber)
			: _name(name), _type(type), _commandNumber(commandNumber)
		{}

		Symbol(const std::string& name, SymbolType type, std::optional<size_t> commandNumber)
			: _name(name), _type(type), _commandNumber(commandNumber)
		{}

		const std::string& getName() const
		{
			return _name;
		}

		SymbolType getType() const
		{
			return _type;
		}

		void setType(SymbolType t)
		{
			_type = t;
		}

		std::optional<size_t> getCommandNumber() const
		{
			return _commandNumber;
		}

		void setCommandNumber(size_t value)
		{
			_commandNumber = value;
		}
	};
}

