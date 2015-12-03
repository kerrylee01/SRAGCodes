#PROJECT(GCRUnitTests)
 
# test source
SET (radsource_test_source ${CMAKE_CURRENT_SOURCE_DIR}/test_RadSource.cpp)

# set libraries needed to link to test cases
SET(LIBS
    pthread
    gtest
    gcrsource
    pthread
)

# includes
INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/RadSource
                     ${CMAKE_SOURCE_DIR}/gtest/gtest-1.7.0/include/)

# add the test exec
ADD_EXECUTABLE (radsource_test
        radsource_unit_test_driver.cc
	${radsource_test_source}
    )

# find the path to the source file
# FIND_PATH(source_file "allflux.dat" ${CMAKE_SOURCE_DIR}/RadSource/GCRSource )

# libraries needed
TARGET_LINK_LIBRARIES(radsource_test ${LIBS})

# c++ 11 needed
SET_PROPERTY(TARGET radsource_test PROPERTY CXX_STANDARD 11)

# run the test
ADD_TEST(NAME RadSourceTest.NoFile COMMAND radsource_test --src_file=${CMAKE_SOURCE_DIR}/RadSource/GCRSource/this_file_doesnt_exist.txt --gtest_filter=RadSourceTest.SetUp)
ADD_TEST(NAME RadSourceTest.Setup COMMAND radsource_test --src_file=${CMAKE_SOURCE_DIR}/RadSource/GCRSource/allflux.dat --gtest_filter=RadSourceTest.SetUp)
# the only test that doesnt need a file
ADD_TEST(NAME RadSourceTest.IsotropicDistribution COMMAND radsource_test --gtest_filter=RadSourceTest.IsotropicDistribution)
ADD_TEST(NAME RadSourceTest.Spectrum COMMAND radsource_test --src_file=${CMAKE_SOURCE_DIR}/Radsource/GCRSource/January2003/January2003H.dat --gtest_filter=RadSourceTest.Spectrum)
ADD_TEST(NAME RadSourceTest.Spectrum2 COMMAND radsource_test --src_file=${CMAKE_SOURCE_DIR}/RadSource/GCRSource/allflux.dat --gtest_filter=RadSourceTest.Spectrum2)
ADD_TEST(NAME RadSourceTest.Source COMMAND radsource_test --src_file=${CMAKE_SOURCE_DIR}/RadSource/GCRSource/allflux.dat --gtest_filter=RadSourceTest.Source)
ADD_TEST(NAME RadSourceTest.GCRSource COMMAND radsource_test --src_file=${CMAKE_SOURCE_DIR}/Radsource/GCRSource/January2003/ --gtest_filter=RadSourceTest.GCRSource)
ADD_TEST(NAME RadSourceTest.Sample COMMAND radsource_test --src_file=${CMAKE_SOURCE_DIR}/RadSource/GCRSource/allflux.dat --gtest_filter=RadSourceTest.Sample)

	
