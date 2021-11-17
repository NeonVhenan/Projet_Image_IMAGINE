#include "image_ppm.h"
#include <string.h>
#include <stdlib.h>


void usage(char * s){
  printf("Usage : %s ImageIn.pgm ImageOut.pgm\n", s);
}


int distance(int i, int j){
  if(i > j)
    return i - j;
  return j - i;
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
  int tailleBloc, valMoy, valMoyI, valMoyJ;
  
  
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
  while(ImgIn[k*nW*3+l] > 7 || ImgIn[k*nW*3+l+1] > 7 || ImgIn[k*nW*3+l+2] > 7){
    l+=3;
    if(l >= nW){
      l = 0;
      k++;
    }
  }

  xp1 = k;
  yp1 = l;

  k = xp1;
  l = yp1;
  while(ImgIn[k*nW*3+l] <= 7 && ImgIn[k*nW*3+l+1] <= 7 && ImgIn[k*nW*3+l+2] <= 7){
    l+=3;
  }

  xp2 = k;
  yp2 = l-1;

  k = xp1;
  l = yp1;
  while(ImgIn[k*nW*3+l] <= 7 && ImgIn[k*nW*3+l+1] <= 7 && ImgIn[k*nW*3+l+2] <= 7){
    k++;
  }

  xp3 = k-1;
  yp3 = l;

  nHC = xp3 - xp1;
  nWC = (yp2 - yp1)/3;
  nTailleC = nHC * nWC;
  nTaille3C = 3* nTailleC;

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
  while(ImgCadre[k*nWC*3+l] <= 7 && ImgCadre[k*nWC*3+l+1] <= 7 && ImgCadre[k*nWC*3+l+2] <= 7){
    l+=3;
    if(l >= nWC){
      l = 0;
      k++;
    }
  }

  xp1 = k+1;
  yp1 = l;

  k = xp1;
  l = nWC*3-3;
  while(ImgCadre[k*nWC*3+l] <= 7 && ImgCadre[k*nWC*3+l+1] <= 7 && ImgCadre[k*nWC*3+l+2] <= 7){
    l-=3;
  }

  xp2 = k;
  yp2 = l;

  k = nHC-1;
  l = yp1;
  while(ImgCadre[k*nWC*3+l] <= 7 && ImgCadre[k*nWC*3+l+1] <= 7 && ImgCadre[k*nWC*3+l+2] <= 7){
    k--;
  }

  xp3 = k-1;
  yp3 = l;


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

  //ecrire_image_ppm(cNomImgEcrite, Img, nHR, nWR);

  k = nHC-1;
  l = 3*(nWC-1);
  
  while(ImgCadre[k*nWC*3+l] > 7 && ImgCadre[k*nWC*3+l+1] > 7 && ImgCadre[k*nWC*3+l+2] > 7){
    l-=3;
  }

  k = nHC-1;
  while(ImgCadre[k*nWC*3+l] <= 7 && ImgCadre[k*nWC*3+l+1] <= 7 && ImgCadre[k*nWC*3+l+2] <= 7){
    k--;
  }
  printf("%d, %d\n", l, k);

  tailleBloc = k-1;
  while(ImgCadre[k*nWC*3+l] > 7 && ImgCadre[k*nWC*3+l+1] > 7 && ImgCadre[k*nWC*3+l+2] > 7){
    k--;
  }
  

  tailleBloc = tailleBloc - k;
  printf("taille bloc : %d\n", tailleBloc);



  /**********************************IMAGE AVEC UN PIXEL PAR COULEUR**********************************/

  nHP = nHR/tailleBloc;
  if(nHR % tailleBloc != 0)
    nHP++;   
  nWP = nWR/tailleBloc;
  if(nWR % tailleBloc != 0)
    nWP++;
  
  if(tailleBloc % 2 == 0)
    valMoy = tailleBloc/2;
  else
    valMoy = (tailleBloc+1)/2;
  
  printf("%d, %d\n", nHP, nWP);
  nTailleP = nHP * nWP;
  nTaille3P = 3 * nTailleP;

  int cpH = 0;
  int cpW = 0;

  allocation_tableau(ImgP, OCTET, nTaille3P);

  k = 0;
  for(int i = 0; i+tailleBloc < nHR ; i+=tailleBloc){
    l = 0;
    for(int j = 0; j+3*tailleBloc < nWR*3; j+=3*tailleBloc){
      ImgP[k*3*nWP+l] = Img[(i+valMoy)*3*nWR+j+valMoy*3];
      ImgP[k*3*nWP+l+1] = Img[(i+valMoy)*3*nWR+j+1+valMoy*3];
      ImgP[k*3*nWP+l+2] = Img[(i+valMoy)*3*nWR+j+2+valMoy*3];
      l+=3;
    }
    k++;
  }
  
  if(tailleBloc * nHP > nHR){
    l = 0;
    if((tailleBloc * nHP - nHR)%2 == 0)
      valMoyI = (tailleBloc * nHP - nHR)/2;
    else
      valMoyI = (tailleBloc * nHP - nHR + 1)/2;
    for(int j = 0; j+3*tailleBloc < nWR*3; j+=3*tailleBloc){
      ImgP[(nHP-1)*3*nWP+l] = Img[((nHP-1)*tailleBloc+valMoyI)*3*nWR+j+valMoy*3];
      ImgP[(nHP-1)*3*nWP+l+1] = Img[((nHP-1)*tailleBloc+valMoyI)*3*nWR+j+1+valMoy*3];
      ImgP[(nHP-1)*3*nWP+l+2] = Img[((nHP-1)*tailleBloc+valMoyI)*3*nWR+j+2+valMoy*3];
      l+=3;
    }
  }
  if(tailleBloc * nWP > nWR){
    k = 0;
    if((tailleBloc * nWP - nWR)%2 == 0)
      valMoyJ = (tailleBloc * nWP - nHR)/2;
    else
      valMoyJ = (tailleBloc * nHP - nHR + 1)/2;
    for(int i = 0; i+tailleBloc < nHR; i+=tailleBloc){
      ImgP[k*3*nWP+(nWP-1)*3] = Img[(i+valMoy)*3*nWR+(((nWP-1)*tailleBloc)+valMoyJ)*3];
      ImgP[k*3*nWP+(nWP-1)*3+1] = Img[(i+valMoy)*3*nWR+(((nWP-1)*tailleBloc)+valMoyJ)*3+1];
      ImgP[k*3*nWP+(nWP-1)*3+2] = Img[(i+valMoy)*3*nWR+(((nWP-1)*tailleBloc)+valMoyJ)*3+2];
      k++;
    }
  }
  if(tailleBloc * nWP > nWR && tailleBloc * nHP > nHR){
    if((tailleBloc * nHP - nHR)%2 == 0)
      valMoyI = (tailleBloc * nHP - nHR)/2;
    else
      valMoyI = (tailleBloc * nHP - nHR + 1)/2;
    if((tailleBloc * nWP - nWR)%2 == 0)
      valMoyJ = (tailleBloc * nWP - nHR)/2;
    else
      valMoyJ = (tailleBloc * nHP - nHR + 1)/2;

    ImgP[(nHP-1)*3*nWP+(nWP-1)*3] = Img[((nHP-1)*tailleBloc+valMoyI)*3*nWR+(((nWP-1)*tailleBloc)+valMoyJ)*3];
    ImgP[(nHP-1)*3*nWP+(nWP-1)*3+1] = Img[((nHP-1)*tailleBloc+valMoyI)*3*nWR+(((nWP-1)*tailleBloc)+valMoyJ)*3+1];
    ImgP[(nHP-1)*3*nWP+(nWP-1)*3+2] = Img[((nHP-1)*tailleBloc+valMoyI)*3*nWR+(((nWP-1)*tailleBloc)+valMoyJ)*3+2];
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
  
  ecrire_image_ppm(cNomImgEcrite, ImgOut, nHPN, nWPN);

  free(ImgIn);
  free(ImgCadre);
  free(Img);
  free(ImgP);  
  return 1;
}

