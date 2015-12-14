//Create isotropic distribution over the surface of a sphere of Radius m_dRadius
//
//Inputs
//int Direction= 0, 0 if you only want inwardly directed particles
//double thetlim = 0 (in degrees), limit of sphere surface in theta 

#include <iostream>
#include <cmath>
#include <CPoint3D.h>
#include <CIsotropic.h>

CIsotropic::CIsotropic(double dRadius, bool bDirection, double dThetaLimit) : CSpatial("Isotropic"), m_dRadius(dRadius), m_bDirection(bDirection) 
{
  if(dThetaLimit > 180.0) {
    std::cout<<" Theta Limit must be less than 180 degrees " << std::endl;
    return;
  } else 
    m_dThetaLimit = M_PI * dThetaLimit / 180.0;
}

void CIsotropic::Clear()
{
  m_dRadius = 0.0;
  m_bDirection = 0;
  m_dThetaLimit = 0.0;
  CSpatial::Clear();
}

void CIsotropic::Print()
{
  std::cout<<"This is CIsotropic::Print()"<<std::endl;
}

void CIsotropic::Sample(std::mt19937_64 &gen)
{
  std::uniform_real_distribution<> PosCosTheta_dis(std::cos(m_dThetaLimit), 1);
  std::uniform_real_distribution<> DirCosTheta_dis(-1, 1);
  std::uniform_real_distribution<> Phi_dis(0, 2 * M_PI);

  //
  //Create a random point on a sphere
  double dPhi, dCosTheta, dSinTheta;
  dPhi = Phi_dis(gen);
  dCosTheta = PosCosTheta_dis(gen);
  dSinTheta = sqrt( (1.0 - (dCosTheta * dCosTheta)) );
  m_p_Position->Set(m_dRadius * cos(dPhi) * dSinTheta,
	            m_dRadius * sin(dPhi) * dSinTheta,
	            m_dRadius * dCosTheta              );
  //
  //Create random direction cosines
  dPhi = Phi_dis(gen);
  dCosTheta = DirCosTheta_dis(gen);
  dSinTheta = sqrt( (1.0 - (dCosTheta * dCosTheta)) );
  m_p_Direction->Set(cos(dPhi) * dSinTheta,
	             sin(dPhi) * dSinTheta,
	             dCosTheta              );
  //
  //Check to see if the desire is for inward directed only
  //
  if( m_bDirection ){
    //if not inward make it so
    if(*m_p_Position * *m_p_Direction > 0) *m_p_Direction = -(*m_p_Direction);
  }
  
  /****************************************************************************
  //Now Translate and Rotate if needed
  //
  //To do this Rotation is a 3x3 matrix object so I will have to write a
  //rotation matrix object and overload all the operators properly
  //Translation is simply another Point3D. Again overloaded operators needed.
  //
  //Rotate
  p_Position = Rotation * p_Position;
  p_Direction = Rotation * p_Direction;
  //Translate
  p_Position += TransMSC;
  ****************************************************************************/
  //Might wish to implement particles moving toward the center of the sphere
  //which means set the diretion toward (0,0,0). No need to sample for 
  //direction cosines if this is the case.  Not sure one would ever use
  //this since it would produce all particles going through a point (infinite 
  // dose), but Vic had this option in the original spatial_gen.f routine.
 
}

bool CIsotropic::Sample(std::vector<double> v_dRan)
{
  //
  //This Distribution requires 4 random numbers
  //
    if(v_dRan.size() < 4) {
    std::cout << "In CIsotropic::Sample the provided random number vector does not contain enough elements to proceed." <<std::endl;
    return false;
  }

  double dRan[4];
  dRan[0] = 2 * M_PI * v_dRan[0];
  dRan[1] = (1 - std::cos(m_dThetaLimit)) * v_dRan[1] + std::cos(m_dThetaLimit);
  dRan[2] = 2 * M_PI * v_dRan[2];
  dRan[3] = 2 * v_dRan[3] - 1;
  //
  //Create a random point on a sphere
  double dPhi, dCosTheta, dSinTheta;
  dPhi = dRan[0];
  dCosTheta = dRan[1];
  dSinTheta = sqrt( (1.0 - (dCosTheta * dCosTheta)) );
  m_p_Position->Set(m_dRadius * cos(dPhi) * dSinTheta,
	            m_dRadius * sin(dPhi) * dSinTheta,
	            m_dRadius * dCosTheta              );
  //
  //Create random direction cosines
  dPhi = dRan[2];
  dCosTheta = dRan[3];
  dSinTheta = sqrt( (1.0 - (dCosTheta * dCosTheta)) );
  m_p_Direction->Set(cos(dPhi) * dSinTheta,
	             sin(dPhi) * dSinTheta,
	             dCosTheta              );
  //
  //Check to see if the desire is for inward directed only
  //
  if( m_bDirection ){
    //if not inward make it so
    if(*m_p_Position * *m_p_Direction > 0) *m_p_Direction = -(*m_p_Direction);
  }
  return true;
}
