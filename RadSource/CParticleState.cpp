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

// set the particle id
void CParticleState::SetParticleID(int iParticleID, double random) {
  // set the particle id - equivalent to the charge number
  m_iParticleID = iParticleID;

  pyne::comp_map comp;
  comp[m_iParticleID*10000000] = 1.0;

  pyne::Material mat = pyne::Material(comp);
  mat = mat.expand_elements();
  nucid = mat.sampler(random,"atom");
  charge = pyne::nucname::znum(nucid);
  nucleon_number = pyne::nucname::anum(nucid);
  atomic_mass = pyne::atomic_mass(nucid);
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
  if(nucid == 10010000)
    return 1;
  if(nucid == 10020000)
    return -3;
  if(nucid == 10030000)
    return -4;
  if(nucid == 20030000)
    return -5;
  if(nucid == 20040000)
    return -6;
  // if we get to here then must be heavy ion
  return -2;
}

