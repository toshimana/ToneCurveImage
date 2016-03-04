#include <boost/filesystem.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

#include "parseFile.h"

namespace fs = boost::filesystem;

int main( int argc, char* argv[] )
{
	parseFile::Table table;
	bool parseResult = parseFile::read( "toneCurve.csv", table );

	for ( int i = 1; i < argc; ++i )
	{
		fs::path filePath( argv[i] );
		cv::Mat_<unsigned char> grayImage = cv::imread( filePath.string(), cv::IMREAD_GRAYSCALE );

		cv::Mat_<unsigned char> convertImage = grayImage.clone();
		for ( auto it = convertImage.begin(); it != convertImage.end(); ++it )
		{
			*it = table[*it];
		}

		fs::path outputDir = filePath.parent_path() / "output";
		fs::create_directories( outputDir );

		fs::path outputPath = outputDir / filePath.filename();
		cv::imwrite( outputPath.string(), convertImage );
	}
	return 0;
}