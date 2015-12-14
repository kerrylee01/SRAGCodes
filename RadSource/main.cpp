
#include <iostream>
#include <vector>
#include <random>
#include <cstdlib>
#include <CParticleState.h>
#include <CRadEnvironment.h>
#include <CIsotropic.h>
#include <CBeam.h>

std::random_device rd;
std::mt19937_64 gen(rd());

void TestSpectrum()
{
  CSpectrum *spec = new CSpectrum("GCRSource/January2003/January2003H.dat",1);
  //spec->Print();
  spec->Randomize();
  //spec->Print();
  spec->ReSort();
  //spec->Print();
  spec->SetSampleLimits(10, 10000);
  CParticleState* p_ParticleState = new CParticleState();
  /*
  for (int n = 0; n < 100000; ++n) {
    //v_p_ParticleState.push_back(new CParticleState());
    spec->Sample(gen, p_ParticleState);
    //p_ParticleState->Print();
    std::cout<<p_ParticleState->GetParticleID()<<"  "<<p_ParticleState->GetEnergy()<<std::endl;
  }
  */
  spec->Draw(0);
  //std::cout << *spec << std::endl;
}

void TestSpectrum2()
{
  CIsotropic* p_Isotropic = new CIsotropic(1.0, false);
  CSource *source = new CSource(p_Isotropic);
  std::vector<int> v_iTemp;
  std::string path = "GCRSource/";
  source->AddBOM2014Spectra(path+="allflux.dat", v_iTemp);
  CSpectrum *spec = source->GetSpectrum(0);
  spec->SetSampleLimits(10, 10000);
  /*
  CParticleState* p_ParticleState = new CParticleState();
  for (int n = 0; n < 100000; ++n) {
    //v_p_ParticleState.push_back(new CParticleState());
    spec->Sample(gen, p_ParticleState);
    //p_ParticleState->Print();
    std::cout<<p_ParticleState->GetParticleID()<<"  "<<p_ParticleState->GetEnergy()<<std::endl;
  }
  */
  spec->Draw(0);
  //std::cout << *spec << std::endl;
}

void TestSource()
{
  //Create multiple CSpecrum class objects and Sample, dumping out
  //ParticleID and Energy of the ParticleState.  Put results into a TTree
  //and see how each spectrum compares to each of the input spectra, by
  //plotting histograms by ParticleID
  CIsotropic* p_Isotropic = new CIsotropic(10.0);
  CSource *source = new CSource(p_Isotropic);
  source->AddSpectrum(new CSpectrum("GCRSource/January2003/January2003H.dat",1),1.0);
  source->AddSpectrum(new CSpectrum("GCRSource/January2003/January2003He.dat",2),1.0);
  //source->Print();
  std::vector<CParticleState*> v_p_ParticleState;
  CParticleState* p_ParticleState = new CParticleState();
  int counters[2] = {0,0};
  for (int n = 0; n < 100; ++n) {
    //v_p_ParticleState.push_back(new CParticleState());
    //source->Sample(v_p_ParticleState.back());
    source->Sample(gen, p_ParticleState);
    //std::cout<<v_p_ParticleState.back()->GetParticleID()<<"  "<<v_p_ParticleState.back()->GetEnergy()<<std::endl;
    //if(v_p_ParticleState.back()->GetParticleID()==1) counters[0]++;
    //else if(v_p_ParticleState.back()->GetParticleID()==2) counters[1]++;
    if(p_ParticleState->GetParticleID()==1) counters[0]++;
    else if(p_ParticleState->GetParticleID()==2) counters[1]++;
  }
  std::cout<<counters[0]<<"  "<<counters[1]<<std::endl;
}

void TestGCRSource(int iNum)
{
  //Create a CSpectrum for each element and isotope using the abundances from
  //Badhwar-O'Niell model for January2003 GCR environment
  CIsotropic* p_Isotropic = new CIsotropic(1.0, false);
  CSource *source = new CSource(p_Isotropic);
  std::string path = "GCRSource/January2003/";
  path+="January2003"; 
  std::vector<std::string> Isotopes = {"H","He","Li","Be","B","C","N","O","F","Ne","Na","Mg","Al","Si","P","S","Cl","Ar","K","Ca","Sc","Ti","V","Cr","Mn","Fe","Co","Ni"};
  for(int i = 0; i < (int)(Isotopes.size()); i++)
    source->AddSpectrum(new CSpectrum(path+Isotopes[i]+".dat",i+1));
  
  CParticleState* p_ParticleState = new CParticleState();
  for (int n = 0; n < iNum; ++n) {
    source->Sample(gen, p_ParticleState);
    p_ParticleState->Print();
  }
}

void TestGCRSource2(int iNum)
{
  //Create a CSpectrum for each element and isotope using the abundances from
  //Badhwar-O'Niell model 2014 from BONUX output file GCR environment
  int a_iPartList[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28};
  //int a_iPartList[] = {1};
  std::vector<int> v_iPartList (a_iPartList, a_iPartList + sizeof(a_iPartList) / sizeof(int));
  //for(int i = 1; i <= 28; i++) 
  //v_iPartList.push_back(i);
  //CIsotropic* p_Isotropic = new CIsotropic(1.0, false);
  //CSource *source = new CSource(p_Isotropic);
  CSource *source = new CSource();
  std::string path = "GCRSource/";
  source->AddBOM2014Spectra(path+="allflux.dat", v_iPartList);
  
  CParticleState* p_ParticleState = new CParticleState();
  for (int n = 0; n < iNum; ++n) {
    source->Sample(gen, p_ParticleState);
    p_ParticleState->Print();
  }
}

void TestExternalRandom(int iNum)
{
  //Create a CSpectrum for each element and isotope using the abundances from
  //Badhwar-O'Niell model 2014 from BONUX output file GCR environment
  int a_iPartList[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28};
  //int a_iPartList[] = {1};
  std::vector<int> v_iPartList (a_iPartList, a_iPartList + sizeof(a_iPartList) / sizeof(int));
  //for(int i = 1; i <= 28; i++) 
  //v_iPartList.push_back(i);
  CIsotropic* p_Isotropic = new CIsotropic(1.0, false);
  CSource *source = new CSource(p_Isotropic);
  //CSource *source = new CSource();
  std::string path = "GCRSource/";
  source->AddBOM2014Spectra(path+="allflux.dat", v_iPartList);
  
  CParticleState* p_ParticleState = new CParticleState();
  std::vector<double> v_dRan;
  std::uniform_real_distribution<> real_dis(0,1);
  for (int n = 0; n < iNum; ++n) {
    for (int i = 0; i < 2; i++) v_dRan.push_back(real_dis(gen));
    source->Sample(v_dRan, p_ParticleState);
    p_ParticleState->Print();
    v_dRan.clear();
  }

}

void TestSPESource()
{ 

}

void TestTrappedSource()
{

}

void TestSpaceEnvironment()
{
  //Create a GCR Source, SPE Source, and a trapped radiation source
  
}

void TestIsotropicDistribution(int iNum)
{
  CIsotropic* p_Isotropic = new CIsotropic(10.0);
  for(int i = 0; i < iNum; i++) {
    p_Isotropic->Sample(gen);
    p_Isotropic->GetPosition()->Print();
    std::cout<<"  ";
    p_Isotropic->GetDirection()->Print();
    std::cout<<std::endl;
  }
}

int main()
{
  //TestSpectrum();
  //TestSpectrum2();
  //TestSource();
  //TestGCRSource(1000000);
  TestGCRSource2(10);
  //TestExternalRandom(10);
  //TestSpaceEnvironment();
  //TestIsotropicDistribution(10);
}



