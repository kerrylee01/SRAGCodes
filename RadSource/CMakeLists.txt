######################################################################
#
# CMakeLists.txt for GCR Source
#
######################################################################
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT( gcrsource )

MESSAGE ( STATUS "Building SRAG GCR Source Library" )

# set the source files
SET(SRAG_SRC  "CRadEnvironment.cpp")
LIST(APPEND SRAG_SRC "CSource.cpp")
LIST(APPEND SRAG_SRC "CSpatial.cpp")
LIST(APPEND SRAG_SRC "CSpectrum.cpp")
LIST(APPEND SRAG_SRC "CPoint3D.cpp")
LIST(APPEND SRAG_SRC "CPoint2D.cpp")
LIST(APPEND SRAG_SRC "CParticleState.cpp")
LIST(APPEND SRAG_SRC "CIsotropic.cpp")
LIST(APPEND SRAG_SRC "CBeam.cpp")

# set the headers
SET ( SRAG_HEADERS "CBeam.h" )
LIST(APPEND SRAG_HEADERS "CIsotropic.h")
LIST(APPEND SRAG_HEADERS "CParticleState.h")
LIST(APPEND SRAG_HEADERS "CPoint2D.h")
LIST(APPEND SRAG_HEADERS "CPoint3D.h")
LIST(APPEND SRAG_HEADERS "CRadEnvironment.h")
LIST(APPEND SRAG_HEADERS "CSource.h")
LIST(APPEND SRAG_HEADERS "CSpatial.h")
LIST(APPEND SRAG_HEADERS "CSpectrum.h")

# use the main as a test for now
SET( TEST_MAIN "main.cpp")

# set the includes
INCLUDE_DIRECTORIES( ${INCLUDE_DIRECTORIES} ${CMAKE_CURRENT_SOURCE_DIR})

# Create Source Library
ADD_LIBRARY( gcrsource SHARED ${SRAG_SRC} )

# add executable
ADD_EXECUTABLE("test_main" ${TEST_MAIN})
TARGET_LINK_LIBRARIES("test_main" gcrsource)

# set the headers to install
SET_TARGET_PROPERTIES( gcrsource PROPERTIES PUBLIC_HEADER "${SRAG_HEADERS}" )

# need c++11 support
SET_PROPERTY(TARGET gcrsource PROPERTY CXX_STANDARD 11)
SET_PROPERTY(TARGET "test_main" PROPERTY CXX_STANDARD 11)

# Put the library in Lib
INSTALL ( TARGETS gcrsource
  RUNTIME DESTINATION "bin"
  LIBRARY DESTINATION "lib"
  ARCHIVE DESTINATION "lib"
  PUBLIC_HEADER DESTINATION "include" )

# add the tests
add_subdirectory(test)

# Put the test in bin
INSTALL ( TARGETS "test_main"
  RUNTIME DESTINATION "bin"
  LIBRARY DESTINATION "lib"
  ARCHIVE DESTINATION "lib"
  PUBLIC_HEADER DESTINATION "include" )

