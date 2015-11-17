#include <iostream>
#include <CPoint2D.h>

CPoint2D::CPoint2D(const CPoint2D & rhs) :
  m_dX(rhs.m_dX), m_dY(rhs.m_dY) {}

bool CPoint2D::operator<(const CPoint2D &p_Point2D) const
{
  return m_dX < p_Point2D.m_dX;
}

void CPoint2D::Set(double dX, double dY) 
{
  m_dX = dX;
  m_dY = dY;
}

void CPoint2D::Print()
{
  std::cout << m_dX << "  " << m_dY << std::endl;
}

std::ostream &operator<<( std::ostream &output, const CPoint2D &Point2D )
{
  return output << Point2D.m_dX  << "  " << Point2D.m_dY << std::endl;
}

std::istream &operator>>( std::istream &input, CPoint2D &Point2D )
{
  return input >> Point2D.m_dX >> Point2D.m_dY;
}
