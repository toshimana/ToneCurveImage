#pragma once

#include <array>

namespace parseFile
{
	typedef std::array<unsigned char, 256> Table;

	bool read( const std::string& path, Table& table );
}