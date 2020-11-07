#pragma once

#include <vector>
#include <sstream>

#include "Word.hpp"
#include "AssemblerStreams.hpp"

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