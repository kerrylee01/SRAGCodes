#include <Source_Fortran.h>

#include <CParticleState.h>

#include <iostream>
#include <string>
#include <vector>
#include <random>

//globals

CSource *Source = new CSource();
//std::random_device rd;
//std::mt19937_64 gen(rd());


void sourceinit_()
{
  //Create a CSpectrum for each element and isotope using the abundances from
  //Badhwar-O'Niell model for January2003 GCR environment
  //Source = new CSource();
  std::string sPath = "GCRSource/January2003/";
  sPath+="January2003"; 
  std::vector<std::string> v_sIsotopes = {"H","He","Li","Be","B","C","N","O","F","Ne","Na","Mg","Al","Si","P","S","Cl","Ar","K","Ca","Sc","Ti","V","Cr","Mn","Fe","Co","Ni"};
  for(int i = 0; i < (int)(v_sIsotopes.size()); i++) {
    Source->AddSpectrum(new CSpectrum(sPath+v_sIsotopes[i]+".dat",i+1));
    //    std::cout<<Source->GetSpectrum(i)->GetAbundance()<<std::endl;
  }
}

void sourcesample_(int* ParticleID, double* Energy, double* Weight)
{
  std::random_device rd;
  std::mt19937_64 gen(rd());
  //double a_dSpecSample[3]; //ParticleID, Energy, Weight
  //Source->SpecSampleExRand(ExRandom);
  CParticleState* p_ParticleState = new CParticleState();
  Source->Sample(gen, p_ParticleState);
  
  *ParticleID = p_ParticleState->GetParticleID();
  *Energy = p_ParticleState->GetEnergy();
  *Weight = p_ParticleState->GetWeight();
  /*
  *ParticleID = 1;
  *Energy = 100.1;
  *Weight = 1.0;
  */
  
}
