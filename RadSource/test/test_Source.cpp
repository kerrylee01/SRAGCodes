#include <gtest/gtest.h>

#include <cmath>
#include <cassert>

#include "Source.h"

extern std::string src_file;

//---------------------------------------------------------------------------//
// TEST FIXTURES
//---------------------------------------------------------------------------//
class SourceTest : public ::testing::Test
{
 protected:

  // initalize variables for each test
  virtual void SetUp() {
  }
};

//---------------------------------------------------------------------------//
// Test setup outcomes
TEST_F(SourceTest, SetUp) {
  double x=0.0;
  double y=0.0;
  double z=0.0;
  double x_w = 20.0;
  double y_w = 20.0;
  double rad = 500.0;
  double z_s = 0.0;
  int pid = 1;
  setup_source_(x,y,z,x_w,y_w,rad,z_s,pid);
}
//---------------------------------------------------------------------------//
// Test setup outcomes
TEST_F(SourceTest, Sample) {
  double x,y,z;
  double u,v,w;
  double e,wgt;
  int id,zz,aa;

  // randoms
  //std::vector<double> randoms={0.1,0.2,0.3,0.4,0.1,0.2,0.3,0.4};
  double randoms[10] = {0.1,0.2,0.3,0.4,0.1,0.2,0.3,0.4,0.4,0.4};
  int num_randoms = 10;
  sample_source_(randoms,num_randoms,x,y,z,u,v,w,e,wgt,id,zz,aa);
}
