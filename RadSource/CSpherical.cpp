#include <iostream>
#include <cmath>

#include "CPoint3D.h"
#include "CSpherical.hpp"

CSpherical::CSpherical(double radius) : CSpatial("Spherical") {
  x_origin = 0.0;
  y_origin = 0.0;
  z_origin = 0.0;

  source_radius = radius;
}

CSpherical::CSpherical() : CSpatial("Spherical") {
}

CSpherical::~CSpherical() {
}

int CSpherical::set_origin(double origin_x, double origin_y, double origin_z) {
  x_origin = origin_x;
  y_origin = origin_y;
  z_origin = origin_z;
  return 0;
}


int CSpherical::set_radius(double radius) {
  source_radius = radius;
  return 0;
}

void CSpherical::Print() {
  std::cout << "Awesome sauce" << std::endl;
}

void CSpherical::Sample(std::mt19937_64 &gen) {
  double x,y,z;
  double u,v,w;

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

bool CSpherical::Sample(std::vector<double> random_v) {
  double x,y,z;
  double u,v,w;


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

int CSpherical::sample_particle(double randoms[4], double &x, double &y,
				double &z, double &u, double &v, double &w) {


  // now pick a random direction above
  double phi = 2.*M_PI*randoms[0];
  double theta = std::acos((2.*randoms[1]) - 1.0);

  //  std::cout << phi << " " << theta << std::endl;
  // source position on sphere
  x = source_radius*std::cos(theta)*std::sin(phi);
  y = source_radius*std::sin(theta)*std::sin(phi);
  z = source_radius*std::cos(phi);
  
  // get uvw
  double dir_u = x_origin - x;
  double dir_v = y_origin - y;
  double dir_w = z_origin - z;


  // normalize vector
  double length = std::sqrt(std::pow(dir_u,2) + std::pow(dir_v,2) + std::pow(dir_w,2));
  
  // make sure uvw points towards uvw and is normalised     	    
  dir_u /= length;
  dir_v /= length;
  dir_w /= length;


  // now pick a random u,v,w that lies in within 2pi sr of the direction
  // now pick a random direction above
  phi = 2.*M_PI*randoms[2];
  theta = std::acos(2.*randoms[3] - 1.0);

  // source position on sphere
  u = std::cos(theta)*std::sin(phi);
  v = std::sin(theta)*std::sin(phi);
  w = std::cos(phi);

  // get dot product
  // uvw and dir_u,dir_v and dir_w are unit vectors

  // dot product of dir1 and dir2
  double vec_dir = (u*dir_u) + (v*dir_v) + (w*dir_w);

  // cos theta of angle between them
  double dir = vec_dir/1.0;
  
  // if cos theta -ve, reverse uvw
  if ( dir <= 0 ) {
    u *= -1.;
    v *= -1.;
    w *= -1.;
  }
  // all done
  return 0;
}
