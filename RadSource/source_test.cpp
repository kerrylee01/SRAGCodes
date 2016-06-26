#include "Source.h"
#include <iostream>
#include <stdlib.h>

int main(int argc, char* argv[]) {

  double x,y,z;
  x = 20.0;
  y = 0.0;
  z = 0.0;
  int a = 1;
  int b = 1;
  int err = 0;
  char* string = "SPHERE";
  int strlen = 6;

  double randoms[10];
  int num_randoms = 10;
  srand(12345);

  setup_source_(x,y,z,x,y,z,x,a,b,err,string,strlen);

  double u,v,w,e,wgt,am;
  int id,zz,nn;

  for ( int i = 0 ; i < 10000 ; i++ ) {
    for ( int j = 0 ; j < 10 ; j++ ) {
      randoms[j] = (double)rand()/RAND_MAX;
    }

    sample_source_(randoms,num_randoms,x,y,z,u,v,w,e,wgt,am,id,zz,nn);
    //    std::cout  << x << " " << y << " " << z << " " << 5*u << " " << 5*v << " " << 5*w << std::endl;

  }
 

  return 0;
}

