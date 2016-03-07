#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <boosttool/filesystem.hpp>

#include "parseFile.h"

namespace fs = boost::filesystem;

namespace
{
	void convertFile( const fs::path& p, const parseFile::Table& table, const fs::path& outputDir )
	{
		cv::Mat_<unsigned char> grayImage = cv::imread( p.string(), cv::IMREAD_GRAYSCALE );
		if( grayImage.empty() ) return;


		cv::Mat_<unsigned char> convertImage = grayImage.clone();
		for ( auto it = convertImage.begin(); it != convertImage.end(); ++it )
		{
			*it = table[*it];
		}

		fs::create_directories( outputDir );

		fs::path outputPath = outputDir / p.filename();
		cv::imwrite( outputPath.string(), convertImage );
	}
}

int main( int argc, char* argv[] )
{
	parseFile::Table table;
	fs::path exePath( argv[0] );
	fs::path exeDir = exePath.parent_path();
	fs::path tablePath = exeDir / "ToneCurve.csv";

	bool parseResult = parseFile::read( tablePath.string(), table );
	if ( !parseResult ) {
		std::cerr << "fail to read : " << tablePath.string() << std::endl;
		return -1;
	}

	for ( int i = 1; i < argc; ++i )
	{
		fs::path filePath( argv[i] );

		if ( fs::is_directory( filePath ) ) {
			BOOST_FOREACH(const fs::path& p, std::make_pair(fs::recursive_directory_iterator(filePath),
				fs::recursive_directory_iterator())) {
					fs::path relatePath = boosttool::make_relative( filePath, p );
					fs::path outputDir = exeDir / "output" / relatePath.parent_path();
					convertFile( p, table, outputDir );
			}

		} else if ( fs::exists( filePath ) ) {
			convertFile( filePath, table, ( exeDir / "output" ).string() );
		}
	}
	return 0;
}