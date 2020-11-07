#pragma once

#include <ostream>
#include <sstream>

namespace Assembler
{
	class BinaryStream : public std::ostringstream
	{
	public:
		BinaryStream() = default;
	};

	class Base64Stream : public std::ostringstream
	{
	public:
		Base64Stream() = default;
	};
}