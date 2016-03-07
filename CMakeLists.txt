CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT( ToneCurveImage )

# OpenCV
FIND_PACKAGE( OpenCV REQUIRED )
IF ( OpenCV_FOUND )
  INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )
ENDIF()

# Boost
FIND_PATH( BOOST_ROOT boost/version.hpp /usr/local/include )
FIND_PACKAGE( Boost REQUIRED COMPONENTS filesystem )
IF ( Boost_FOUND )
  INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
  LINK_DIRECTORIES( ${Boost_LIBRARY_DIR} )
ENDIF()

# Tool
FIND_PATH( TOOL_DIR tool.hpp
  /usr/local/include )
INCLUDE_DIRECTORIES( ${TOOL_DIR} )

ADD_EXECUTABLE( ToneCurveImage main.cpp parseFile.cpp )
TARGET_LINK_LIBRARIES( ToneCurveImage ${OpenCV_LIBS} )