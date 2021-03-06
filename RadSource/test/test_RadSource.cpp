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
  std::cout << file << std::endl;
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

  for ( int i = 0 ; i < 100000 ; i++ ) {
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

// test the SphericalElement sample
TEST_F(RadSourceTest, ReducedParticleList) {
  // only use hydrogen/protons
  int a_iPartList[] = {1};
  std::vector<int> v_iPartList (a_iPartList, a_iPartList + sizeof(a_iPartList) / sizeof(int));
  // source dist
  CSphericalElement *sph = new CSphericalElement(0,0,0,15,15,50,0);
  // make a new source
  CSource *source = new CSource(sph);
  std::string file = src_file;
  // read the spectra into the source from the file 
  source->AddBOM2014Spectra(file, v_iPartList);
  // make the random device
  std::random_device rd;
  // seed it
  std::mt19937_64 gen(12345);

  // get the particle information
  CParticleState* particleState = new CParticleState();
  // sample
  for ( int i = 0 ; i < 100000 ; i++ ) {
    source->Sample(gen,particleState);
    EXPECT_EQ(particleState->GetParticleID(),1);
    EXPECT_GE(particleState->GetEnergy(),0.1);
    EXPECT_LE(particleState->GetEnergy(),1.e7);
    EXPECT_EQ(particleState->GetWeight(),1.0);
    // clear the state
    particleState->Clear();
  }
}

// test the sampling from a single element source
TEST_F(RadSourceTest, ReducedParticleList2014) {
  // source dist
  CSphericalElement *sph = new CSphericalElement(0,0,0,15,15,50,0);
  // make a new source
  CSource *source = new CSource(sph);
  std::string file = src_file;
  // read the spectra into the source from the file 
  source->AddSpectrum(new CSpectrum(file+"January2003H.dat",1),1.0);
  // make the random device
  std::random_device rd;
  // seed it
  std::mt19937_64 gen(12345);

  // get the particle information
  CParticleState* particleState = new CParticleState();
  // sample
  for ( int i = 0 ; i < 100000 ; i++ ) {
    source->Sample(gen,particleState);
    EXPECT_EQ(particleState->GetParticleID(),1);
    EXPECT_GE(particleState->GetEnergy(),1.0);
    EXPECT_LE(particleState->GetEnergy(),1.e6);
    EXPECT_EQ(particleState->GetWeight(),1.0);
    // clear the state
    particleState->Clear();
  }
}

// test the sampling from a single element source
TEST_F(RadSourceTest, FlukaParticleFunctionsH) {
  // source dist
  CSphericalElement *sph = new CSphericalElement(0,0,0,15,15,50,0);
  // make a new source
  CSource *source = new CSource(sph);
  std::string file = src_file;
  std::cout << file << std::endl;
  // read the spectra into the source from the file 
  source->AddSpectrum(new CSpectrum(file+"January2003H.dat",1),1.0);
  // make the random device
  std::random_device rd;
  // seed it
  std::mt19937_64 gen(12345);

  // get the particle information
  CParticleState* particleState = new CParticleState();
  // sample

  source->Sample(gen,particleState);
  EXPECT_EQ(particleState->GetParticleID(),1);
  EXPECT_GE(particleState->GetEnergy(),1.0);
  EXPECT_LE(particleState->GetEnergy(),1.e6);
  EXPECT_EQ(particleState->GetWeight(),1.0);
  EXPECT_EQ(particleState->GetFlukaParticleID(),1);
  EXPECT_EQ(particleState->GetChargeNumber(),1);
  EXPECT_EQ(particleState->GetNucleonNumber(),1);
  EXPECT_EQ(particleState->GetAtomicMass(),1.00782503223);
}

// test the sampling from a single element source
TEST_F(RadSourceTest, FlukaParticleFunctionsHe) {
  // source dist
  CSphericalElement *sph = new CSphericalElement(0,0,0,15,15,50,0);
  // make a new source
  CSource *source = new CSource(sph);
  std::string file = src_file;
  // read the spectra into the source from the file 
  std::cout << file << std::endl;
  source->AddSpectrum(new CSpectrum(file+"January2003He.dat",2),1.0);
  // make the random device
  std::random_device rd;
  // seed it
  std::mt19937_64 gen(12345);

  // get the particle information
  CParticleState* particleState = new CParticleState();
  // sample

  source->Sample(gen,particleState);
  EXPECT_EQ(particleState->GetParticleID(),2);
  EXPECT_GE(particleState->GetEnergy(),1.0);
  EXPECT_LE(particleState->GetEnergy(),1.e6);
  EXPECT_EQ(particleState->GetWeight(),1.0);
  EXPECT_EQ(particleState->GetFlukaParticleID(),-6);
  EXPECT_EQ(particleState->GetChargeNumber(),2);
  EXPECT_EQ(particleState->GetNucleonNumber(),4);
  EXPECT_DOUBLE_EQ(particleState->GetAtomicMass(),4.00260325413);
}

// test the sampling from a single element source
TEST_F(RadSourceTest, FlukaParticleFunctionsFe) {
  // source dist
  CSphericalElement *sph = new CSphericalElement(0,0,0,15,15,50,0);
  // make a new source
  CSource *source = new CSource(sph);
  std::string file = src_file;
  // read the spectra into the source from the file 
  std::cout << file << std::endl;
  source->AddSpectrum(new CSpectrum(file+"January2003Fe.dat",26),1.0);
  // make the random device
  std::random_device rd;
  // seed it
  std::mt19937_64 gen(12345);

  // get the particle information
  CParticleState* particleState = new CParticleState();
  // sample

  source->Sample(gen,particleState);
  EXPECT_EQ(particleState->GetParticleID(),26);
  EXPECT_GE(particleState->GetEnergy(),1.0);
  EXPECT_LE(particleState->GetEnergy(),1.e6);
  EXPECT_EQ(particleState->GetWeight(),1.0);
  EXPECT_EQ(particleState->GetFlukaParticleID(),-2);
  EXPECT_EQ(particleState->GetChargeNumber(),26);
  EXPECT_EQ(particleState->GetNucleonNumber(),56);
  EXPECT_DOUBLE_EQ(particleState->GetAtomicMass(),55.934936325999999);
  EXPECT_EQ(particleState->GetNucID(),260560000);

  std::map<int,int> counts;
  for ( int i = 0 ; i < 1000000 ; i++ ) {
    source->Sample(gen,particleState);
    if ( counts.count(particleState->GetNucID()) == 0 ) {
      counts[particleState->GetNucID()] = 1;
    } else {
      counts[particleState->GetNucID()] += 1;
    }
  }

  std::map<int,double> ref_results;

  ref_results[260540000] = 0.05845;
  ref_results[260560000] = 0.91754;
  ref_results[260570000] = 0.02119;
  ref_results[260580000] = 0.00282;
    
  std::map<int,int> :: iterator it;
  int sum = 0;
  for ( it = counts.begin() ; it != counts.end() ; ++it ) {
    EXPECT_NEAR(double(it->second)/double(1000000),ref_results[it->first],0.01);
  }
}
