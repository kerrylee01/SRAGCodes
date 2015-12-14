#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <CSource.h>
#include <CParticleState.h>

/*
CSource::CSource(std::string sSpatialType)
{
  m_sSpatialType = sSpatialType;
  if (sSpatialType == "Isotropic") {
    //m_p_Spatial = new CIsotropic(10.0);
  }
  m_dAbundanceSum = 0.0;
  m_v_dRelativeAbundances.push_back(0.0);
}
*/

CSource::CSource()
{
  m_p_Spatial = 0x0;
  m_v_dRelativeAbundances.push_back(0.0); 
  m_dAbundanceSum = 0.0; 
}

CSource::CSource(CSpatial* p_Spatial) : m_p_Spatial(p_Spatial)
{
  m_v_dRelativeAbundances.push_back(0.0); 
  m_dAbundanceSum = 0.0; 
}

void CSource::AddSpectrum(CSpectrum* p_Spectrum, double dAbundance) 
{ 
  if(dAbundance < 1E-20) dAbundance = p_Spectrum->GetAbundance(); 
  m_v_dRelativeAbundances.push_back(m_v_dRelativeAbundances.back() + dAbundance);
  m_dAbundanceSum = m_v_dRelativeAbundances.back();
  m_v_p_Spectra.push_back(p_Spectrum);
  //*************************************************************************
  //May need to take care of different flux units here, but I think the
  //right thing to do is to pick a default and take care of it all within
  //CSpectrum constructor
  //
  //May have to worry about different energy limits of the different Spectra
  //that are added here. Need to think about the best way to do this.
  //*************************************************************************
  //m_v_dRelativeAbundances.push_back(m_v_dRelativeAbundances.back() + p_Spectrum->GetAbundance());
  /*
    for(unsigned int ui = 1; ui <= m_v_p_Spectra.size(); ui++) {
    m_v_dRelativeAbundances.push_back(m_v_dRelativeAbundances[ui - 1] + m_v_p_Spectra[ui - 1]->GetAbundance() / m_dAbundanceSum );
    }
  */
  
}

void CSource::AddBOM2014Spectra(std::string sSpecFile, std::vector<int> v_iPartList, double dAbundance)
{
  //
  //Read BOM2014 AllFlux data into vectors and add each Spectrum
  //
  std::vector<double> v_dTemp;
  std::vector<double> v_dEnergy;
  std::vector<std::vector<double> > v_dFlux;
  std::vector<int> v_iParticleID;
  std::ifstream ifSpecFile(sSpecFile.c_str());
  std::string sLine;
  std::stringstream ssStream;
  int iIndex;
  double dEnergy, dFlux, dSumFlux = 0.0;
  if( !(ifSpecFile.good()) ) { 
    //std::cout<<"Error opening file "<<ifSpecFile<<std::endl;
    std::cout<<"Error opening file "<<sSpecFile<<std::endl;
    return;
  }
  //
  //Read through the first data line to setup the 2-d vector
  //
  unsigned int uiColumn = 0;
  while( !(ifSpecFile.eof()) ) {
    getline(ifSpecFile, sLine);
    if( sLine[sLine.find_first_not_of(' ')] != '#') break;
  }
  ssStream.str(sLine);
  ssStream >> iIndex >> dEnergy;
  v_iParticleID.push_back(iIndex);
  v_dEnergy.push_back(dEnergy);
  while( !(ssStream.eof()) ) {
    ssStream >> dFlux;
    if( !(ssStream.good()) ) break;
    if(v_dFlux.size() <= uiColumn) 
      v_dFlux.push_back(v_dTemp);
    v_dFlux[uiColumn++].push_back(dFlux);
  }
  //
  //Read through the remaining lines and fill the vectors
  //
  while( !(ifSpecFile.eof()) ) {
    ssStream.str("");
    ssStream.clear();
    getline(ifSpecFile, sLine);
    if( !(ifSpecFile.good()) ) break;
    ssStream.str(sLine);
    ssStream >> iIndex >> dEnergy;
    v_iParticleID.push_back(iIndex);
    v_dEnergy.push_back(dEnergy);
    uiColumn = 0;
    while( !(ssStream.eof()) ) {
      ssStream >> dFlux;
      if( !(ssStream.good()) ) break;
      v_dFlux[uiColumn++].push_back(dFlux);
    }
  }
  /*
  std::vector<std::vector<double> >::iterator iter;
  for (iter = v_dFlux.begin(); iter != v_dFlux.end(); ++iter)
    AddSpectrum(new CSpectrum(v_dEnergy, *iter, v_iParticleID[i]), dAbundance);
  */
  for(unsigned int i = 0 ; i < v_dFlux.size(); i++)
    if (v_iPartList.size() == 0 || (std::find(v_iPartList.begin(), v_iPartList.end(), v_iParticleID[i]) != v_iPartList.end()) )
      AddSpectrum(new CSpectrum(v_dEnergy, v_dFlux[i], v_iParticleID[i]), dAbundance);
}

