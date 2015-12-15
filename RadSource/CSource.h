
#ifndef Header_CSource
#define Header_CSource

#include <string>
#include <random>
#include <CSpectrum.h>
#include <CSpatial.h>

class CParticleState;
//class CSpatial;

class CSource {
 public:
  CSource(); //default constructor with no Spacial configuration
  CSource(CSpatial* p_Spatial);
  //CSource(std::string sSpatialType);
  ~CSource() { Delete(); }
  void Clear();
  void Delete();
  void AddSpectrum(CSpectrum* p_Spectrum, double dAbundance = 0.0);
  void AddBOM2014Spectra(std::string sSpecFile, std::vector<int> v_iPartList, double dAbundance = 0.0);
  CSpectrum* GetSpectrum(int i) { return m_v_p_Spectra.at(i); }
  std::vector<double> GetRelativeAbundances() { return m_v_dRelativeAbundances; }  
  void Print();
  void Sample(std::mt19937_64 &gen, CParticleState* p_ParticleState);
  void Sample(std::vector<double> v_dRan, CParticleState* p_ParticleState);
  void SetSpatial(CSpatial* p_Spatial) { m_p_Spatial = p_Spatial; } 
  
 private:
  std::vector<CSpectrum*> m_v_p_Spectra;
  std::vector<double> m_v_dRelativeAbundances;
  double m_dAbundanceSum;
  std::string m_sSpatialType;
  CSpatial* m_p_Spatial;
};

#endif
