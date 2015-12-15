
#ifndef Header_CBeam
#define Header_CBeam

#include <CSpatial.h>

class CBeam : public CSpatial {
 public:
 CBeam() : CSpatial("Beam") { }
  virtual ~CBeam() {  }
  virtual void Print();
  virtual void Sample(std::mt19937_64 &gen);
  virtual bool Sample(std::vector<double> v_dRandom);

 private:

};

#endif
