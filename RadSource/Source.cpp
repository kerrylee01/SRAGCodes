#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include <CParticleState.h>
#include <CRadEnvironment.h>
#include <CSphericalElement.hpp>
#include <CBeam.h>

#include <Source.h>

bool sample_vector;

// setup the rn generator
std::mt19937_64 gen;


CSphericalElement *dist;
CSource *source;
CParticleState* state;
CPoint3D *point;
std::vector<std::string> Isotopes = {"H","He","Li","Be","B","C","N","O","F",
                                     "Ne","Na","Mg","Al","Si","P","S","Cl",
                                     "Ar","K","Ca","Sc","Ti","V","Cr","Mn",
                                     "Fe","Co","Ni"};

std::vector<int> particle_id = {1,2,3,4,5,6,7,8,9,10,11,12,13,
                     14,15,16,17,18,19,20,21,22,23,
                     24,25,26,27,28};

// setup the source
void setup_source_(double &origin_x, double &origin_y, double &origin_z,
            double &x_width, double &y_width, double &radius,
            double &z_shift, int &ionid, int &spectrum_type) {

  int seed = 12345;
  gen.seed(seed);


  // make new spherical element class
  dist = new CSphericalElement(origin_x, origin_y, origin_z,
                              x_width, y_width, radius,
                              z_shift);

  state = new CParticleState();

  // make a new source - attach the SphericalElement Source
  source = new CSource(dist);

  std::string datapath;
  // get the environemnt for the source path
  if(const char *gcr_source_path = std::getenv("GCR_SOURCE_PATH")) {
    datapath = std::string(gcr_source_path);
  } else {
    std::cout << "GCR_SOURCE_PATH enviroment variable not set" << std::endl;
    exit(1);
  }

  std::string path = datapath;

  // add all particles
  if( ionid  <= 0 ) {
    for( int i = 0; i < (int)(Isotopes.size()); i++ ) {
        if(spectrum_type == 0 ) {
          path += "January2003/";
          // append the name of the file
          path += "January2003";
          source->AddSpectrum(new CSpectrum(path+Isotopes[i]+".dat",i+1));
        } else if ( spectrum_type == 1 ) {
          source->AddBOM2014Spectra(path+="allflux.dat", particle_id);
        } else if ( spectrum_type == 2 ) {
          source->AddBOM2014Spectra(path+="BON2014flux.dat", particle_id);
        } else {
          std::cout << "Invalid source number / ion combination" << std::endl;
        }
    }
  } else {
  // add only the requested ion
      if(spectrum_type == 0 ) {
        path += "January2003/";
        // append the name of the file
        path += "January2003";
        source->AddSpectrum(new CSpectrum(path+Isotopes[ionid-1]+".dat",ionid));
      } else {
        std::cout << "Invalid source number / ion combination" << std::endl;
      }
  }
  return;
}

// sample from the source
void sample_source_(double *randoms, int& num_randoms, double &xxx, double &yyy, double &zzz,
             double &uuu, double &vvv, double &www,
             double &energy, double &weight,
             int &ionID, int &charge, int &nucleon_num) {

  // randoms
  std::vector<double> randoms_v(randoms, randoms + num_randoms );

  sample_vector = false;
  if(sample_vector) {
    source->Sample(randoms_v,state);
  } else {
    source->Sample(gen,state);
  }
  // set the particle position
  point = state->GetPosition();
  xxx = point->GetX();
  yyy = point->GetY();
  zzz = point->GetZ();
  // set the particle direction
  point = state->GetDirection();
  uuu = point->GetX();
  vvv = point->GetY();
  www = point->GetZ();
  // set the energy and weight
  energy = state->GetEnergy();
  weight = state->GetWeight();
  // set the ion ids
  ionID = state->GetFlukaParticleID();
  charge = state->GetChargeNumber();
  nucleon_num = state->GetNucleonNumber();
  return;

}
