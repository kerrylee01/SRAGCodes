
#include <CSpatial.h>

CSpatial::CSpatial(std::string sSpatialType) :  m_sSpatialType(sSpatialType)
{ 
  m_p_Position = new CPoint3D();
  m_p_Direction = new CPoint3D();
}

void CSpatial::Clear()
{
  m_p_Position->Set(0, 0, 0);
  m_p_Direction->Set(0, 0, 0);
}

void CSpatial::Delete()
{
  delete m_p_Position; 
  delete m_p_Direction;
}

/*
void CSpatial::Print()
{

}
*/

