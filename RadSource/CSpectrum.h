//Tests to do
//1) Test that Randomize keeps X and Y values together - Done
//2) Test that Randomize maintains all elements - Done
//3) Test that ReSort returns exactly the original sorted list after Randomizing it - Done
//4) Test that Sample produces the spectrum that is being sampled in analog mode
//5) Test that Sample produces a flat sampling in weighted mode


#ifndef Header_CSpectrum
#define Header_CSpectrum

#include <vector>
#include <string>
#include <random>
#include <CPoint2D.h>

class CParticleState; 

class CSpectrum {
 public:
  CSpectrum() { m_dAbundance = 0.0; }
  CSpectrum(std::string sFile, int iParticleID);
  CSpectrum(std::vector<double> v_dEnergy, std::vector<double> v_dFlux, int iParticleID);
  //CSpectrum(double dLowEnergy, double dHighEnergy, std::string sDistribution);
  ~CSpectrum() { Delete(); }
  void Clear();
  void Delete();
  void AddPoint(double dX, double dY) { 
    m_v_p_Point2D.push_back(new CPoint2D(dX, dY));
  }
  void Draw(bool bDelete = true); //Draw in ROOT
  double GetAbundance() { return m_dAbundance; }
  double GetEnergy(int iPoint) { return m_v_p_Point2D.at(iPoint)->GetX(); }
  double GetFlux(int iPoint) { return m_v_p_Point2D.at(iPoint)->GetY(); }
  double GetFlux(double dEnergy);
  double GetLowerSampleLimit() { return m_dLowerLimit; }
  double GetUpperSampleLimit() { return m_dUpperLimit; }
  
  void InterpolateLog();
  //void InterpolateLin();
  void Print();
  void Sample(std::mt19937_64 &gen, CParticleState* p_ParticleState);
  void Sample(double dRan, double dRan1, CParticleState* p_ParticleState);
  void DoSampling(double dRan1, double dRan2, CParticleState* p_ParticleState);
  void Set();
  void SetAbundance(double dAbundance) { m_dAbundance = dAbundance; }
  void SetSampleLimits(double dLower, double dUpper);
  static bool Sort(CPoint2D*, CPoint2D*);
  void ReSort();
  void Randomize();
  friend std::ostream &operator<<( std::ostream &output, CSpectrum &S );
  //friend std::istream &operator>>( std::istream &input, CSpectrum &S );

 private:
  std::vector<CPoint2D*> m_v_p_Point2D;
  double m_dAbundance;
  std::vector<double> m_v_dFluxes; //holds the discrete values of the CDF
  int m_iParticleID;
  double m_dUpperLimit; //Sampling upper limit
  double m_dLowerLimit; //Sampling lower limit
  int m_iLowIndex;
  int m_iUpperIndex;
  
};

#endif
