#ifndef Header_CSphericalElement
#define Header_CSphericalElement

#include <random>
#include "CSpatial.h"

class CSphericalElement : public CSpatial {
  public:
  // full constructor
  CSphericalElement(double origin_x, double origin_y, double origin_z,
		    double x_width, double y_width, double radius, double z_shift);
  // empty constructor
  CSphericalElement();
  // destructor
 ~CSphericalElement();

  // set the origin of the sphere
  int set_origin(double origin_x, double origin_y, double origin_z);
  // set the target area
  int set_target(double x_width, double y_width);
  // set the sampling radius
  int set_radius(double radius, double z_shift);

  // clear the state of the class
  void Clear();

  // print the type of sampling
  void Print();

  // sample
  void Sample(std::mt19937_64 &gen);
  bool Sample(std::vector<double> v_dRan);

  // return a particle
  int sample_particle(double randoms[4],double &x, double &y, double &z,
		      double &u, double &v, double &w);

  // private member variables
  private:
   double x_origin;
   double y_origin;
   double z_origin;

   double target_x_width;
   double target_y_width;
   double source_radius;
   double vertical_shift;
};
#endif

/*
#ifdef __cplusplus
  extern "C" {
#endif

// setup function
void setup_(double *origin_x, double *origin_y, double *origin_z,
	    double *x_width, double *y_width, double *radius, double *z_shift);

// sample function
void sample_(double randoms[4], double *x, double *y, double *z,
	     double *u, double *v, double *w);

#ifdef __cplusplus
  }
#endif
*/
