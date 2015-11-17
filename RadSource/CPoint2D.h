
#ifndef Header_CPoint2D
#define Header_CPoint2D

class CPoint2D {
 public:
  CPoint2D(double dX = 0.0, double dY = 0.0) { Set(dX, dY); }
  CPoint2D(const CPoint2D &); //copy constructor
  ~CPoint2D() { }
  
  bool operator<(const CPoint2D &) const;
  void Print();
  void Set(double dX, double dY);
  double GetX() { return m_dX; }
  double GetY() { return m_dY; }
  friend std::ostream &operator<<( std::ostream &output, const CPoint2D &Point2D );
  friend std::istream &operator>>( std::istream &input, CPoint2D &Point2D );

 private:
  double m_dX;
  double m_dY;
};

#endif
