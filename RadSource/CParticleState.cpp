#include <iostream>
#include <CParticleState.h>

CParticleState::CParticleState()
{
  m_p_Position = new CPoint3D();
  m_p_Direction = new CPoint3D();
}

void CParticleState::Clear() 
{ 
  Delete();
  m_p_Position = new CPoint3D();
  m_p_Direction = new CPoint3D();
  m_dEnergy = 0.0;
  m_iParticleID = 0;
  m_dWeight = 1.0;
}

void CParticleState::Delete()
{
  delete m_p_Position; 
  delete m_p_Direction; 
}

void CParticleState::Print()
{
  std::cout << m_iParticleID << "  " << m_dEnergy << "  ";
  m_p_Position->Print();
  std::cout<<"  ";
  m_p_Direction->Print();
  std::cout<<"  "<<m_dWeight<<std::endl;
}

void CParticleState::SetPosition(CPoint3D* p_Point3D)
{
  m_p_Position = p_Point3D;
}

void CParticleState::SetPosition(double dX, double dY, double dZ)
{
  SetPosition(new CPoint3D(dX, dY, dZ));
}

void CParticleState::SetDirection(CPoint3D* p_Point3D)
{
  m_p_Direction = p_Point3D;
  m_p_Direction->Normalize();
}

void CParticleState::SetDirection(double dX, double dY, double dZ)
{
  SetDirection(new CPoint3D(dX, dY, dZ));
}

int CParticleState::GetFlukaParticleID() {
  if ( m_iParticleID == 1 ) {
    return 1;
  } else if ( m_iParticleID > 1 ) {
    return -2;
  }
}

// get the nucleon number
int CParticleState::GetNucleonNumber() {
  return 0;
}

// get the charge number
int CParticleState::GetChargeNumber() {
  return m_iParticleID;
}
