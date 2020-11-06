#pragma once

#include <vector>
#include <sstream>

#include "Word.hpp"

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

		friend std::ostream& operator<<(std::ostream& os, const Command& cmd)
		{
			for (const auto& word : cmd._words)
			{
				os << word << std::endl;
			}

			return os;
		}

		const std::string getBinaryCommand()
		{
			std::ostringstream os;

			os << *this;

			return os.str();
		}
	};
}