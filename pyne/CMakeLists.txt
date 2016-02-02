# CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
MESSAGE ( STATUS "Including Amalgamated PyNE")

ADD_SUBDIRECTORY(test)

SET ( CODE_SRCDIR      "pyne" )
SET ( CODE_SRC_FILES   "pyne.cpp"  )
SET ( CODE_PUB_HEADERS "pyne.h" )

add_library( pyne_static STATIC ${CODE_SRC_FILES})
 
target_include_directories( pyne_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

SET_TARGET_PROPERTIES( pyne_static PROPERTIES PUBLIC_HEADER "${CODE_PUB_HEADERS}" )

INSTALL( TARGETS       pyne_static
  LIBRARY        DESTINATION   "${INSTALL_LIB_DIR}"
  ARCHIVE        DESTINATION   "${INSTALL_ARCH_DIR}"
  PUBLIC_HEADER  DESTINATION   "${INSTALL_INCLUDE_DIR}"
  )

target_link_libraries(pyne_static)




