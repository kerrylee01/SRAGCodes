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
  setup_source_(&x,&y,&z,&x_w,&y_w,&rad,&z_s,&pid);
}
//---------------------------------------------------------------------------//
// Test setup outcomes
TEST_F(SourceTest, Sample) {
  double x;
  double y;
  double z;
  double u;
  double v;
  double w;
  double e;
  double wgt;
  int id;
  int zz;
  int aa;
  sample_source_(&x,&y,&z,&u,&v,&w,&e,&wgt,&id,&zz,&aa);
}
