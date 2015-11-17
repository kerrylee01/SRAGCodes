
#ifndef Header_CPoint3D
#define Header_CPoint3D

class CPoint3D {
 public:
  CPoint3D(double dX = 0.0, double dY = 0.0, double dZ = 0.0);
  CPoint3D(const CPoint3D &); //copy constructor
  ~CPoint3D() { }
  inline CPoint3D & operator = (const CPoint3D &); //assignment operator
  inline CPoint3D operator - () const; //Unary minus operator
  CPoint3D operator+(const CPoint3D& rhs);
  CPoint3D operator-(const CPoint3D& rhs);
  double operator*(const CPoint3D& rhs); //dot product operator
  inline double Dot(const CPoint3D &) const; //Dot Product function
  inline CPoint3D Cross(const CPoint3D &) const; //Cross Product function

  void Normalize();
  void Print();
  void Set(double dX, double dY, double dZ);
  double GetX() { return m_dX; }
  double GetY() { return m_dY; }
  double GetZ() { return m_dZ; }
  void SetX(double dX) { m_dX = dX; }
  void SetY(double dY) { m_dY = dY; }
  void SetZ(double dZ) { m_dZ = dZ; }

 private:
  double m_dX;
  double m_dY;
  double m_dZ;
};

inline CPoint3D & CPoint3D::operator = (const CPoint3D & rhs) 
{
   m_dX = rhs.m_dX;
   m_dY = rhs.m_dY;
   m_dZ = rhs.m_dZ;
   return *this;
}

inline CPoint3D CPoint3D::operator - () const
{
  return CPoint3D(-m_dX, -m_dY, -m_dZ);
}

inline double CPoint3D::Dot(const CPoint3D & rhs) const 
{
  return m_dX * rhs.m_dX + m_dY * rhs.m_dY + m_dZ * rhs.m_dZ;
}

inline CPoint3D CPoint3D::Cross(const CPoint3D & rhs) const 
{
  return CPoint3D(m_dY * rhs.m_dZ - rhs.m_dY * m_dZ,
		  m_dZ * rhs.m_dX - rhs.m_dZ * m_dX,
		  m_dX * rhs.m_dY - rhs.m_dX * m_dY );
}

#endif
