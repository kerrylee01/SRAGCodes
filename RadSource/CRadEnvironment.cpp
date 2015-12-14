
#include <iostream>
#include <CRadEnvironment.h>
#include <CParticleState.h>


//CRadEnvironment::CRadEnvironment() { }

void CRadEnvironment::Clear() 
{ 
  m_v_dRelativeAbundances.clear();
  Delete();
}

void CRadEnvironment::Delete()
{
  while(!m_v_p_Sources.empty()) {
    CSource* p_Source = m_v_p_Sources.back();
    m_v_p_Sources.pop_back();
    delete p_Source;
  }
}

void CRadEnvironment::AddSource(CSource* p_Source, double dAbundance = 1.0) 
{ 
    m_v_p_Sources.push_back(p_Source);
    //m_v_dAbundances.push_back(dAbundance);
    m_v_dRelativeAbundances.push_back(m_v_dRelativeAbundances.back() + dAbundance);
}

void CRadEnvironment::Sample(std::mt19937_64 &gen, CParticleState* p_ParticleState)
{ 
  std::vector<double>::iterator iter_low;
  std::uniform_real_distribution<> real_dis(0, m_v_dRelativeAbundances.back());
  iter_low = std::lower_bound(m_v_dRelativeAbundances.begin(), m_v_dRelativeAbundances.end(), real_dis(gen) );
  m_v_p_Sources[iter_low - m_v_dRelativeAbundances.begin() - 1]->Sample(gen, p_ParticleState);

}

void CRadEnvironment::Sample(std::vector<double> v_dRan, CParticleState* p_ParticleState)
{
  if(v_dRan.size() < 1) {
    std::cout << "In CRadEnvironment::Sample the provided random number vector does not contain enough elements to proceed." <<std::endl;
    return;
  }
  
  std::vector<double>::iterator iter_low;
  double dRandom = m_v_dRelativeAbundances.back() * v_dRan[0];
  iter_low = std::lower_bound(m_v_dRelativeAbundances.begin(), m_v_dRelativeAbundances.end(), );
  std::vector<double> v_dRandom(v_dRan.begin() + 1, v_dRan.end());
  m_v_p_Sources[iter_low - m_v_dRelativeAbundances.begin() - 1]->Sample(v_dRandom, p_ParticleState);

}

