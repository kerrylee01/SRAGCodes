// FluDAG/src/test/test_FlukaFuncs.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <cassert>

#include "CParticleState.h"
#include "CRadEnvironment.h"
#include "CIsotropic.h"
#include "CBeam.h"

#include "CSphericalElement.hpp"

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
  int a_iPartList[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28};
  //int a_iPartList[] = {1};
  std::vector<int> v_iPartList (a_iPartList, a_iPartList + sizeof(a_iPartList) / sizeof(int));
  //for(int i = 1; i <= 28; i++) 
  //v_iPartList.push_back(i);
  CIsotropic* p_Isotropic = new CIsotropic(1.0, false);
  CSource *source = new CSource(p_Isotropic);
  std::string file = src_file;
  source->AddBOM2014Spectra(file, v_iPartList);
  source->Sample(gen,particleState);
}

// test the SphericalElement class
TEST_F(RadSourceTest, SphericalElementSetup) {
  CSphericalElement *sph = new CSphericalElement();
  sph->set_origin(0,0,0);
  sph->set_target(15,15);
  sph->set_radius(50,0);  
  // no segfault = pass
}

// test the SphericalElement class
TEST_F(RadSourceTest, SphericalElementConstructor) {
  CSphericalElement *sph = new CSphericalElement(0,0,0,15,15,50,0);
  // no segfault = pass
}

// test the SphericalElement sample
TEST_F(RadSourceTest, SphericalElementSampleGen) {
  CSphericalElement *sph = new CSphericalElement(0,0,0,15,15,50,0);
  std::random_device rd;
  std::mt19937_64 gen(12345);
  sph->Sample(gen);
  CPoint3D *point = sph->GetPosition();
  double x = point->GetX();
  double y = point->GetY();
  double z = point->GetZ();

  EXPECT_NEAR(x,-14.316007088081156,1e-12);
  EXPECT_NEAR(y,-35.752740944487599,1e-12);
  EXPECT_NEAR(z, 31.887198936412876,1e-12);

  for ( int i = 0 ; i < 10000 ; i++ ) {
    sph->Sample(gen);
    CPoint3D *point = sph->GetPosition();
    double x = point->GetX();
    double y = point->GetY();
    double z = point->GetZ();

    // sqrt(sum of squares) to should be 50.
    EXPECT_NEAR(std::sqrt((x*x)+(y*y)+(z*z)),50.0,1e-12);
    // all points should be in the +ve hemisphere -50 to 50
    EXPECT_GE(x,-50.0);
    EXPECT_LE(x,50.0);
    EXPECT_GE(y,-50.0);
    EXPECT_LE(y,50.0);
    EXPECT_GE(z,0.);
    EXPECT_LE(z,50.0);
  }
  // no segfault = pass
}

// test the SphericalElement sample
TEST_F(RadSourceTest, SphericalElementSampleRanArr) {
  CSphericalElement *sph = new CSphericalElement(0,0,0,15,15,50,0);
  std::vector<double> rands = {0.5,0.5,0.5,0.5};
  sph->Sample(rands);
  CPoint3D *point = sph->GetPosition();
  double x = point->GetX();
  double y = point->GetY();
  double z = point->GetZ();

  EXPECT_NEAR(x,-35.35533905932737,1e-12);
  EXPECT_NEAR(y,4.3297802811774655e-15,1e-12);
  EXPECT_NEAR(z,35.355339059327378,1e-12);
  // no segfault = pass
}
