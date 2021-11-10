#include "image_ppm.h"
#include <stdlib.h>

void usage(char * s){
  printf("Usage : %s ImageIn.pgm ImageOut.pgm\n", s);
}


int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;

  if (argc != 3){
      usage(argv[0]);
      exit(EXIT_FAILURE) ;
  }

  sscanf (argv[1],"%s",cNomImgLue);
  sscanf (argv[2],"%s",cNomImgEcrite);

  OCTET *ImgIn, *ImgOut;

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

  allocation_tableau(ImgOut, OCTET, nTaille);
  lire_image_pgm(cNomImgEcrite, ImgOut, nH * nW);

  float s = 0.0;
  float eqm = 0.0;
  for(int i = 0; i < nH; i++){
    for(int j = 0; j < nW; j++){
      eqm += pow((ImgIn[i*nW+j] - ImgOut[i*nW+j]), 2);
    }
  }
  s = 1.0 /(nW * nH) * eqm;
  eqm = s;
  s = 0.0;
  s = 10.0*log10f(pow(255,2)*1.0/eqm);
  printf("PSNR : %f\n", s);

  free(ImgIn);
  free(ImgOut);
  
  return 1;
}
