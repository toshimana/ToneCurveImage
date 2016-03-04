#include <boost/filesystem.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

namespace fs = boost::filesystem;

int main( int argc, char* argv[] )
{
	for ( int i = 1; i < argc; ++i )
	{
		fs::path filePath( argv[1] );
		cv::Mat grayImage = cv::imread( filePath.string(), cv::IMREAD_GRAYSCALE );

		cv::Mat convertImage = grayImage.clone();

		fs::path outputDir = filePath.parent_path() / "output";
		fs::create_directories( outputDir );

		fs::path outputPath = outputDir / filePath.filename();
		cv::imwrite( outputPath.string(), convertImage );
	}
	return 0;
}