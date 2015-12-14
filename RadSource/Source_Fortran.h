
#ifndef Header_Source_Fortran
#define Header_Source_Fortran

#include <CSource.h>

#ifdef __cplusplus
extern "C" {
#endif

  /* initialize the CSource object from FORTRAN */
  void sourceinit_();

  /* initialize the CSource object for BOM2014 from FORTRAN */
  void sourceinitbom2014_();

  /* Sample the CSource with internal random number generator */
  void sourcesample_(int* ParticleID, double* Energy, double* Weight);

  /* Sample the CSource object from FORTRAN using external random numbers */
  void sourcesampleran_(double* a_dRand, int* ParticleID, double* Energy, double* Weight);
  //void sourcesampleran_(int* ParticleID, double* Energy, double* Weight);
#ifdef __cplusplus
} // extern "C"
#endif

#endif

