CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# enable tests
ENABLE_TESTING()

# Needed for finding cmake modules
SET ( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake)

SET(INSTALL_BIN_DIR "bin")
SET(INSTALL_LIB_DIR "lib")
SET(INSTALL_ARCH_DIR "lib")
SET(INSTALL_HEADER_DIR "include")

add_subdirectory(RadSource)
add_subdirectory(gtest)