// FluDAG/src/test/test_FlukaFuncs.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <cassert>

#include "CParticleState.h"
#include "CRadEnvironment.h"
#include "CIsotropic.h"
#include "CBeam.h"

extern std::string src_file;

//---------------------------------------------------------------------------//
// TEST FIXTURES
//---------------------------------------------------------------------------//
class RadSourceTest : public ::testing::Test
{
 protected:

  // initalize variables for each test
  virtual void SetUp() {

    int a_iPartList[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28};
    //int a_iPartList[] = {1};
    std::vector<int> v_iPartList (a_iPartList, a_iPartList + sizeof(a_iPartList) / sizeof(int));
    //for(int i = 1; i <= 28; i++) 
    //v_iPartList.push_back(i);
    CIsotropic* p_Isotropic = new CIsotropic(1.0, false);
    CSource *source = new CSource(p_Isotropic);
    std::string file = src_file;
    source->AddBOM2014Spectra(file, v_iPartList);
  }

 protected:
  CSource *source;
  CIsotropic *spatial;
};

//---------------------------------------------------------------------------//
// Test setup outcomes
TEST_F(RadSourceTest, SetUp) {
}

//---------------------------------------------------------------------------//
// Test setup outcomes
TEST_F(RadSourceTest, Sample) {
  CParticleState* particleState = new CParticleState();

  std::random_device rd;
  std::mt19937_64 gen(rd());
  SetUp();
  source->Sample(gen,particleState);
}

