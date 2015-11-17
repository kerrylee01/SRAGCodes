#include <cmath>
#include <iostream>
#include <CPoint3D.h>

CPoint3D::CPoint3D(const CPoint3D & rhs) :
  m_dX(rhs.m_dX), m_dY(rhs.m_dY), m_dZ(rhs.m_dZ) {}

CPoint3D::CPoint3D(double dX, double dY, double dZ) :
  m_dX(dX), m_dY(dY), m_dZ(dZ) {}

CPoint3D CPoint3D::operator+(const CPoint3D& rhs)
{
    return CPoint3D( m_dX + rhs.m_dX, m_dY + rhs.m_dY, m_dZ + rhs.m_dZ );
}

CPoint3D CPoint3D::operator-(const CPoint3D& rhs)
{
    return CPoint3D( m_dX - rhs.m_dX, m_dY - rhs.m_dY, m_dZ - rhs.m_dZ );
}

//
//overload the * operator as the dot product
//
double CPoint3D::operator*(const CPoint3D& rhs)
{
    return m_dX * rhs.m_dX + m_dY * rhs.m_dY + m_dZ * rhs.m_dZ;
}


void CPoint3D::Set(double dX, double dY, double dZ) 
{
  m_dX = dX;
  m_dY = dY;
  m_dZ = dZ;
}

void CPoint3D::Print()
{
  std::cout << m_dX << "  " << m_dY << "  " << m_dZ;
}

void CPoint3D::Normalize()
{
  double dLength = sqrt(m_dX * m_dX + m_dY * m_dY + m_dZ * m_dZ);
  m_dX = m_dX / dLength;
  m_dY = m_dY / dLength;
  m_dZ = ( m_dZ / std::abs(m_dZ) ) * sqrt(1.0 - (m_dX * m_dX + m_dY * m_dY));
}
