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
    std::string env = src_file+"/RadSource/GCRSource/";

    const char *gcr_env_var = env.c_str();
    const char *env_name ="GCR_SOURCE_PATH";
    std::cout << env_name << std::endl;
    std::cout << gcr_env_var << std::endl;
    int ec = setenv(env_name,gcr_env_var,1);

    double x=0.0;
    double y=0.0;
    double z=0.0;
    double x_w = 20.0;
    double y_w = 20.0;
    double rad = 500.0;
    double z_s = 0.0;
    int pid = 0;
    int spectrum_type = 0;
    int err = 0;
    setup_source_(x,y,z,x_w,y_w,rad,z_s,pid,spectrum_type,err);
  }
};

//---------------------------------------------------------------------------//
// Test setup outcomes
TEST_F(SourceTest, SetUpSource) {
}

//---------------------------------------------------------------------------//
// Test setup outcomes
TEST_F(SourceTest, Sample1) {
  double x,y,z;
  double u,v,w;
  double e,wgt;
  int id,zz,aa;
  double am;

  // randoms
  //std::vector<double> randoms={0.1,0.2,0.3,0.4,0.1,0.2,0.3,0.4};
  double randoms[10] = {0.1,0.2,0.3,0.4,0.1,0.2,0.3,0.4,0.4,0.4};
  int num_randoms = 10;
  sample_source_(randoms,num_randoms,x,y,z,u,v,w,e,wgt,am,id,zz,aa);
  EXPECT_NE(0.0,x);
  EXPECT_NE(0.0,y);
  EXPECT_NE(0.0,z);
  EXPECT_NE(0.0,u);
  EXPECT_NE(0.0,v);
  EXPECT_NE(0.0,w);
}

//---------------------------------------------------------------------------//
// Test setup outcomes
TEST_F(SourceTest, Sample2) {
  double x,y,z;
  double u,v,w;
  double e,wgt;
  int id,zz,aa;
  double am;

  // randoms
  //std::vector<double> randoms={0.1,0.2,0.3,0.4,0.1,0.2,0.3,0.4};
  double randoms[10] = {0.1,0.2,0.3,0.4,0.1,0.2,0.3,0.4,0.4,0.4};
  int num_randoms = 10;
  for ( int i = 0 ; i < 10 ; i++ ) {
   sample_source_(randoms,num_randoms,x,y,z,u,v,w,e,wgt,am,id,zz,aa);
   std::cout << x << " " << y << " " << z << std::endl;
   std::cout << u << " " << v << " " << w << std::endl;
   std::cout << e << " " << wgt << std::endl;
   std::cout << id << " " << zz << " " << aa << std::endl;
 }
}

//---------------------------------------------------------------------------//
// TEST FIXTURES
//---------------------------------------------------------------------------//
class BONSourceTest : public ::testing::Test
{
 protected:

  // initalize variables for each test
  virtual void SetUp() {
    std::string env = src_file+"/RadSource/GCRSource/";

    const char *gcr_env_var = env.c_str();
    const char *env_name ="GCR_SOURCE_PATH";
    std::cout << env_name << std::endl;
    std::cout << gcr_env_var << std::endl;
    int ec = setenv(env_name,gcr_env_var,1);

    double x=0.0;
    double y=0.0;
    double z=0.0;
    double x_w = 20.0;
    double y_w = 20.0;
    double rad = 500.0;
    double z_s = 0.0;
    int pid = 0;
    int spectrum_type = 1;
    int err = 0;
    setup_source_(x,y,z,x_w,y_w,rad,z_s,pid,spectrum_type,err);
  }
};

//---------------------------------------------------------------------------//
// Test setup outcomes
TEST_F(BONSourceTest, SetUpSource) {
}

