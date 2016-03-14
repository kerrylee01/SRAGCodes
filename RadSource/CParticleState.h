
#ifndef Header_CParticleState
#define Header_CParticleState

#include <pyne.h>

#include <CPoint3D.h>

class CParticleState {
 public:
  CParticleState();
  ~CParticleState() { Delete(); }
  void Clear();
  void Delete();
  void SetPosition(CPoint3D*);
  void SetPosition(double, double, double);
  void SetDirection(CPoint3D*);
  void SetDirection(double, double, double);
  void SetEnergy(double dEnergy) { m_dEnergy = dEnergy; }
  void SetWeight(double dWeight) { m_dWeight = dWeight; }
  void SetParticleID(int iParticleID) { m_iParticleID = iParticleID; }
  CPoint3D* GetPosition() { return m_p_Position; }
  CPoint3D* GetDirection() { return m_p_Direction; }
  double GetEnergy() { return m_dEnergy; }
  double GetWeight() { return m_dWeight; }
  int GetParticleID() { return m_iParticleID; }
  int GetFlukaParticleID();
  int GetNucleonNumber();
  int GetChargeNumber();

  void Print();

 private:
  CPoint3D* m_p_Position;
  CPoint3D* m_p_Direction;
  double m_dEnergy;
  double m_dWeight;
  int m_iParticleID;
 
};

#endif
