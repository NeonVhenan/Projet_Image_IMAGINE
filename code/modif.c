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
  
  nT = (nH + 20*N)*(nW+20*N);
  nT3 = nT * 3;
  allocation_tableau(ImgIn, OCTET, nTaille3);
  lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgOut, OCTET, nT3);


  for(int i = 0; i < 10*N; i++){
    for(int j = 0; j < 3*(nW+20*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }

  int k = 0;
  int l;
  for(int i = 10*N; i < 10*N+nH; i++){
    for(int j = 0; j < 3*(10*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
    l = 0;
    for(int j = 3*(10*N); j < 3*(nW+10*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = ImgIn[k*3*nW+l];
      ImgOut[i*3*(nW+20*N)+j+1] = ImgIn[k*3*nW+l+1];
      ImgOut[i*3*(nW+20*N)+j+2] = ImgIn[k*3*nW+l+2];
      l+=3;
    }
    for(int j = 3*(nW+10*N); j < 3*(nW+20*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
    k++;
  }

  for(int i = nH+10*N; i < nH+20*N; i++){
    for(int j = 0; j < 3*(nW+10*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }

  for(int i = nH+10*N; i < nH+11*N; i++){
    for(int j = 3*(nW+10*N); j < 3*(nW+20*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  //ligne 11-12
  for(int i = nH+11*N; i < nH+12*N; i++){
    for(int j = 3*(nW+10*N); j < 3*(nW+11*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+11*N; i < nH+12*N; i++){
    for(int j = 3*(nW+11*N); j < 3*(nW+12*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+11*N; i < nH+12*N; i++){
    for(int j = 3*(nW+12*N); j < 3*(nW+13*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+11*N; i < nH+12*N; i++){
    for(int j = 3*(nW+13*N); j < 3*(nW+14*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+11*N; i < nH+12*N; i++){
    for(int j = 3*(nW+14*N); j < 3*(nW+15*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+11*N; i < nH+12*N; i++){
    for(int j = 3*(nW+15*N); j < 3*(nW+16*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+11*N; i < nH+12*N; i++){
    for(int j = 3*(nW+16*N); j < 3*(nW+17*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+11*N; i < nH+12*N; i++){
    for(int j = 3*(nW+17*N); j < 3*(nW+18*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+11*N; i < nH+12*N; i++){
    for(int j = 3*(nW+18*N); j < 3*(nW+19*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+11*N; i < nH+12*N; i++){
    for(int j = 3*(nW+19*N); j < 3*(nW+20*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }

  //ligne 12-13
  for(int i = nH+12*N; i < nH+13*N; i++){
    for(int j = 3*(nW+10*N); j < 3*(nW+11*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+12*N; i < nH+13*N; i++){
    for(int j = 3*(nW+11*N); j < 3*(nW+12*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+12*N; i < nH+13*N; i++){
    for(int j = 3*(nW+12*N); j < 3*(nW+13*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+12*N; i < nH+13*N; i++){
    for(int j = 3*(nW+13*N); j < 3*(nW+14*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+12*N; i < nH+13*N; i++){
    for(int j = 3*(nW+14*N); j < 3*(nW+15*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+12*N; i < nH+13*N; i++){
    for(int j = 3*(nW+15*N); j < 3*(nW+16*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+12*N; i < nH+13*N; i++){
    for(int j = 3*(nW+16*N); j < 3*(nW+17*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+12*N; i < nH+13*N; i++){
    for(int j = 3*(nW+17*N); j < 3*(nW+18*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+12*N; i < nH+13*N; i++){
    for(int j = 3*(nW+18*N); j < 3*(nW+19*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+12*N; i < nH+13*N; i++){
    for(int j = 3*(nW+19*N); j < 3*(nW+20*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }


  //ligne 13-14
  for(int i = nH+13*N; i < nH+14*N; i++){
    for(int j = 3*(nW+10*N); j < 3*(nW+11*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+13*N; i < nH+14*N; i++){
    for(int j = 3*(nW+11*N); j < 3*(nW+12*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+13*N; i < nH+14*N; i++){
    for(int j = 3*(nW+12*N); j < 3*(nW+13*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+13*N; i < nH+14*N; i++){
    for(int j = 3*(nW+13*N); j < 3*(nW+14*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+13*N; i < nH+14*N; i++){
    for(int j = 3*(nW+14*N); j < 3*(nW+15*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+13*N; i < nH+14*N; i++){
    for(int j = 3*(nW+15*N); j < 3*(nW+16*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+13*N; i < nH+14*N; i++){
    for(int j = 3*(nW+16*N); j < 3*(nW+17*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+13*N; i < nH+14*N; i++){
    for(int j = 3*(nW+17*N); j < 3*(nW+18*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+13*N; i < nH+14*N; i++){
    for(int j = 3*(nW+18*N); j < 3*(nW+19*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+13*N; i < nH+14*N; i++){
    for(int j = 3*(nW+19*N); j < 3*(nW+20*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }

  //ligne 14-15
  for(int i = nH+14*N; i < nH+15*N; i++){
    for(int j = 3*(nW+10*N); j < 3*(nW+11*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+14*N; i < nH+15*N; i++){
    for(int j = 3*(nW+11*N); j < 3*(nW+12*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+14*N; i < nH+15*N; i++){
    for(int j = 3*(nW+12*N); j < 3*(nW+13*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+14*N; i < nH+15*N; i++){
    for(int j = 3*(nW+13*N); j < 3*(nW+14*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+14*N; i < nH+15*N; i++){
    for(int j = 3*(nW+14*N); j < 3*(nW+15*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+14*N; i < nH+15*N; i++){
    for(int j = 3*(nW+15*N); j < 3*(nW+16*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+14*N; i < nH+15*N; i++){
    for(int j = 3*(nW+16*N); j < 3*(nW+17*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+14*N; i < nH+15*N; i++){
    for(int j = 3*(nW+17*N); j < 3*(nW+18*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+14*N; i < nH+15*N; i++){
    for(int j = 3*(nW+18*N); j < 3*(nW+19*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+14*N; i < nH+15*N; i++){
    for(int j = 3*(nW+19*N); j < 3*(nW+20*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }


  //ligne 15-16
  for(int i = nH+15*N; i < nH+16*N; i++){
    for(int j = 3*(nW+10*N); j < 3*(nW+11*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+15*N; i < nH+16*N; i++){
    for(int j = 3*(nW+11*N); j < 3*(nW+12*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+15*N; i < nH+16*N; i++){
    for(int j = 3*(nW+12*N); j < 3*(nW+13*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+15*N; i < nH+16*N; i++){
    for(int j = 3*(nW+13*N); j < 3*(nW+14*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+15*N; i < nH+16*N; i++){
    for(int j = 3*(nW+14*N); j < 3*(nW+15*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+15*N; i < nH+16*N; i++){
    for(int j = 3*(nW+15*N); j < 3*(nW+16*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+15*N; i < nH+16*N; i++){
    for(int j = 3*(nW+16*N); j < 3*(nW+17*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+15*N; i < nH+16*N; i++){
    for(int j = 3*(nW+17*N); j < 3*(nW+18*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+15*N; i < nH+16*N; i++){
    for(int j = 3*(nW+18*N); j < 3*(nW+19*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+15*N; i < nH+16*N; i++){
    for(int j = 3*(nW+19*N); j < 3*(nW+20*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }

  //ligne 16-17
  for(int i = nH+16*N; i < nH+17*N; i++){
    for(int j = 3*(nW+10*N); j < 3*(nW+11*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+16*N; i < nH+17*N; i++){
    for(int j = 3*(nW+11*N); j < 3*(nW+12*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+16*N; i < nH+17*N; i++){
    for(int j = 3*(nW+12*N); j < 3*(nW+13*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+16*N; i < nH+17*N; i++){
    for(int j = 3*(nW+13*N); j < 3*(nW+14*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+16*N; i < nH+17*N; i++){
    for(int j = 3*(nW+14*N); j < 3*(nW+15*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+16*N; i < nH+17*N; i++){
    for(int j = 3*(nW+15*N); j < 3*(nW+16*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+16*N; i < nH+17*N; i++){
    for(int j = 3*(nW+16*N); j < 3*(nW+17*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+16*N; i < nH+17*N; i++){
    for(int j = 3*(nW+17*N); j < 3*(nW+18*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+16*N; i < nH+17*N; i++){
    for(int j = 3*(nW+18*N); j < 3*(nW+19*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+16*N; i < nH+17*N; i++){
    for(int j = 3*(nW+19*N); j < 3*(nW+20*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }



  //ligne 17-18
  for(int i = nH+17*N; i < nH+18*N; i++){
    for(int j = 3*(nW+10*N); j < 3*(nW+11*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+17*N; i < nH+18*N; i++){
    for(int j = 3*(nW+11*N); j < 3*(nW+12*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+17*N; i < nH+18*N; i++){
    for(int j = 3*(nW+12*N); j < 3*(nW+13*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+17*N; i < nH+18*N; i++){
    for(int j = 3*(nW+13*N); j < 3*(nW+14*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+17*N; i < nH+18*N; i++){
    for(int j = 3*(nW+14*N); j < 3*(nW+15*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+17*N; i < nH+18*N; i++){
    for(int j = 3*(nW+15*N); j < 3*(nW+16*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+17*N; i < nH+18*N; i++){
    for(int j = 3*(nW+16*N); j < 3*(nW+17*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+17*N; i < nH+18*N; i++){
    for(int j = 3*(nW+17*N); j < 3*(nW+18*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+17*N; i < nH+18*N; i++){
    for(int j = 3*(nW+18*N); j < 3*(nW+19*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+17*N; i < nH+18*N; i++){
    for(int j = 3*(nW+19*N); j < 3*(nW+20*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }

  //ligne 18-19
  for(int i = nH+18*N; i < nH+19*N; i++){
    for(int j = 3*(nW+10*N); j < 3*(nW+11*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+18*N; i < nH+19*N; i++){
    for(int j = 3*(nW+11*N); j < 3*(nW+12*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+18*N; i < nH+19*N; i++){
    for(int j = 3*(nW+12*N); j < 3*(nW+13*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+18*N; i < nH+19*N; i++){
    for(int j = 3*(nW+13*N); j < 3*(nW+14*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+18*N; i < nH+19*N; i++){
    for(int j = 3*(nW+14*N); j < 3*(nW+15*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+18*N; i < nH+19*N; i++){
    for(int j = 3*(nW+15*N); j < 3*(nW+16*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+18*N; i < nH+19*N; i++){
    for(int j = 3*(nW+16*N); j < 3*(nW+17*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+18*N; i < nH+19*N; i++){
    for(int j = 3*(nW+17*N); j < 3*(nW+18*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  for(int i = nH+18*N; i < nH+19*N; i++){
    for(int j = 3*(nW+18*N); j < 3*(nW+19*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 255;
      ImgOut[i*3*(nW+20*N)+j+1] = 255;
      ImgOut[i*3*(nW+20*N)+j+2] = 255;
    }
  }
  for(int i = nH+18*N; i < nH+19*N; i++){
    for(int j = 3*(nW+19*N); j < 3*(nW+20*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }


  for(int i = nH+19*N; i < nH+20*N; i++){
    for(int j = 3*(nW+10*N); j < 3*(nW+20*N); j+=3){
      ImgOut[i*3*(nW+20*N)+j] = 0;
      ImgOut[i*3*(nW+20*N)+j+1] = 0;
      ImgOut[i*3*(nW+20*N)+j+2] = 0;
    }
  }
  

  ecrire_image_ppm(cNomImgEcrite, ImgOut, nH + 20*N, nW+20*N);
  free(ImgIn);
  return 1;
}
