#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <CSpectrum.h>
#include <CParticleState.h>

bool CSpectrum::Sort(CPoint2D* p_Point1, CPoint2D* p_Point2)
{
  return p_Point1->GetX() < p_Point2->GetX();
}

//
//Potential Constructor to deal with various flux units.  For now lets
//assume all flux units are the same and there is not a need for this
//
//CSpectrum::CSpectrum(std::string sSpecFile, std::string sFluxUnits)

CSpectrum::CSpectrum(std::string sSpecFile, int iParticleID)
{
  m_dAbundance = 0.0;
  m_iParticleID = iParticleID;
  std::cout << sSpecFile.c_str() << std::endl;
  std::ifstream *ifSpecFile = new std::ifstream(sSpecFile.c_str());
  double dEnergy, dFlux, dSumFlux = 0.0;
  if( !(ifSpecFile->good()) ) { 
    std::cout<<"Error opening file "<<sSpecFile<<std::endl;
    return;
  }
  while( !(ifSpecFile->eof()) ) {
    *ifSpecFile>>dEnergy>>dFlux;
    if( !(ifSpecFile->good()) ) break;
    AddPoint(dEnergy, dFlux);
    dSumFlux+=dFlux;
    m_v_dFluxes.push_back(dSumFlux);
  }
  CSpectrum::Set();
}

CSpectrum::CSpectrum(std::vector<double> v_dEnergy, std::vector<double> v_dFlux, int iParticleID)
{
  m_dAbundance = 0.0;
  m_iParticleID = iParticleID;
  double dSumFlux = 0.0;
  for ( unsigned int i = 0; i < v_dEnergy.size(); i++  ) {
    AddPoint(v_dEnergy[i], v_dFlux[i]);
    dSumFlux+=v_dFlux[i];
    m_v_dFluxes.push_back(dSumFlux);
  }
  CSpectrum::Set();  
}

double CSpectrum::GetFlux(double dEnergy) 
{
  std::cout<< "Function CSpectrum::GetFlux not yet implemented" <<std::endl;
  
  return 0;
}

void CSpectrum::Clear() 
{
  m_dAbundance = 0.0;
  m_v_dFluxes.clear();
  Delete();
  std::cout<<"Particle Type is "<<m_iParticleID<<std::endl;
}

void CSpectrum::Delete()
{
  while(!m_v_p_Point2D.empty()) {
    CPoint2D* p_Point2D = m_v_p_Point2D.back();
    m_v_p_Point2D.pop_back();
    delete p_Point2D;
  }
}

void CSpectrum::Draw(bool bDelete)
{
  int iErr;
  std::ofstream ofOut("test.txt");
  ofOut << *this;
  iErr = system("root DrawTest.C'(\"test.txt\")'");
  if(bDelete) iErr = system("rm -f test.txt");
}

void CSpectrum::InterpolateLog()
{
  /*
  //std::vector<CPoint2D*>::iterator iter_energy_low;
   for(auto iter_energy_low = m_v_p_Point2D.begin(); iter_energy_low < m_v_p_Point2D.end(); iter_energy_low++ ) 
    if((*iter_energy_low)->GetX() > dRan) break;
  p_ParticleState->SetEnergy(m_v_p_Point2D[iter_energy_low - m_v_p_Point2D.begin() - 1]->GetX());
  */
}

void CSpectrum::Print()
{
  //std::vector<CPoint2D*>::iterator iter;
  for (auto iter = m_v_p_Point2D.begin(); iter != m_v_p_Point2D.end(); ++iter)
    (*iter)->Print();
}

void CSpectrum::Sample(std::mt19937_64 &gen, CParticleState* p_ParticleState)
{
  std::uniform_real_distribution<> real_dis1(0, 1);
  double ran1 = real_dis1(gen);
  double ran2 = real_dis1(gen);
  CSpectrum::DoSampling(ran1,ran2, p_ParticleState);
}

void CSpectrum::Sample(double dRan, double dRan2, CParticleState* p_ParticleState)
{
  double dRandom = (m_v_dFluxes[m_iUpperIndex] - m_v_dFluxes[m_iLowIndex]) * dRan + m_v_dFluxes[m_iLowIndex];
  CSpectrum::DoSampling(dRandom, dRan2, p_ParticleState);
}

