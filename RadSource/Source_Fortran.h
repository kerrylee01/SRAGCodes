
#ifndef Header_Source_Fortran
#define Header_Source_Fortran

#include <CSource.h>

#ifdef __cplusplus
extern "C" {
#endif


  /* initialize the CSource object from FORTRAN */
  void sourceinit_();

  /* Sample the CSource with internal random number generator */

  void sourcesample_(int* ParticleID, double* Energy, double* Weight);

  /* Sample the CSource object from FORTRAN using external random numbers */
  
  //double* sourcesampleran_(double* a_dRand);

#ifdef __cplusplus
} // extern "C"
#endif

#endif

