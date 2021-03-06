######################################################################
#
# CMakeLists.txt for GCR Source
#
######################################################################
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT( gcrsource )

MESSAGE ( STATUS "Building SRAG GCR Source Library" )

FIND_PACKAGE ( HDF5 REQUIRED )
INCLUDE_DIRECTORIES( ${HDF5_INCLUDE_DIRS} )

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
LIST(APPEND SRAG_SRC "CSphericalElement.cpp")
LIST(APPEND SRAG_SRC "CSpherical.cpp")
LIST(APPEND SRAG_SRC "Source.cpp")
LIST(APPEND SRAG_SRC "../pyne/pyne.cpp")

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
LIST(APPEND SRAG_HEADERS "CSphericalElement.hpp")
LIST(APPEND SRAG_SRC "CSpherical.hpp")
LIST(APPEND SRAG_HEADERS "Source.h")
LIST(APPEND SRAG_SRC "../pyne/pyne.h")

# set the includes
INCLUDE_DIRECTORIES( ${INCLUDE_DIRECTORIES} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../pyne/ )

# Create Source Library
ADD_LIBRARY( gcrsource STATIC ${SRAG_SRC} )

TARGET_LINK_LIBRARIES(gcrsource ${HDF5_hdf5_hl_LIBRARY} ${HDF5_hdf5_LIBRARY})

# set the headers to install
SET_TARGET_PROPERTIES( gcrsource PROPERTIES PUBLIC_HEADER "${SRAG_HEADERS}" )


# c++11 support
add_definitions(-std=c++11)

# this should work!
# need c++11 support
#SET_PROPERTY(TARGET gcrsource PROPERTY CXX_STANDARD 11)
# SET_PROPERTY(TARGET "test_main" PROPERTY CXX_STANDARD 11)

# Put the library in Lib
INSTALL ( TARGETS gcrsource
  RUNTIME DESTINATION "bin"
  LIBRARY DESTINATION "lib"
  ARCHIVE DESTINATION "lib"
  PUBLIC_HEADER DESTINATION "include" )

# add the tests
add_subdirectory(test)