void CSource::Clear() 
{ 
  Delete();
  m_v_dRelativeAbundances.clear();
  m_dAbundanceSum = 0.0;
}

void CSource::Delete()
{
  while(!m_v_p_Spectra.empty()) {
    CSpectrum* p_Spectrum = m_v_p_Spectra.back();
    m_v_p_Spectra.pop_back();
    delete p_Spectrum;
  }
  delete m_p_Spatial;
}

void CSource::Sample(std::mt19937_64 &gen, CParticleState* p_ParticleState)
{
  //std::cout<<"In CSource::Sample(gen, CParticleState)"<<std::endl;
  std::vector<double>::iterator iter_low;
  std::uniform_real_distribution<> real_dis(0, m_v_dRelativeAbundances.back());
  iter_low = std::lower_bound(m_v_dRelativeAbundances.begin(), m_v_dRelativeAbundances.end(), real_dis(gen) );
  m_v_p_Spectra[iter_low - m_v_dRelativeAbundances.begin() - 1]->Sample(gen, p_ParticleState);
  //std::cout<<p_ParticleState->GetParticleID()<<"  "<<p_ParticleState->GetEnergy()<<" "<<p_ParticleState->GetWeight()<<std::endl;
  //
  //If biased run by weight take care of spectral weight here
  //
  //p_ParticleState->SetWeight(p_ParticleState->GetWeight()/m_dAbundanceSum);??
  //
  //
  //Now take care of spatial distribution:
  //
  if(m_p_Spatial != 0x0) {
    m_p_Spatial->Sample(gen);
    p_ParticleState->SetPosition(m_p_Spatial->GetPosition());
    p_ParticleState->SetDirection(m_p_Spatial->GetDirection());
  }
  //std::cout<<p_ParticleState->GetParticleID()<<"  "<<p_ParticleState->GetEnergy()<<" "<<p_ParticleState->GetWeight()<<std::endl;
}

void CSource::Sample(std::vector<double> v_dRan, CParticleState* p_ParticleState)
{
  if(v_dRan.size() < 2) {
    std::cout << "In CSource::Sample the provided random number vector does not contain enough elements to proceed." <<std::endl;
    return;
  }

  std::vector<double>::iterator iter_low;
  double dRandom = m_v_dRelativeAbundances.back() * v_dRan[0];
  iter_low = std::lower_bound(m_v_dRelativeAbundances.begin(), m_v_dRelativeAbundances.end(), dRandom );

  m_v_p_Spectra[iter_low - m_v_dRelativeAbundances.begin() - 1]->Sample(v_dRan[1], p_ParticleState);
  //
  //Now take care of spatial distribution:
  //
  std::vector<double> v_dRandom(v_dRan.begin() + 2, v_dRan.end());
  if(m_p_Spatial != 0x0) {
    if(m_p_Spatial->Sample(v_dRandom) == false) return;
    p_ParticleState->SetPosition(m_p_Spatial->GetPosition());
    p_ParticleState->SetDirection(m_p_Spatial->GetDirection());
  }
}

void CSource::Print()
{
  //std::vector<CSpectrum*>::iterator iter;
  for (auto iter = m_v_p_Spectra.begin(); iter != m_v_p_Spectra.end(); ++iter)
    (*iter)->Print();
}
