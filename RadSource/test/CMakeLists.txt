#PROJECT(GCRUnitTests)

# radsource test source
SET (radsource_test_source ${CMAKE_CURRENT_SOURCE_DIR}/test_RadSource.cpp)

# c callable test source
SET (source_test_source ${CMAKE_CURRENT_SOURCE_DIR}/test_Source.cpp)


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

# add the radsource test exec
ADD_EXECUTABLE (radsource_test
                radsource_unit_test_driver.cc
	              ${radsource_test_source})

# add the source test exec
ADD_EXECUTABLE (source_test
                radsource_unit_test_driver.cc
                ${source_test_source})

# libraries needed
TARGET_LINK_LIBRARIES(radsource_test ${LIBS})
TARGET_LINK_LIBRARIES(source_test ${LIBS})

# c++ 11 needed
SET_PROPERTY(TARGET radsource_test PROPERTY CXX_STANDARD 11)

Message(Display ${CMAKE_SOURCE_DIR})

# add the RadSource tests
ADD_TEST(NAME RadSourceTest.NoFile COMMAND radsource_test --src_file=${CMAKE_SOURCE_DIR}/RadSource/GCRSource/this_file_doesnt_exist.txt --gtest_filter=RadSourceTest.SetUp)
ADD_TEST(NAME RadSourceTest.Setup COMMAND radsource_test --src_file=${CMAKE_SOURCE_DIR}/RadSource/GCRSource/allflux.dat --gtest_filter=RadSourceTest.SetUp)
# the only test that doesnt need a file
ADD_TEST(NAME RadSourceTest.IsotropicDistribution COMMAND radsource_test --gtest_filter=RadSourceTest.IsotropicDistribution)
ADD_TEST(NAME RadSourceTest.Spectrum COMMAND radsource_test --src_file=${CMAKE_SOURCE_DIR}/Radsource/GCRSource/January2003/January2003H.dat --gtest_filter=RadSourceTest.Spectrum)
ADD_TEST(NAME RadSourceTest.Spectrum2 COMMAND radsource_test --src_file=${CMAKE_SOURCE_DIR}/RadSource/GCRSource/allflux.dat --gtest_filter=RadSourceTest.Spectrum2)
ADD_TEST(NAME RadSourceTest.Source COMMAND radsource_test --src_file=${CMAKE_SOURCE_DIR}/RadSource/GCRSource/allflux.dat --gtest_filter=RadSourceTest.Source)
ADD_TEST(NAME RadSourceTest.GCRSource COMMAND radsource_test --src_file=${CMAKE_SOURCE_DIR}/Radsource/GCRSource/January2003/ --gtest_filter=RadSourceTest.GCRSource)
ADD_TEST(NAME RadSourceTest.Sample COMMAND radsource_test --src_file=${CMAKE_SOURCE_DIR}/RadSource/GCRSource/allflux.dat --gtest_filter=RadSourceTest.Sample)
ADD_TEST(NAME RadSourceTest.SphericalElementSetup COMMAND radsource_test --src_file=${CMAKE_SOURCE_DIR}/RadSource/GCRSource/allflux.dat --gtest_filter=RadSourceTest.SphericalElementSetup)
ADD_TEST(NAME RadSourceTest.SphericalElementSampleGen COMMAND radsource_test --src_file=${CMAKE_SOURCE_DIR}/RadSource/GCRSource/allflux.dat --gtest_filter=RadSourceTest.SphericalElementSampleGen)
ADD_TEST(NAME RadSourceTest.SphericalElementSampleRanArr COMMAND radsource_test --src_file=${CMAKE_SOURCE_DIR}/RadSource/GCRSource/allflux.dat --gtest_filter=RadSourceTest.SphericalElementSampleRanArr)
ADD_TEST(NAME RadSourceTest.ReducedParticleList COMMAND radsource_test --src_file=${CMAKE_SOURCE_DIR}/RadSource/GCRSource/allflux.dat --gtest_filter=RadSourceTest.ReducedParticleList)
ADD_TEST(NAME RadSourceTest.ReducedParticleList2014 COMMAND radsource_test --src_file=${CMAKE_SOURCE_DIR}/RadSource/GCRSource/January2003/ --gtest_filter=RadSourceTest.ReducedParticleList2014)
ADD_TEST(NAME RadSourceTest.FlukaParticleFunctionsH COMMAND radsource_test --src_file=${CMAKE_SOURCE_DIR}/RadSource/GCRSource/January2003/ --gtest_filter=RadSourceTest.FlukaParticleFunctionsH)
ADD_TEST(NAME RadSourceTest.FlukaParticleFunctionsHe COMMAND radsource_test --src_file=${CMAKE_SOURCE_DIR}/RadSource/GCRSource/January2003/ --gtest_filter=RadSourceTest.FlukaParticleFunctionsHe)
# add the c callable function tests
ADD_TEST(NAME SourceTest.SetUpSource COMMAND source_test --gtest_filter=SourceTest.SetUpSource --src_file=${CMAKE_SOURCE_DIR})
ADD_TEST(NAME SourceTest.Sample1 COMMAND source_test --gtest_filter=SourceTest.Sample1 --src_file=${CMAKE_SOURCE_DIR})
ADD_TEST(NAME SourceTest.Sample2 COMMAND source_test --gtest_filter=SourceTest.Sample2 --src_file=${CMAKE_SOURCE_DIR})
ADD_TEST(NAME BONSourceTest.SetUpSource COMMAND source_test --gtest_filter=BONSourceTest.SetUpSource --src_file=${CMAKE_SOURCE_DIR})
ADD_TEST(NAME BONSourceTest.Sample1 COMMAND source_test --gtest_filter=BONSourceTest.Sample1 --src_file=${CMAKE_SOURCE_DIR})
ADD_TEST(NAME BONSourceTest.Sample2 COMMAND source_test --gtest_filter=BONSourceTest.Sample2 --src_file=${CMAKE_SOURCE_DIR})
ADD_TEST(NAME BON2014SourceTest.SetUpSource COMMAND source_test --gtest_filter=BONSourceTest.SetUpSource --src_file=${CMAKE_SOURCE_DIR})
ADD_TEST(NAME BON2014SourceTest.Sample1 COMMAND source_test --gtest_filter=BONSourceTest.Sample1 --src_file=${CMAKE_SOURCE_DIR})
ADD_TEST(NAME BON2014SourceTest.Sample2 COMMAND source_test --gtest_filter=BONSourceTest.Sample2 --src_file=${CMAKE_SOURCE_DIR})
