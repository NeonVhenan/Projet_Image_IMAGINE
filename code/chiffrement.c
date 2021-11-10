#include "image_ppm.h"
#include <string.h>
#include <stdlib.h>



void usage(char * s){
  printf("Usage : %s ImageIn.pgm ImageOut.pgm key_x0 key_k\n", s);
}



int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nTaille3;
  int nH8, nW8, nTaille8, nTaille38;
  int x0, k;
  int i8, j8;
  int mR, mG, mB;
  int di, dj;
  
  
  if (argc != 5){
      usage(argv[0]);
      exit(EXIT_FAILURE) ;
  }
   
  sscanf (argv[1],"%s",cNomImgLue);
  sscanf (argv[2],"%s",cNomImgEcrite);
  x0 = atoi(argv[3]);
  k = atoi(argv[4]); 

  OCTET *ImgIn, *ImgR, *ImgB, *ImgG, *ImgRbloc, *ImgBbloc, *ImgGbloc, *ImgRbits, *ImgBbits, *ImgGbits *ImgOut;
   
  lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  nTaille3 = 3 * nTaille;

  allocation_tableau(ImgIn, OCTET, nTaille3);
  lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

  allocation_tableau(ImgR, OCTET, nTaille);
  allocation_tableau(ImgG, OCTET, nTaille);
  allocation_tableau(ImgB, OCTET, nTaille);

  nH8 = nH;
  if(nH % 8 != 0)
    nH8 = nH + (8 - (nH % 8));
  nW8 = nW;
  if(nW % 8 != 0)
    nW8 = nW + (8 - (nW % 8));
  nTaille8 = nH8 * nW8;
  nTaille38 = nTaille8 * 3;
    
  allocation_tableau(ImgOut, OCTET, nTaille38);
  allocation_tableau(ImgR8, OCTET, nTaille8);
  allocation_tableau(ImgG8, OCTET, nTaille8);
  allocation_tableau(ImgB8, OCTET, nTaille8);

  allocation_tableau(ImgRbloc, OCTET, nTaille8/64);
  allocation_tableau(ImgGbloc, OCTET, nTaille8/64);
  allocation_tableau(ImgBbloc, OCTET, nTaille8/64);

  allocation_tableau(ImgRbits, OCTET, nTaille8/8);
  allocation_tableau(ImgGbits, OCTET, nTaille8/8);
  allocation_tableau(ImgBbits, OCTET, nTaille8/8);
 
  for(int i = 0; i < nH; i++){
    j8 = 0;
    for(int j = 0; j < nW*3; j+=3){
      ImgR[i*nW+j8] = ImgIn[i*nW*3+j];
      ImgG[i*nW+j8] = ImgIn[i*nW*3+j+1];
      ImgB[i*nW+j8] = ImgIn[i*nW*3+j+2];
      j8++;
    }
  }

  i8 = 0;
  for(int i = 0; i < nH; i+=8){
    j8 = 0;
    for(int j = 0; j < nW; j+=8){
      mR = 0;
      mB = 0;
      mG = 0;
      di = 0;
      for(int l = 0; l < 8; l++){
	if(i + l >= nH){
	  di = l;
	  l = (nH - 1) - i;
	}
	dj = 0;
	for(int w = 0 ; w < 8; w++){
	  if(j + w >= nW){
	    dj = w;
	    w = (nW - 1) - j;
	  }
	  mR += ImgR[(i+l)*nW+j+w];
	  mG += ImgG[(i+l)*nW+j+w];
	  mB += ImgB[(i+l)*nW+j+w];
	  if(dj != 0){
	    w = dj;
	  }
	}
	if(di != 0){
	  l = di;
	}
      }
      mR = mR / 64.0;
      mG = mG / 64.0;
      mB = mB / 64.0;
      ImgRbloc[i8*(nW8/8)+j8] = mR;
      ImgGbloc[i8*(nW8/8)+j8] = mG;
      ImgBbloc[i8*(nW8/8)+j8] = mB;
      j8++;
    }
    i8++;
  }

  i8 = 0;
  for(int i = 0; i < nTaille8/8, i+=8){
    if(ImgRbloc[i8] >= 128){ 
      ImgRbits[i+7] = 1;
      ImgRbloc[i8]-=128;
    }
    else{
      ImgRbits[i+7] = 0;
    }
    if(ImgRbloc[i8] >= 64){ 
      ImgRbits[i+6] = 1;
      ImgRbloc[i8]-=64;
    }
    else{
      ImgRbits[i+6] = 0;
    }
    if(ImgRbloc[i8] >= 32){ 
      ImgRbits[i+5] = 1;
      ImgRbloc[i8]-=32;
    }
    else{
      ImgRbits[i+5] = 0;
    }
    if(ImgRbloc[i8] >= 16){ 
      ImgRbits[i+4] = 1;
      ImgRbloc[i8]-=16;
    }
    else{
      ImgRbits[i+4] = 0;
    }
    if(ImgRbloc[i8] >= 8){ 
      ImgRbits[i+3] = 1;
      ImgRbloc[i8]-= 8;
    }
    else{
      ImgRbits[i+3] = 0;
    }
    if(ImgRbloc[i8] >= 4){ 
      ImgRbits[i+2] = 1;
      ImgRbloc[i8]-= 4;
    }
    else{
      ImgRbits[i+2] = 0;
    }
    if(ImgRbloc[i8] >= 2){ 
      ImgRbits[i+1] = 1;
      ImgRbloc[i8]-= 2;
    }
    else{
      ImgRbits[i+1] = 0;
    }
    ImgRbits[i] = ImgRbloc[i8];
    i8++;
  }

  i8 = 0;
  for(int i = 0; i < nTaille8/8, i+=8){
    if(ImgGbloc[i8] >= 128){ 
      ImgGbits[i+7] = 1;
      ImgGbloc[i8]-=128;
    }
    else{
      ImgGbits[i+7] = 0;
    }
    if(ImgGbloc[i8] >= 64){ 
      ImgGbits[i+6] = 1;
      ImgGbloc[i8]-=64;
    }
    else{
      ImgGbits[i+6] = 0;
    }
    if(ImgGbloc[i8] >= 32){ 
      ImgGbits[i+5] = 1;
      ImgGbloc[i8]-=32;
    }
    else{
      ImgGbits[i+5] = 0;
    }
    if(ImgGbloc[i8] >= 16){ 
      ImgGbits[i+4] = 1;
      ImgGbloc[i8]-=16;
    }
    else{
      ImgGbits[i+4] = 0;
    }
    if(ImgGbloc[i8] >= 8){ 
      ImgGbits[i+3] = 1;
      ImgGbloc[i8]-= 8;
    }
    else{
      ImgGbits[i+3] = 0;
    }
    if(ImgGbloc[i8] >= 4){ 
      ImgGbits[i+2] = 1;
      ImgGbloc[i8]-= 4;
    }
    else{
      ImgGbits[i+2] = 0;
    }
    if(ImgGbloc[i8] >= 2){ 
      ImgGbits[i+1] = 1;
      ImgGbloc[i8]-= 2;
    }
    else{
      ImgGbits[i+1] = 0;
    }
    ImgGbits[i] = ImgGbloc[i8];
    i8++;
  }

  i8 = 0;
  for(int i = 0; i < nTaille8/8, i+=8){
    if(ImgBbloc[i8] >= 128){ 
      ImgBbits[i+7] = 1;
      ImgBbloc[i8]-=128;
    }
    else{
      ImgBbits[i+7] = 0;
    }
    if(ImgBbloc[i8] >= 64){ 
      ImgBbits[i+6] = 1;
      ImgBbloc[i8]-=64;
    }
    else{
      ImgBbits[i+6] = 0;
    }
    if(ImgBbloc[i8] >= 32){ 
      ImgBbits[i+5] = 1;
      ImgBbloc[i8]-=32;
    }
    else{
      ImgBbits[i+5] = 0;
    }
    if(ImgBbloc[i8] >= 16){ 
      ImgBbits[i+4] = 1;
      ImgBbloc[i8]-=16;
    }
    else{
      ImgBbits[i+4] = 0;
    }
    if(ImgBbloc[i8] >= 8){ 
      ImgBbits[i+3] = 1;
      ImgBbloc[i8]-= 8;
    }
    else{
      ImgBbits[i+3] = 0;
    }
    if(ImgBbloc[i8] >= 4){ 
      ImgBbits[i+2] = 1;
      ImgBbloc[i8]-= 4;
    }
    else{
      ImgBbits[i+2] = 0;
    }
    if(ImgBbloc[i8] >= 2){ 
      ImgBbits[i+1] = 1;
      ImgBbloc[i8]-= 2;
    }
    else{
      ImgBbits[i+1] = 0;
    }
    ImgBbits[i] = ImgBbloc[i8];
    i8++;
  }

  

  //ecrire_image_ppm(cNomImgEcrite, ImgOutbloc, nH8/8, nW8/8);

  free(ImgIn);
  
  return 1;
}
