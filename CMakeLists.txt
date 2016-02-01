CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
# enable tests
ENABLE_TESTING()

SET(INSTALL_BIN_DIR "bin")
SET(INSTALL_LIB_DIR "lib")
SET(INSTALL_ARCH_DIR "lib")
SET(INSTALL_HEADER_DIR "include")

# make the gcrsource
add_subdirectory(pyne)
add_subdirectory(RadSource)
add_subdirectory(gtest)