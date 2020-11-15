#pragma once

#include <map>
#include <string>
#include <optional>
#include "Symbol.hpp"

namespace Assembler
{
	class SymbolPool 
	{
	private:
		std::map<std::string, Symbol> _symbols;
		size_t _ic;
		size_t _dc;

		SymbolPool()
			:_ic(0), _dc(0)
		{}

	public:
		static SymbolPool& Instance() 
		{
			static SymbolPool myInstance;
			return myInstance;
		}

		// delete copy and move constructors and assign operators
		SymbolPool(SymbolPool const&) = delete;             // Copy construct
		SymbolPool(SymbolPool&&) = delete;                  // Move construct
		SymbolPool& operator=(SymbolPool const&) = delete;  // Copy assign
		SymbolPool& operator=(SymbolPool&&) = delete;      // Move assign
		
		bool isSymbolExsits(const std::string& symbolName) const
		{
			return (_symbols.find(symbolName) != _symbols.end());
		}

		std::optional<Symbol> getSymbol(const std::string& symbolName) const
		{
			if (!isSymbolExsits(symbolName))
				return {};
			return _symbols.at(symbolName);
		}

		bool addSymbol(const std::string& symbolName, const Symbol& symbol)
		{
			if (isSymbolExsits(symbolName))
				return false;

			_symbols.emplace(std::pair<std::string, Symbol>(symbolName, symbol));
		}

		bool addSymbol(const std::string& symbolName, SymbolType type, size_t commandNumber)
		{
			if (isSymbolExsits(symbolName))
			{
				if (_symbols.at(symbolName).getType() != SymbolType::ENTRY)
					return false;
				else
				{
					_symbols.at(symbolName).setCommandNumber(commandNumber);
					return true;
				}
			}

			_symbols.emplace(std::pair<std::string, Symbol>(symbolName, { symbolName, type, commandNumber }));
			return true;
		}

		bool addSymbolEntryOrExtern(const std::string& symbolName, SymbolType type, std::optional<size_t> commandNumber)
		{
			if (isSymbolExsits(symbolName))
			{
				if (type != SymbolType::ENTRY)
					return false;
				else
				{
					_symbols.at(symbolName).setType(type);
					return true;
				}
			}

			_symbols.emplace(std::pair<std::string, Symbol>(symbolName, { symbolName, type, commandNumber }));
			return true;
		}

		size_t getIc() const
		{
			return _ic;
		}

		size_t getDc() const
		{
			return _dc;
		}

		void addIc(size_t value)
		{
			_ic += value;
		}

		void addDc(size_t value)
		{
			_dc += value;
		}

		void clear()
		{
			_symbols.clear();
			_ic = _dc = 0;
		}
	};
}
