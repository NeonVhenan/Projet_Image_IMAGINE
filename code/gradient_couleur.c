#include "image_ppm.h"

void usage(char * s){
  printf("Usage %s : imageIn.ppm imageOut.ppm\n", s);
}


int max(int a, int b, int c){
  if(a >= b && a >= c)
    return a;
  if (b >= a && b >= c)
    return b;
  return c;
}



int main(int argc, char* argv[]){
  char cNomImgLue[250], cNomImgEcrite[250], cR[250], cG[250], cB[250];
  int nH, nW, nTaille, nTaille3;
  int gx, gy;
  int k;

  if(argc < 3){
    usage(argv[0]);
    exit(EXIT_FAILURE);
  }

  sscanf (argv[1],"%s",cNomImgLue) ;
  sscanf (argv[2],"%s",cNomImgEcrite);

  sscanf ("gradientR.pgm","%s",cR);
  sscanf ("gradientG.pgm","%s",cG);
  sscanf ("gradientB.pgm","%s",cB);

  OCTET *ImgIn, *ImgOut, *Gx, *Gy, *ImgR, *ImgG, *ImgB, *ImgROut, *ImgGOut, *ImgBOut;
   
  lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;
  nTaille3 = 3* nTaille;

  allocation_tableau(ImgIn, OCTET, nTaille3);
  lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgR, OCTET, nTaille);
  allocation_tableau(ImgG, OCTET, nTaille);
  allocation_tableau(ImgB, OCTET, nTaille);
  allocation_tableau(ImgROut, OCTET, nTaille);
  allocation_tableau(ImgGOut, OCTET, nTaille);
  allocation_tableau(ImgBOut, OCTET, nTaille);
  allocation_tableau(ImgOut, OCTET, nTaille);
  allocation_tableau(Gx, OCTET, nTaille);
  allocation_tableau(Gy, OCTET, nTaille);

  /***************************ROUGE***************************/

  for(int i = 0; i < nH; i++) {
    k = 0;
    for(int j = 0; j < nW*3; j+=3){
      ImgR[i*nW+k] = ImgIn[i*nW*3+j];
      k++;
    }
  }

  for(int i = 0; i < nH-1 ; i++){
    for(int j = 0; j < nW-1 ; j++){
      Gx[i*nW+j] = abs(ImgR[(i+1)*nW+j] - ImgR[i*nW+j]);
      Gy[i*nW+j] = abs(ImgR[i*nW+j+1] - ImgR[i*nW+j]);
    }
  }
  for(int j = 0; j < nW-1 ; j++){
    Gx[(nH-1)*nW+j] = ImgR[(nH-1)*nW+j];
    Gy[(nH-1)*nW+j] = abs(ImgR[(nH-1)*nW+j+1] - ImgR[(nH-1)*nW+j]);
  }

  for(int i = 0; i < nH-1 ; i++){
    Gx[i*nW+nW-1] = abs(ImgR[(i+1)*nW+nW-1] - ImgR[i*nW+nW-1]);
    Gy[i*nW+nW-1] = ImgR[i*nW+nW-1];
  }

  Gx[(nH-1)*nW+nW-1] = ImgR[(nH-1)*nW+nW-1];
  Gy[(nH-1)*nW+nW-1] = ImgR[(nH-1)*nW+nW-1];

  for(int i = 0; i < nH ; i++){
    for(int j = 0; j < nW ; j++){
      gx = abs(Gx[i*nW+j]);
      gy = abs(Gy[i*nW+j]);
      if(gx > gy)
	ImgROut[i*nW+j] = gx;
      else
	ImgROut[i*nW+j] = gy;
    }
  }

  ecrire_image_pgm(cR, ImgROut,  nH, nW);

  /***************************VERT***************************/

  for(int i = 0; i < nH; i++) {
    k = 0;
    for(int j = 0; j < nW*3; j+=3){
      ImgG[i*nW+k] = ImgIn[i*nW*3+j+1];
      k++;
    }
  }

  for(int i = 0; i < nH-1 ; i++){
    for(int j = 0; j < nW-1 ; j++){
      Gx[i*nW+j] = abs(ImgG[(i+1)*nW+j] - ImgG[i*nW+j]);
      Gy[i*nW+j] = abs(ImgG[i*nW+j+1] - ImgG[i*nW+j]);
    }
  }
  for(int j = 0; j < nW-1 ; j++){
    Gx[(nH-1)*nW+j] = ImgG[(nH-1)*nW+j];
    Gy[(nH-1)*nW+j] = abs(ImgG[(nH-1)*nW+j+1] - ImgG[(nH-1)*nW+j]);
  }

  for(int i = 0; i < nH-1 ; i++){
    Gx[i*nW+nW-1] = abs(ImgG[(i+1)*nW+nW-1] - ImgG[i*nW+nW-1]);
    Gy[i*nW+nW-1] = ImgG[i*nW+nW-1];
  }

  Gx[(nH-1)*nW+nW-1] = ImgG[(nH-1)*nW+nW-1];
  Gy[(nH-1)*nW+nW-1] = ImgG[(nH-1)*nW+nW-1];

  for(int i = 0; i < nH ; i++){
    for(int j = 0; j < nW ; j++){
      gx = abs(Gx[i*nW+j]);
      gy = abs(Gy[i*nW+j]);
      if(gx > gy)
	ImgGOut[i*nW+j] = gx;
      else
	ImgGOut[i*nW+j] = gy;
    }
  }

  ecrire_image_pgm(cG, ImgGOut,  nH, nW);

  /***************************BLEU***************************/

  for(int i = 0; i < nH; i++) {
    k = 0;
    for(int j = 0; j < nW*3; j+=3){
      ImgB[i*nW+k] = ImgIn[i*nW*3+j+2];
      k++;
    }
  }

  for(int i = 0; i < nH-1 ; i++){
    for(int j = 0; j < nW-1 ; j++){
      Gx[i*nW+j] = abs(ImgB[(i+1)*nW+j] - ImgB[i*nW+j]);
      Gy[i*nW+j] = abs(ImgB[i*nW+j+1] - ImgB[i*nW+j]);
    }
  }
  for(int j = 0; j < nW-1 ; j++){
    Gx[(nH-1)*nW+j] = ImgB[(nH-1)*nW+j];
    Gy[(nH-1)*nW+j] = abs(ImgB[(nH-1)*nW+j+1] - ImgB[(nH-1)*nW+j]);
  }

  for(int i = 0; i < nH-1 ; i++){
    Gx[i*nW+nW-1] = abs(ImgB[(i+1)*nW+nW-1] - ImgB[i*nW+nW-1]);
    Gy[i*nW+nW-1] = ImgB[i*nW+nW-1];
  }

  Gx[(nH-1)*nW+nW-1] = ImgB[(nH-1)*nW+nW-1];
  Gy[(nH-1)*nW+nW-1] = ImgB[(nH-1)*nW+nW-1];

  for(int i = 0; i < nH ; i++){
    for(int j = 0; j < nW ; j++){
      gx = abs(Gx[i*nW+j]);
      gy = abs(Gy[i*nW+j]);
      if(gx > gy)
	ImgBOut[i*nW+j] = gx;
      else
	ImgBOut[i*nW+j] = gy;
    }
  }

  ecrire_image_pgm(cB, ImgBOut,  nH, nW);

  //***************************ImgOUT***************************/

  int val;
  for(int i = 0; i < nH; i++){
    for(int j = 0; j < nW; j++){
      val = max(ImgROut[i*nW+j], ImgGOut[i*nW+j], ImgBOut[i*nW+j]);
      printf("%d   ", val);
      ImgOut[i*nW+j] = val;
    }
    printf("\n");
  }
  

  ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
      

  free(ImgIn);
  free(Gx);
  free(Gy);
  free(ImgR);
  free(ImgG);
  free(ImgB);
  return 1;
}