//---------------------------------------------------------------------------//
// Test setup outcomes
TEST_F(BONSourceTest, Sample1) {
  double x,y,z;
  double u,v,w;
  double e,wgt;
  int id,zz,aa;
  double am;

  // randoms
  //std::vector<double> randoms={0.1,0.2,0.3,0.4,0.1,0.2,0.3,0.4};
  double randoms[10] = {0.1,0.2,0.3,0.4,0.1,0.2,0.3,0.4,0.4,0.4};
  int num_randoms = 10;
  sample_source_(randoms,num_randoms,x,y,z,u,v,w,e,wgt,am,id,zz,aa);
}

//---------------------------------------------------------------------------//
// Test setup outcomes
TEST_F(BONSourceTest, Sample2) {
  double x,y,z;
  double u,v,w;
  double e,wgt;
  int id,zz,aa;
  double am;

  // randoms
  //std::vector<double> randoms={0.1,0.2,0.3,0.4,0.1,0.2,0.3,0.4};
  double randoms[10] = {0.1,0.2,0.3,0.4,0.1,0.2,0.3,0.4,0.4,0.4};
  int num_randoms = 10;
  for ( int i = 0 ; i < 10 ; i++ ) {
   sample_source_(randoms,num_randoms,x,y,z,u,v,w,e,wgt,am,id,zz,aa);
   std::cout << x << " " << y << " " << z << std::endl;
   std::cout << u << " " << v << " " << w << std::endl;
   std::cout << e << " " << wgt << std::endl;
   std::cout << id << " " << zz << " " << aa << std::endl;
 }
}


//---------------------------------------------------------------------------//
// TEST FIXTURES
//---------------------------------------------------------------------------//
class BON2014SourceTest : public ::testing::Test
{
 protected:

  // initalize variables for each test
  virtual void SetUp() {
    std::string env = src_file+"/RadSource/GCRSource/";

    const char *gcr_env_var = env.c_str();
    const char *env_name ="GCR_SOURCE_PATH";
    std::cout << env_name << std::endl;
    std::cout << gcr_env_var << std::endl;
    int ec = setenv(env_name,gcr_env_var,1);

    double x=0.0;
    double y=0.0;
    double z=0.0;
    double x_w = 20.0;
    double y_w = 20.0;
    double rad = 500.0;
    double z_s = 0.0;
    int pid = 0;
    int spectrum_type = 2;
    int err = 0;
    setup_source_(x,y,z,x_w,y_w,rad,z_s,pid,spectrum_type,err);
  }
};

//---------------------------------------------------------------------------//
// Test setup outcomes
TEST_F(BON2014SourceTest, SetUpSource) {
}

//---------------------------------------------------------------------------//
// Test setup outcomes
TEST_F(BON2014SourceTest, Sample1) {
  double x,y,z;
  double u,v,w;
  double e,wgt;
  int id,zz,aa;
  double am;

  // randoms
  //std::vector<double> randoms={0.1,0.2,0.3,0.4,0.1,0.2,0.3,0.4};
  double randoms[10] = {0.1,0.2,0.3,0.4,0.1,0.2,0.3,0.4,0.4,0.4};
  int num_randoms = 10;
  sample_source_(randoms,num_randoms,x,y,z,u,v,w,e,wgt,am,id,zz,aa);
}

//---------------------------------------------------------------------------//
// Test setup outcomes
TEST_F(BON2014SourceTest, Sample2) {
  double x,y,z;
  double u,v,w;
  double e,wgt;
  int id,zz,aa;
  double am;

  // randoms
  //std::vector<double> randoms={0.1,0.2,0.3,0.4,0.1,0.2,0.3,0.4};
  double randoms[10] = {0.1,0.2,0.3,0.4,0.1,0.2,0.3,0.4,0.4,0.4};
  int num_randoms = 10;
  for ( int i = 0 ; i < 10 ; i++ ) {
   sample_source_(randoms,num_randoms,x,y,z,u,v,w,e,wgt,am,id,zz,aa);
   std::cout << x << " " << y << " " << z << std::endl;
   std::cout << u << " " << v << " " << w << std::endl;
   std::cout << e << " " << wgt << std::endl;
   std::cout << id << " " << zz << " " << aa << std::endl;
 }
}
