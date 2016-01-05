#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include <CParticleState.h>
#include <CRadEnvironment.h>
#include <CSphericalElement.hpp>
#include <CBeam.h>

#include <Source.h>

CSphericalElement *dist;
CSource *source;
CParticleState* state;
CPoint3D *point;
std::vector<std::string> Isotopes = {"H","He","Li","Be","B","C","N","O","F","Ne","Na","Mg","Al","Si","P","S","Cl","Ar","K","Ca","Sc","Ti","V","Cr","Mn","Fe","Co","Ni"};

// setup the source
void setup_source_(double *origin_x, double *origin_y, double *origin_z,
            double *x_width, double *y_width, double *radius,
            double *z_shift, int *ionid) {
  // make new spherical element class
  dist = new CSphericalElement(*origin_x, *origin_y, *origin_z,
                              *x_width, *y_width, *radius,
                              *z_shift);

  state = new CParticleState();

  // make a new source - attach the SphericalElement Source
  source = new CSource(dist);

  std::string path = "GCRSource/January2003/";
  path+="January2003";

  // add all particles
  if( ionid  <= 0 ) {
    for( int i = 0; i < (int)(Isotopes.size()); i++ )
      source->AddSpectrum(new CSpectrum(path+Isotopes[i]+".dat",i+1));
  } else {
  // add only the requested ion
      source->AddSpectrum(new CSpectrum(path+Isotopes[*ionid-1]+".dat",*ionid));
  }

  return;
}

// sample from the source
void sample_source_(double *xxx, double *yyy, double *zzz,
             double *uuu, double *vvv, double *www,
             double *energy, double *weight,
             int *ionID, int *charge, int *nucleon_num) {

  // randoms
  std::vector<double> randoms;
  source->Sample(randoms,state);
  // set the particle position
  point = state->GetPosition();
  *xxx = point->GetX();
  *yyy = point->GetY();
  *zzz = point->GetZ();
  // set the particle direction
  point = state->GetDirection();
  *uuu = point->GetX();
  *vvv = point->GetY();
  *www = point->GetZ();
  // set the energy and weight
  *energy = state->GetEnergy();
  *weight = state->GetWeight();
  // set the ion ids
  *ionID = state->GetFlukaParticleID();
  *charge = state->GetChargeNumber();
  *nucleon_num = state->GetNucleonNumber();
  return;

}
