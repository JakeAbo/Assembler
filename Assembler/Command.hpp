#pragma once

#include <vector>
#include <sstream>
#include <string>

#include "Word.hpp"
#include "AssemblerStreams.hpp"
#include "SymbolPool.hpp"

namespace Assembler
{
	class Command
	{
	private:
		std::vector<Word> _words;

	public:
		Command()
			: _words()
		{}

		void clear()
		{
			_words.clear();
		}

		void addWord(const Word& word)
		{
			_words.emplace_back(word);
		}

		void addWords(std::initializer_list<Word> words)
		{
			_words.insert(_words.end(), words);
		}

		void updateSymbols()
		{
			for (auto& w : _words)
			{
				if (w.isSymbol())
				{
					auto sym = SymbolPool::Instance().getSymbol(w.getSymbol().value());
					w.setSymbol(sym.value().getCommandNumber().value());
					if (sym.value().getType() == SymbolType::EXTERN)
						w.setExternal();
					else
						w.setRelocatable();
				}
			}
		}

		friend BinaryStream& operator<<(BinaryStream& os, const Command& cmd)
		{
			for (const auto& word : cmd._words)
			{
				os << word << std::endl;
			}

			return os;
		}

		friend Base64Stream& operator<<(Base64Stream& os, const Command& cmd)
		{
			for (const auto& word : cmd._words)
			{
				os << word << std::endl;
			}

			return os;
		}

		size_t getNumberOfWords() const
		{
			return _words.size();
		}

		const std::string getBinaryCommand() const
		{
			BinaryStream os;

			os << *this;

			return os.str();
		}

		const std::string getBase64Command() const
		{
			Base64Stream os;

			os << *this;

			return os.str();
		}
	};
}