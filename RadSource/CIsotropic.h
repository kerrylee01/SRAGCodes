
#ifndef Header_CIsotropic
#define Header_CIsotropic

#include <random>
#include <CSpatial.h>

class CIsotropic : public CSpatial {
 public:
  CIsotropic(double dRadius, bool bDirection = false, double dThetaLimit = 180.);
  virtual ~CIsotropic() { CSpatial::Delete(); }
  void Clear();
  virtual void Print();
  virtual void Sample(std::mt19937_64 &gen);

 private:
  double m_dRadius;
  double m_dThetaLimit;
  bool   m_bDirection;
};

#endif
