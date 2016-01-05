#include <iostream>
#include <cmath>

#include "CPoint3D.h"
#include "CSphericalElement.hpp"

/*
// sample class pointer
CSphericalElement *src;

// setup the source
void setup_(double *origin_x, double *origin_y, double *origin_z,
	   double *x_width, double *y_width, double *radius, double *z_shift) {
  // make new class
  src = new CSphericalElement(*origin_x, *origin_y, *origin_z,
			      *x_width, *y_width, *radius, *z_shift);
}

// sample from the source
void sample_(double randoms[4], double *x, double *y, double *z,
	    double *u, double *v, double *w) {
  int ec = src->sample_particle(randoms,*x,*y,*z,*u,*v,*w);

}

*/


CSphericalElement::CSphericalElement(double origin_x, double origin_y, double origin_z,
				     double x_width, double y_width, double radius, double z_shift)
                                     : CSpatial("SphericalElement") {
  x_origin = origin_x;
  y_origin = origin_y;
  z_origin = origin_z;

  target_x_width = x_width;
  target_y_width = y_width;

  source_radius = radius;
  vertical_shift = z_shift;
}

CSphericalElement::CSphericalElement() {
}

CSphericalElement::~CSphericalElement() {
}

int CSphericalElement::set_origin(double origin_x, double origin_y, double origin_z) {
  x_origin = origin_x;
  y_origin = origin_y;
  z_origin = origin_z;
  return 0;
}

int CSphericalElement::set_target(double x_width, double y_width) {
  target_x_width = x_width;
  target_y_width = y_width;
  return 0;
}

int CSphericalElement::set_radius(double radius, double z_shift) {
  source_radius = radius;
  vertical_shift = z_shift;
  return 0;
}

void CSphericalElement::Print() {
  std::cout << "Awesome sauce" << std::endl;
}

void CSphericalElement::Sample(std::mt19937_64 &gen) {
  double x,y,z;
  double u,v,w;
  // s

  double random_array[4];

  std::uniform_real_distribution<> real_dis(0,1.0);

  random_array[0] = real_dis(gen);
  random_array[1] = real_dis(gen);
  random_array[2] = real_dis(gen);
  random_array[3] = real_dis(gen);

  int rval = sample_particle(random_array, x,y,z, u,v,w );
  m_p_Position->Set(x,y,z);
  m_p_Direction->Set(u,v,w);
}

bool CSphericalElement::Sample(std::vector<double> random_v) {
  double x,y,z;
  double u,v,w;
  // s

  // make sure that the array is the right size
  if( random_v.size() != 4 ) return false;

  double *random_array;
  random_array = new double[random_v.size()];
  std::copy(random_v.begin(),random_v.end(),random_array);
  int rval = sample_particle(random_array, x,y,z, u,v,w );
  m_p_Position->Set(x,y,z);
  m_p_Direction->Set(u,v,w);
  return true;
}

int CSphericalElement::sample_particle(double randoms[4], double &x, double &y,
				       double &z, double &u, double &v, double &w) {
  // generates x and y distributed from -target/2 to +target/2
  double rand_x = target_x_width*(randoms[0]-0.5);
  double rand_y = target_y_width*(randoms[1]-0.5);
  // z is constant
  double rand_z = z_origin;

  // now pick a random direction above
  double phi_angle = 2.*M_PI*randoms[2];
  double cosphi = std::cos(phi_angle);
  double sinphi = std::sin(phi_angle);

  // pick a point on the sphere such that the z value is above
  // the origin
  double mintheta = std::acos(z_origin/(source_radius-vertical_shift));

  double theta_angle = (mintheta)*randoms[3];
  double costheta = std::cos(theta_angle);
  double sintheta = std::sin(theta_angle);

  // x is point on the sphere but with z greater than z_origin
  x = source_radius*sintheta*cosphi;
  y = source_radius*sintheta*sinphi;
  z = source_radius*costheta - vertical_shift;

  // trace this ray back to the sphere origin
  double distance = std::sqrt(std::pow(x-rand_x,2) + std::pow(y-rand_y,2)
			      + std::pow(z-rand_z,2));

  u = (rand_x - x)/distance;
  v = (rand_y - y)/distance;
  w = (rand_z - z)/distance;

  return 0;
}