void CSpectrum::DoSampling(double dRan, double dRan2, CParticleState* p_ParticleState)
{
  //std::cout<<"In CSpectrum::DoSampling()"<<std::endl;
  //***************************************************************************
  //There are two options for sampling that we want to support
  //  1) Flat in energy and then weighting the particles by flux/abundance
  //  2) analog which means sampling according to flux/abundance, weight = 1.0
  //***************************************************************************
  std::vector<double>::iterator iter_low;
  //
  //Select based on discrete flux CDF - analog discrete sampling
  //
  //*********************************************************************
  //analog sampling on defined grid
  //
  ////std::uniform_real_distribution<> real_dis(m_v_dFluxes[m_iLowIndex], m_v_dFluxes[m_iUpperIndex]);
  ////double dRan = real_dis(gen);
  iter_low = std::lower_bound(m_v_dFluxes.begin() + m_iLowIndex, 
			      m_v_dFluxes.begin() + m_iUpperIndex, dRan );
  p_ParticleState->SetEnergy(m_v_p_Point2D[iter_low - m_v_dFluxes.begin() - 1]->GetX());
  //p_ParticleState->SetWeight(1.0);
  
  //******************************************************************
  //analog sampling with interpolation
  //
  //Proper interpolation should be done with a natural cubic spline
  //I tested this using a ROOT TSpline3 function and it works well.  SRAG
  //could use their own Spline generating class for all interpolations
  //needed across fixed grids with piecewise continuous functions. Definitely
  //could be used in all HZETRN output grids like EffectiveDose code.
  //This Spectrum class should contain the CSpline object that holds all
  //the coefficients and evaluation function.  For now we stick with the 
  //linear interpolation in log space below.
  //  - Kerry Lee 8/31/2014
  //
  double x1, x2, y1, y2;
  int iIndex = iter_low - m_v_dFluxes.begin();
  x1 = m_v_p_Point2D[iIndex - 1]->GetX();
  x2 = m_v_p_Point2D[iIndex]->GetX();
  y1 = m_v_dFluxes[iIndex - 1];
  y2 = m_v_dFluxes[iIndex];
  x1 = log(x1);
  x2 = log(x2);
  y1 = log(y1);
  y2 = log(y2);
  p_ParticleState->SetEnergy(exp(((log(dRan) - y1) / (y2 - y1)) * (x2 - x1) + x1));
  p_ParticleState->SetWeight(1.0);
  //*******************************************************************
  //biased sampling in energy
  //
  //Needs additional testing, but initial look at results seems reasonable
  // - Kerry Lee 8/29/2014
  //
  /*
  std::uniform_real_distribution<> real_energy_dis(m_dLowerLimit, m_dUpperLimit);
  dRan = real_energy_dis(gen);
  std::vector<CPoint2D*>::iterator iter_energy_low;
  for(iter_energy_low = m_v_p_Point2D.begin() + m_iLowIndex; iter_energy_low < m_v_p_Point2D.begin() + m_iUpperIndex; iter_energy_low++ ) 
    if((*iter_energy_low)->GetX() > dRan) break;
  x1 = m_v_p_Point2D[iter_energy_low - m_v_p_Point2D.begin() - 1]->GetX();
  x2 = m_v_p_Point2D[iter_energy_low - m_v_p_Point2D.begin()]->GetX();
  y1 = m_v_p_Point2D[iter_energy_low - m_v_p_Point2D.begin() - 1]->GetY();
  y2 = m_v_p_Point2D[iter_energy_low - m_v_p_Point2D.begin()]->GetY();
  //x1 = log(x1);
  //x2 = log(x2);
  //y1 = log(y1);
  //y2 = log(y2);
  p_ParticleState->SetEnergy(dRan);
  p_ParticleState->SetWeight((((dRan - x1) / (x2 - x1)) * (y2 - y1) + y1)/m_dAbundance);
  */
  //****************************************************************************
  
  p_ParticleState->SetParticleID(m_iParticleID,dRan2);
  //std::cout<<p_ParticleState->GetParticleID()<<"  "<<p_ParticleState->GetEnergy()<<" "<<p_ParticleState->GetWeight()<<std::endl;
}


void CSpectrum::Set() 
{
  std::sort(m_v_p_Point2D.begin(), m_v_p_Point2D.end(), CSpectrum::Sort);
  m_dLowerLimit = CSpectrum::GetEnergy(0);
  m_dUpperLimit = m_v_p_Point2D.back()->GetX();
  m_iLowIndex = 0;
  m_iUpperIndex = m_v_p_Point2D.size() - 1;
  //
  //Need to set abundance of spectrum according to total flux
  //if flux does not have energy integrated out already then one must integrate
  //else the below will work (possibly use sFluxUnits, see above)
  //
  m_dAbundance = m_v_dFluxes.back();
  //
  //otherwise will have to loop over and multiply by bin width.  Could likely
  //be done in loops in Constructors
  //
}

void CSpectrum::SetSampleLimits(double dLower, double dUpper)
{
  m_dLowerLimit = dLower;
  m_dUpperLimit = dUpper;
  auto iter = m_v_p_Point2D.begin();
  for(; iter < m_v_p_Point2D.end(); iter++ ) { 
    if((*iter)->GetX() > dLower) {
      m_iLowIndex = iter - m_v_p_Point2D.begin() - 1;
      break;
    }
  }
  for(; iter < m_v_p_Point2D.end(); iter++ ) {
    if((*iter)->GetX() >= dUpper) {
      m_iUpperIndex = iter - m_v_p_Point2D.begin() + 1;
      break;
    }
  }
}

void CSpectrum::ReSort()
{
  std::sort(m_v_p_Point2D.begin(), m_v_p_Point2D.end(), CSpectrum::Sort);
}

void CSpectrum::Randomize()
{
  std::random_shuffle(m_v_p_Point2D.begin(), m_v_p_Point2D.end());
}

std::ostream &operator<<( std::ostream &output, CSpectrum &S )
{
  //std::vector<CPoint2D*>::iterator iter;
  for (auto iter = (S.m_v_p_Point2D).begin(); iter != (S.m_v_p_Point2D).end(); ++iter)
    output << **iter;
  return output;
}
/*
std::istream &operator>>( std::istream &input, CSpectrum &S )
{
  return input >> S. >> S.;
}
*/
