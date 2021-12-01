#include "image_ppm.h"
#include <string.h>
#include <stdlib.h>

#define test 70
#define test2 50
#define test3 51
#define test4 75
#define test5 40

void usage(char * s){
  printf("Usage : %s ImageIn.pgm ImageOut.pgm\n", s);
}

int distanceMax(int i, int j, OCTET * IMG){
  if(abs(IMG[i] - IMG[j]) >= abs(IMG[i+1] - IMG[j+1]) && abs(IMG[i] - IMG[j]) >= abs(IMG[i+2] - IMG[j+2]))
    return abs(IMG[i] - IMG[j]);
  if(abs(IMG[i] - IMG[j]) <= abs(IMG[i+1] - IMG[j+1]) && abs(IMG[i+1] - IMG[j+1]) >= abs(IMG[i+2] - IMG[j+2]))
    return abs(IMG[i+1] - IMG[j+1]);
  return abs(IMG[i+2] - IMG[j+2]);
}



int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nTaille3;
  int nHC, nWC, nTailleC, nTaille3C;
  int nHR, nWR, nTailleR, nTaille3R;
  int nHP, nWP, nTailleP, nTaille3P;
  int nHPN, nWPN, nTaillePN, nTaille3PN;
  int xp1, yp1;
  int xp2, yp2;
  int xp3, yp3;
  int k, l;
  int tailleBlocH, tailleBlocW, valMoyH, valMoyW, valMoyI, valMoyJ;
  int nbBlocs;
  
  
  if (argc != 3){
      usage(argv[0]);
      exit(EXIT_FAILURE) ;
  }
   
  sscanf (argv[1],"%s",cNomImgLue);
  sscanf (argv[2],"%s",cNomImgEcrite);

  OCTET *ImgIn, *ImgCadre, *Img, *ImgP, *ImgOut;

   
  lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  nTaille3 = 3 * nTaille;

  allocation_tableau(ImgIn, OCTET, nTaille3);
  lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

  /**********************************IMAGE AVEC CADRE**********************************/
  
  k = 0;
  l = 0;
  while(ImgIn[k*nW*3+l] > test || ImgIn[k*nW*3+l+1] > test || ImgIn[k*nW*3+l+2] > test){
    l+=3;
    if(l > (nW-1)*3){
      l = 0;
      k++;
    }
  }

  xp1 = k;
  yp1 = l;

  k = xp1;
  l = (nW-1)*3;
  while(ImgIn[k*nW*3+l] > test || ImgIn[k*nW*3+l+1] > test || ImgIn[k*nW*3+l+2] > test){
    l-=3;
    if(l < 3*(nW/2)){
      l = (nW-1)*3;
      k++;
    }
  }
  
  xp2 = k;
  yp2 = l-3;

  if(xp2 > xp1){
    xp1 = xp2;
  }

  k = nH-1;
  l = (nW-1)*3;
  while(ImgIn[k*nW*3+l] > test || ImgIn[k*nW*3+l+1] > test ||  ImgIn[k*nW*3+l+2] > test){
    k--;
    if(k < nH/2){
      l-=3;
      k = nH-1;
    }
  }

  xp3 = k-1;
  yp3 = l;

  if(yp3 > yp2)
    yp2 = yp3;

  printf("(%d %d)    %d %d   %d %d  %d %d\n",nH, 3*nW, xp1, yp1, xp2, yp2, xp3, yp3);
  

  nHC = xp3 - xp1;
  nWC = (yp2 - yp1)/3;
  nTailleC = nHC * nWC;
  nTaille3C = 3* nTailleC;
  printf("why?\n");

  allocation_tableau(ImgCadre, OCTET, nTaille3C);

  for(int i = 0; i < nHC ; i++){
    for(int j = 0; j < nWC*3; j+=3){
      ImgCadre[i*3*nWC+j] = ImgIn[(i+xp1)*3*nW+j+yp1];
      ImgCadre[i*3*nWC+j+1] = ImgIn[(i+xp1)*3*nW+j+1+yp1];
      ImgCadre[i*3*nWC+j+2] = ImgIn[(i+xp1)*3*nW+j+2+yp1];
    }
  }
  
  //ecrire_image_ppm(cNomImgEcrite, ImgCadre, nHC, nWC);

  /**********************************IMAGE SANS CADRE**********************************/

  k = 0;
  l = 0;
  while(ImgCadre[k*nWC*3+l] <= test4 && ImgCadre[k*nWC*3+l+1] <= test4 && ImgCadre[k*nWC*3+l+2] <= test4){
    l+=3;
    if(l >= 3*(nW/4)){
      k++;
      l = 0;
    }
  }

  xp1 = k;
  yp1 = l;

  
  k = xp1;
  l = 3*(nWC-1) - 81;
  printf("%d %d %d\n", ImgCadre[k*nWC*3+l], ImgCadre[k*nWC*3+l+1], ImgCadre[k*nWC*3+l+2]);
  while(ImgCadre[k*nWC*3+l] <= test3 || ImgCadre[k*nWC*3+l+1] <= test3 || ImgCadre[k*nWC*3+l+2] <= test3){
    l-=3;
    if(l < 3*(3*nW/4)){
      k++;
      l = 3*(nWC-1) - 81;
    }
  }

  xp2 = k;
  yp2 = l;
  
  k = nHC-1;
  l = 0;
  while(ImgCadre[k*nWC*3+l] <= test2 && ImgCadre[k*nWC*3+l+1] <= test2){//&& ImgCadre[k*nWC*3+l+2] <= test2){	
    k--;
    if(k < nH/2){
      l+=3;
      k = nHC-1;
    }
  }

  xp3 = k-1;
  yp3 = l;

  printf("%d %d   %d %d  %d %d\n", xp1, yp1, xp2, yp2, xp3, yp3);
  
  nHR = xp3 - xp1;
  nWR = (yp2 - yp1)/3;
  nTailleR = nHR * nWR;
  nTaille3R = 3 * nTailleR;

  allocation_tableau(Img, OCTET, nTaille3R);

  for(int i = 0; i < nHR ; i++){
    for(int j = 0; j < nWR*3; j+=3){
      Img[i*3*nWR+j] = ImgCadre[(i+xp1)*3*nWC+j+yp1];
      Img[i*3*nWR+j+1] = ImgCadre[(i+xp1)*3*nWC+j+1+yp1];
      Img[i*3*nWR+j+2] = ImgCadre[(i+xp1)*3*nWC+j+2+yp1];
    }
  }

  ecrire_image_ppm(cNomImgEcrite, Img, nHR, nWR);

  k = nHC-1;
  l = 3*(nWC-1);
  
  while(ImgCadre[k*nWC*3+l] <= test && ImgCadre[k*nWC*3+l+1] <= test && ImgCadre[k*nWC*3+l+2] <= test){
    l-=3;
    if(l < 3*3*(nWC)/4){
      k--;
      l = 3*(nWC-1);
    }
  } 

  while(ImgCadre[k*nWC*3+l] > test && ImgCadre[k*nWC*3+l+1] > test && ImgCadre[k*nWC*3+l+2] > test2){
    k--;
  }

  ImgCadre[k*nWC*3+l] = 255;
  ImgCadre[k*nWC*3+l+1] = 0;
  ImgCadre[k*nWC*3+l+2] = 0;

  nbBlocs = 0;
  int somme = 0;
  tailleBlocH = k;
  while(ImgCadre[k*nWC*3+l] <= test5 && ImgCadre[k*nWC*3+l+1] <= test5 && ImgCadre[k*nWC*3+l+2] <= test5){
    k--;
  }
  somme += tailleBlocH-k;
  nbBlocs++;

  int testBloc = 0;
  while(testBloc != 1 && k > 3*nH/4){
    tailleBlocH = k;
    while(ImgCadre[k*nWC*3+l] > test5 && ImgCadre[k*nWC*3+l+1] > test5 && ImgCadre[k*nWC*3+l+2] > test5){
      k--;
    }
    somme += tailleBlocH-k;
    nbBlocs++;

    tailleBlocH = k;
    while(ImgCadre[k*nWC*3+l] <= test5 || ImgCadre[k*nWC*3+l+1] <= test5 && ImgCadre[k*nWC*3+l+2] <= test5){
      k--;
    }
    if(tailleBlocH - k > 40)
      testBloc = 1;
    else{
      somme += tailleBlocH-k;
      nbBlocs++;
    }
    printf("hello %d\n", nbBlocs);
  }

  tailleBlocH = somme/nbBlocs;
  
  printf("taille bloc : %d\n", tailleBlocH);


  k = nHC-1;
  l = 3*(nWC-1)-21;
  
  while(ImgCadre[k*nWC*3+l] <= test || ImgCadre[k*nWC*3+l+1] <= test){// && ImgCadre[k*nWC*3+l+2] <= test){
    k--;
    if(k < 7*(nHC)/8){
      k = nHC - 1;
      l -= 3;
    }
  }

  l-=3;
  
  int l_avant = l;

  while(ImgCadre[k*nWC*3+l] > test5 && ImgCadre[k*nWC*3+l+1] > test5){// && ImgCadre[k*nWC*3+l+2] > test){
    l-=3;
  }
  

  nbBlocs = 0;
  somme = 0;
  tailleBlocW = l/3;
  printf("valeur : %d %d %d\n",ImgCadre[k*nWC*3+l], ImgCadre[k*nWC*3+l+1], ImgCadre[k*nWC*3+l+2]);
  while(ImgCadre[k*nWC*3+l] <= test || ImgCadre[k*nWC*3+l+1] <= test){// && ImgCadre[k*nWC*3+l+2] <= test){
    l-=3;
  }
  somme += tailleBlocW - l/3;
  nbBlocs++;

  //printf("diff : %d %d\n", l_avant, l);

  /*ImgCadre[k*nWC*3+l] = 255;
  ImgCadre[k*nWC*3+l+1] = 255;
  ImgCadre[k*nWC*3+l+2] = 0;

  ecrire_image_ppm(cNomImgEcrite, ImgCadre, nHC, nWC);*/

  testBloc = 0;
  while(testBloc != 1 && l > 3*(3*nW/4)){
    tailleBlocW = l/3;
    while(ImgCadre[k*nWC*3+l] > test5 && ImgCadre[k*nWC*3+l+1] > test5){// && ImgCadre[k*nWC*3+l+2] > test5){
      l-=3;
    }
    if(tailleBlocW - l/3 < 40){
      somme += tailleBlocW - l/3;
      nbBlocs++;
      tailleBlocW = l/3;
      while(ImgCadre[k*nWC*3+l] <= test || ImgCadre[k*nWC*3+l+1] <= test){// && ImgCadre[k*nWC*3+l+2] <= test){
	l-=3;
      }
      if(tailleBlocW - l/3 >= 40)
	testBloc = 1;
      else{
	somme += tailleBlocW - l/3;
	nbBlocs++;
      }
      //printf("hello %d\n", nbBlocs);
    }
    else
      testBloc = 1;
  }

  printf("taille %f\n", somme*1.0/nbBlocs);
  
  tailleBlocW = somme/nbBlocs;
  
  printf("taille bloc : %d\n", tailleBlocW);

  printf("%d %f\n", nWR, 1.0*nWR/106);

  tailleBlocW = tailleBlocH;



  /**********************************IMAGE AVEC UN PIXEL PAR COULEUR**********************************/

  nHP = nHR/tailleBlocH;
  if(nHR % tailleBlocH != 0)
    nHP++;   
  nWP = nWR/tailleBlocW;
  if(nWR % tailleBlocW != 0)
    nWP++;
  
  if(tailleBlocH % 2 == 0)
    valMoyH = tailleBlocH/2;
  else
    valMoyH = (tailleBlocH+1)/2;

  if(tailleBlocW % 2 == 0)
    valMoyW = tailleBlocW/2;
  else
    valMoyW = (tailleBlocW+1)/2;
  
  printf("%d, %d\n", nHP, nWP);
  nTailleP = nHP * nWP;
  nTaille3P = 3 * nTailleP;

  allocation_tableau(ImgP, OCTET, nTaille3P);
  
  k = 0;
  for(int i = 0; i+tailleBlocH < nHR ; i+=tailleBlocH){
    l = 0;
    for(int j = 0; j+3*tailleBlocW < nWR*3; j+=3*tailleBlocW){
      ImgP[k*3*nWP+l] = Img[(i+valMoyH)*3*nWR+j+valMoyW*3];
      ImgP[k*3*nWP+l+1] = Img[(i+valMoyH)*3*nWR+j+1+valMoyW*3];
      ImgP[k*3*nWP+l+2] = Img[(i+valMoyH)*3*nWR+j+2+valMoyW*3];
      l+=3;
    }
    k++;
  }
  
  if(tailleBlocH * nHP > nHR){
    l = 0;
    if((tailleBlocH * nHP - nHR)%2 == 0)
      valMoyI = (tailleBlocH * nHP - nHR)/2;
    else
      valMoyI = (tailleBlocH * nHP - nHR + 1)/2;
    for(int j = 0; j+3*tailleBlocW < nWR*3; j+=3*tailleBlocW){
      ImgP[(nHP-1)*3*nWP+l] = Img[((nHP-1)*tailleBlocH+valMoyI)*3*nWR+j+valMoyW*3];
      ImgP[(nHP-1)*3*nWP+l+1] = Img[((nHP-1)*tailleBlocH+valMoyI)*3*nWR+j+1+valMoyW*3];
      ImgP[(nHP-1)*3*nWP+l+2] = Img[((nHP-1)*tailleBlocH+valMoyI)*3*nWR+j+2+valMoyW*3];
      l+=3;
    }
  }
  if(tailleBlocW * nWP >= nWR){
    k = 0;
    if((tailleBlocW * nWP - nWR)%2 == 0)
      valMoyJ = (tailleBlocW * nWP - nHR)/2;
    else
      valMoyJ = (tailleBlocW * nHP - nHR + 1)/2;
    for(int i = 0; i+tailleBlocH < nHR; i+=tailleBlocH){
      ImgP[k*3*nWP+(nWP-1)*3] = Img[(i+valMoyH)*3*nWR+((nWP-1)*tailleBlocW)*3];
      ImgP[k*3*nWP+(nWP-1)*3+1] = Img[(i+valMoyH)*3*nWR+((nWP-1)*tailleBlocW)*3+1];
      ImgP[k*3*nWP+(nWP-1)*3+2] = Img[(i+valMoyH)*3*nWR+((nWP-1)*tailleBlocW)*3+2];
      k++;
    }
  }
  if(tailleBlocW * nWP >= nWR && tailleBlocH * nHP >= nHR){
    ImgP[(nHP-1)*3*nWP+(nWP-1)*3] = Img[((nHP-1)*tailleBlocH)*3*nWR+((nWP-1)*tailleBlocW)*3];
    ImgP[(nHP-1)*3*nWP+(nWP-1)*3+1] = Img[((nHP-1)*tailleBlocH)*3*nWR+((nWP-1)*tailleBlocW)*3+1];
    ImgP[(nHP-1)*3*nWP+(nWP-1)*3+2] = Img[((nHP-1)*tailleBlocH)*3*nWR+((nWP-1)*tailleBlocW)*3+2];
  }
      

  //ecrire_image_ppm(cNomImgEcrite, ImgP, nHP, nWP);


  /**********************************IMAGE AVEC UN BLOC PAR COULEUR**********************************/

  nHPN = N * nHP;
  nWPN = N * nWP;
  nTaillePN = nHPN * nWPN;
  nTaille3PN = 3 * nTaillePN;
  
  allocation_tableau(ImgOut, OCTET, nTaille3PN);

  k = 0;
  for(int i = 0; i < nHPN; i+=N){
    l = 0;
    for(int j = 0; j < 3*nWPN; j+=3*N){
      for(int x = 0; x < N; x++){
	for(int y = 0; y < N; y++){
	  ImgOut[(i+x)*nWPN*3+j+y*3] = ImgP[k*3*nWP+l];
	  ImgOut[(i+x)*nWPN*3+j+1+y*3] = ImgP[k*3*nWP+l+1];
	  ImgOut[(i+x)*nWPN*3+j+2+y*3] = ImgP[k*3*nWP+l+2];
	}
      }
      l+=3;
    }
    k++;
  }
  
  //ecrire_image_ppm(cNomImgEcrite, ImgOut, nHPN, nWPN);

  free(ImgIn);
  free(ImgCadre);
  free(Img);
  free(ImgP);  
  return 1;
}

