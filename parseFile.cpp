#include "parseFile.h"
#include <fstream>
#include <boost/log/trivial.hpp>

/*****************************************************************************/
// Boost.Spirit.Qi
// パース処理
/*****************************************************************************/
#define BOOST_SPIRIT_USE_PHOENIX_V3

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>

namespace qi = boost::spirit::qi;

namespace
{
	template<typename Iterator>
	struct parseFileImpl
		: qi::grammar<Iterator, std::vector<unsigned short>()>
	{
		qi::rule<Iterator, std::vector<unsigned short>()> result;

		parseFileImpl()
			: parseFileImpl::base_type( result )
		{
			result %= qi::repeat(256)[ qi::ushort_ >> *qi::eol ];
		}
	};
};


bool
parseFile::read( const std::string& path, parseFile::Table& table )
{
	std::string in;
	{
		std::ifstream ifs( path.c_str() );
		if ( !ifs.is_open() ) {
			return false;
		}

		try {
			in = std::string( (std::istreambuf_iterator<char>( ifs )), std::istreambuf_iterator<char>() );
		}
		catch ( ... ) {
			return false;
		}
	}
	parseFileImpl<std::string::iterator> parseFI;

	std::string str( in );
	auto it = str.begin();
	std::vector<unsigned short> table_raw;

	bool parseRet = qi::phrase_parse( it, str.end(), parseFI, boost::spirit::ascii::space, table_raw );
	bool ret = parseRet && (it == str.end());
	if ( ret ) {
		std::transform( table_raw.begin(), table_raw.end(), table.begin(), []( unsigned short s ){return static_cast<unsigned char>(s); } );
	}
	return ret;
}

