
#ifndef Header_CSpatial
#define Header_CSpatial

#include <string>
#include <vector>
#include <random>
#include <CPoint3D.h>

//class CPoint3D;

class CSpatial {
 public:
  CSpatial(std::string sSpatialType = "");
  virtual ~CSpatial() { Delete(); }
  void Clear();
  void Delete();
  std::string GetType() { return m_sSpatialType; }
  CPoint3D* GetPosition() { return m_p_Position; }
  CPoint3D* GetDirection() { return m_p_Direction; }
  virtual void Print() = 0;
  virtual void Sample(std::mt19937_64 &gen) = 0;
  virtual bool Sample(std::vector<double> v_dRandom) = 0;

 protected:
  CPoint3D* m_p_Position;
  CPoint3D* m_p_Direction;

 private:
  std::string m_sSpatialType;
};

#endif
