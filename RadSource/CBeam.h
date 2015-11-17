
#ifndef Header_CBeam
#define Header_CBeam

#include <CSpatial.h>

class CParticleState;

class CBeam : public CSpatial {
 public:
 CBeam() : CSpatial("Beam") { }
  virtual ~CBeam() {  }
  virtual void Print();
  virtual void Sample(CParticleState* p_ParticleState);

 private:

};

#endif
