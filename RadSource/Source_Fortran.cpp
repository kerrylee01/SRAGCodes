#include <Source_Fortran.h>

#include <CParticleState.h>

#include <iostream>
#include <string>
#include <vector>
#include <random>

//globals
CSource *Source = new CSource();

void sourceinit_()
{
  //Create a CSpectrum for each element and isotope using the abundances from
  //Badhwar-O'Niell model for January2003 GCR environment
  std::string sPath = "GCRSource/January2003/";
  sPath+="January2003"; 
  std::vector<std::string> v_sIsotopes = {"H","He","Li","Be","B","C","N","O","F","Ne","Na","Mg","Al","Si","P","S","Cl","Ar","K","Ca","Sc","Ti","V","Cr","Mn","Fe","Co","Ni"};
  for(int i = 0; i < (int)(v_sIsotopes.size()); i++) {
    Source->AddSpectrum(new CSpectrum(sPath+v_sIsotopes[i]+".dat",i+1));
    //    std::cout<<Source->GetSpectrum(i)->GetAbundance()<<std::endl;
  }
}

void sourceinitbom2014_()
{
  //Create a CSpectrum for each element and isotope using the abundances from
  //Badhwar-O'Niell model 2014 from BONUX output file GCR environment
  int a_iPartList[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28};
  std::vector<int> v_iPartList (a_iPartList, a_iPartList + sizeof(a_iPartList) / sizeof(int));
  std::string path = "GCRSource/";
  Source->AddBOM2014Spectra(path+="allflux.dat", v_iPartList);
}

void sourcesample_(int* ParticleID, double* Energy, double* Weight)
{
  //std::cout<<"In soucesample_"<<std::endl;
  std::random_device rd;
  std::mt19937_64 gen(rd());
  CParticleState* p_ParticleState = new CParticleState();
  Source->Sample(gen, p_ParticleState);
  *ParticleID = p_ParticleState->GetParticleID();
  *Energy = p_ParticleState->GetEnergy();
  *Weight = p_ParticleState->GetWeight();
}

void sourcesampleran_(double* a_dRan, int* ParticleID, double* Energy, double* Weight)
{
  //std::cout<<"In soucesampleran_"<<std::endl; 
  std::vector<double> v_dRan;
  for(int i = 0; i < 6; i++) {
    //std::cout<<a_dRan[i]<<" ";
    v_dRan.push_back(a_dRan[i]);
  }
  //std::cout<<std::endl; 
  CParticleState* p_ParticleState = new CParticleState();
  Source->Sample(v_dRan, p_ParticleState); 
  *ParticleID = p_ParticleState->GetParticleID();
  *Energy = p_ParticleState->GetEnergy();
  *Weight = p_ParticleState->GetWeight();
}
