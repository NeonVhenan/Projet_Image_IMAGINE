#include "image_ppm.h"

void usage(char * s){
  printf("Usage %s : ImgIn.ppm ImgOut.ppm\n", s);
}

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nTaille3;
  int nT, nT3;
  
  if (argc != 3){
      usage(argv[0]);
      exit(EXIT_FAILURE) ;
  }
   
  sscanf (argv[1],"%s",cNomImgLue);
  sscanf (argv[2],"%s",cNomImgEcrite);

  OCTET *ImgIn, *ImgOut;
   
  lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;
  nTaille3 = 3 * nTaille;
  
  nT = (nH + 4*N)*(nW+4*N);
  nT3 = nT * 3;
  allocation_tableau(ImgIn, OCTET, nTaille3);
  lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgOut, OCTET, nT3);


  for(int i = 0; i < 2*N; i++){
    for(int j = 0; j < 3*(nW+4*N); j+=3){
      ImgOut[i*3*(nW+4*N)+j] = 0;
      ImgOut[i*3*(nW+4*N)+j+1] = 0;
      ImgOut[i*3*(nW+4*N)+j+2] = 0;
    }
  }

  int k = 0;
  int l;
  for(int i = 2*N; i < 2*N+nH; i++){
    for(int j = 0; j < 3*(2*N); j+=3){
      ImgOut[i*3*(nW+4*N)+j] = 0;
      ImgOut[i*3*(nW+4*N)+j+1] = 0;
      ImgOut[i*3*(nW+4*N)+j+2] = 0;
    }
    l = 0;
    for(int j = 3*(2*N); j < 3*(nW+2*N); j+=3){
      ImgOut[i*3*(nW+4*N)+j] = ImgIn[k*3*nW+l];
      ImgOut[i*3*(nW+4*N)+j+1] = ImgIn[k*3*nW+l+1];
      ImgOut[i*3*(nW+4*N)+j+2] = ImgIn[k*3*nW+l+2];
      l+=3;
    }
    for(int j = 3*(nW+2*N); j < 3*(nW+4*N); j+=3){
      ImgOut[i*3*(nW+4*N)+j] = 0;
      ImgOut[i*3*(nW+4*N)+j+1] = 0;
      ImgOut[i*3*(nW+4*N)+j+2] = 0;
    }
    k++;
  }

  for(int i = nH+2*N; i < nH+4*N; i++){
    for(int j = 0; j < 3*(nW+2*N); j+=3){
      ImgOut[i*3*(nW+4*N)+j] = 0;
      ImgOut[i*3*(nW+4*N)+j+1] = 0;
      ImgOut[i*3*(nW+4*N)+j+2] = 0;
    }
  }
  
  for(int i = nH+2*N; i < nH+3*N; i++){
    for(int j = 3*(nW+2*N); j < 3*(nW+3*N); j+=3){
      ImgOut[i*3*(nW+4*N)+j] = 255;
      ImgOut[i*3*(nW+4*N)+j+1] = 255;
      ImgOut[i*3*(nW+4*N)+j+2] = 255;
    }
  }
  for(int i = nH+3*N; i < nH+4*N; i++){
    for(int j = 3*(nW+2*N); j < 3*(nW+3*N); j+=3){
      ImgOut[i*3*(nW+4*N)+j] = 0;
      ImgOut[i*3*(nW+4*N)+j+1] = 0;
      ImgOut[i*3*(nW+4*N)+j+2] = 0;
    }
  }

  for(int i = nH+2*N; i < nH+3*N; i++){
    for(int j = 3*(nW+3*N); j < 3*(nW+4*N); j+=3){
      ImgOut[i*3*(nW+4*N)+j] = 0;
      ImgOut[i*3*(nW+4*N)+j+1] = 0;
      ImgOut[i*3*(nW+4*N)+j+2] = 0;
    }
  }
  for(int i = nH+3*N; i < nH+4*N; i++){
    for(int j = 3*(nW+3*N); j < 3*(nW+4*N); j+=3){
      ImgOut[i*3*(nW+4*N)+j] = 255;
      ImgOut[i*3*(nW+4*N)+j+1] = 255;
      ImgOut[i*3*(nW+4*N)+j+2] = 255;
    }
  }
  
  

  ecrire_image_ppm(cNomImgEcrite, ImgOut, nH + 4*N, nW+4*N);
  free(ImgIn);
  return 1;
}
