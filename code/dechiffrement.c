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
  double x0, k;
  int i8, j8;
  int mR, mG, mB;
  int di, dj;
  tab * xn;
  
  
  if (argc != 5){
      usage(argv[0]);
      exit(EXIT_FAILURE) ;
  }
   
  sscanf (argv[1],"%s",cNomImgLue);
  sscanf (argv[2],"%s",cNomImgEcrite);
  x0 = atof(argv[3]);
  k = atof(argv[4]); 

  OCTET *ImgIn, *ImgR, *ImgB, *ImgG, *ImgRbloc, *ImgBbloc, *ImgGbloc, *ImgRchiffr, *ImgBchiffr, *ImgGchiffr, *ImgOut, *ImgR8, *ImgG8, *ImgB8;

   
  lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  nTaille3 = 3 * nTaille;

  allocation_tableau(ImgIn, OCTET, nTaille3);
  lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

  allocation_tableau(ImgR, OCTET, nTaille);
  allocation_tableau(ImgG, OCTET, nTaille);
  allocation_tableau(ImgB, OCTET, nTaille);

  nH8 = nH;
  if(nH % N != 0)
    nH8 = nH + (N - (nH % N));
  nW8 = nW;
  if(nW % N != 0)
    nW8 = nW + (N - (nW % N));
  nTaille8 = nH8 * nW8;
  nTaille38 = nTaille8 * 3;
    
  allocation_tableau(ImgOut, OCTET, nTaille38);

  allocation_tableau(ImgRbloc, OCTET, nTaille8/(N*N));
  allocation_tableau(ImgGbloc, OCTET, nTaille8/(N*N));
  allocation_tableau(ImgBbloc, OCTET, nTaille8/(N*N));

  allocation_tableau(ImgRchiffr, OCTET, nTaille8/(N*N));
  allocation_tableau(ImgGchiffr, OCTET, nTaille8/(N*N));
  allocation_tableau(ImgBchiffr, OCTET, nTaille8/(N*N));

  allocation_tableau(ImgR8, OCTET, nTaille8);
  allocation_tableau(ImgG8, OCTET, nTaille8);
  allocation_tableau(ImgB8, OCTET, nTaille8);

 
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
  for(int i = 0; i < nH; i+=N){
    j8 = 0;
    for(int j = 0; j < nW; j+=N){
      mR = 0;
      mB = 0;
      mG = 0;
      di = 0;
      for(int l = 0; l < N; l++){
	if(i + l >= nH){
	  di = l;
	  l = (nH - 1) - i;
	}
	dj = 0;
	for(int w = 0 ; w < N; w++){
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
      mR = mR * 1.0 / (N*N);
      mG = mG * 1.0 / (N*N);
      mB = mB * 1.0 / (N*N);
      ImgRbloc[i8*(nW8/N)+j8] = mR;
      ImgGbloc[i8*(nW8/N)+j8] = mG;
      ImgBbloc[i8*(nW8/N)+j8] = mB;
      j8++;
    }
    i8++;
  }

  xn = malloc(sizeof(double)*nTaille8/(N*N));
  xn[0].val = cos(k*acos(x0));
  xn[0].pos = 0;
  
  
  for(int i = 1; i < nTaille8/(N*N); i++){
    xn[i].val = cos(k*acos(xn[i-1].val));
    xn[i].pos = i;
  }

  qsort(xn, nTaille8/(N*N), sizeof(tab), compare);

  for(int i = 0; i < nTaille8/(N*N); i++){
    ImgRchiffr[xn[i].pos] = ImgRbloc[i];
    ImgGchiffr[xn[i].pos] = ImgGbloc[i];
    ImgBchiffr[xn[i].pos] = ImgBbloc[i];
  }

  i8 = 0;
  for(int i = 0; i < nH8; i+=N){
    j8 = 0;
    for(int j = 0; j < nW8; j+=N){
      for(int l = 0; l < N; l++){
	for(int p = 0; p < N; p++){
	  ImgR8[(i+l)*nW8+j+p] = ImgRchiffr[i8*(nW8/N)+j8];
	  ImgG8[(i+l)*nW8+j+p] = ImgGchiffr[i8*(nW8/N)+j8];
	  ImgB8[(i+l)*nW8+j+p] = ImgBchiffr[i8*(nW8/N)+j8];
	}
      }
      j8++;
    }
    i8++;
  }

  for(int i = 0; i < nH8; i++){
    j8 = 0;
    for(int j = 0; j < nW8*3; j+=3){
      ImgOut[i*nW8*3+j] = ImgR8[i*nW8+j8];
      ImgOut[i*nW8*3+j+1] = ImgG8[i*nW8+j8];
      ImgOut[i*nW8*3+j+2] = ImgB8[i*nW8+j8];
      j8++;
    }
  }
  
  ecrire_image_ppm(cNomImgEcrite, ImgOut, nH8, nW8);

  free(ImgIn);

  
  
  return 1;
}
