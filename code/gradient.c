#include "image_ppm.h"

void usage(char * s){
  printf("Usage %s : imageIn.pgm imageOut.pgm\n", s);
}



int main(int argc, char* argv[]){
  char cNomImgLue[250], cNomImgEcrite[250], cGx[250], cGy[250];
  int nH, nW, nTaille;
  int gx, gy;

  if(argc < 3){
    usage(argv[0]);
    exit(EXIT_FAILURE);
  }

  sscanf (argv[1],"%s",cNomImgLue) ;
  sscanf (argv[2],"%s",cNomImgEcrite);

  sscanf ("gradient_x.pgm","%s",cGx);
  sscanf ("gradient_y.pgm","%s",cGy);

  OCTET *ImgIn, *ImgOut, *Gx, *Gy;
   
  lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgOut, OCTET, nTaille);
  allocation_tableau(Gx, OCTET, nTaille);
  allocation_tableau(Gy, OCTET, nTaille);


  for(int i = 0; i < nH-1 ; i++){
    for(int j = 0; j < nW-1 ; j++){
      Gx[i*nW+j] = abs(ImgIn[(i+1)*nW+j] - ImgIn[i*nW+j]);
      Gy[i*nW+j] = abs(ImgIn[i*nW+j+1] - ImgIn[i*nW+j]);
    }
  }
  for(int j = 0; j < nW-1 ; j++){
    Gx[(nH-1)*nW+j] = ImgIn[(nH-1)*nW+j];
    Gy[(nH-1)*nW+j] = abs(ImgIn[(nH-1)*nW+j+1] - ImgIn[(nH-1)*nW+j]);
  }

  for(int i = 0; i < nH-1 ; i++){
    Gx[i*nW+nW-1] = abs(ImgIn[(i+1)*nW+nW-1] - ImgIn[i*nW+nW-1]);
    Gy[i*nW+nW-1] = ImgIn[i*nW+nW-1];
  }

  Gx[(nH-1)*nW+nW-1] = ImgIn[(nH-1)*nW+nW-1];
  Gy[(nH-1)*nW+nW-1] = ImgIn[(nH-1)*nW+nW-1];

  ecrire_image_pgm(cGx, Gx,  nH, nW);
  ecrire_image_pgm(cGy, Gy,  nH, nW);


  for(int i = 0; i < nH ; i++){
    for(int j = 0; j < nW ; j++){
      gx = abs(Gx[i*nW+j]);
      gy = abs(Gy[i*nW+j]);
      if(gx > gy)
	ImgOut[i*nW+j] = gx;
      else
	ImgOut[i*nW+j] = gy;
    }
  }

  ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
      

  free(ImgIn);
  free(Gx);
  free(Gy);
  return 1;
}
