
#ifndef Header_CRadEnvironment
#define Header_CRadEnvironment

#include <vector>
#include <random>
#include <CSource.h>

class CParticleState;

class CRadEnvironment {
 public:
  CRadEnvironment() { }
  ~CRadEnvironment() { Delete(); }
  void Clear();
  void Delete();
  void AddSource(CSource* p_Source, double dAbundance);
  CSource* GetSource(int iSource) { return m_v_p_Sources.at(iSource); }
  void Sample(std::mt19937_64 &gen, CParticleState* p_ParticleState);
  void Sample(std::vector<double> v_dRan, CParticleState* p_ParticleState);
 private:
  std::vector<CSource*> m_v_p_Sources;
  std::vector<double> m_v_dRelativeAbundances;
 
};

#endif
