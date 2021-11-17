#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "ImageBase.h"

int main(int argc, char **argv) {

    char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, S, S1, S2;
  
  if (argc <= 3)
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm Seuil\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   sscanf (argv[3],"%d",&S);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);
	
   //   for (int i=0; i < nTaille; i++)
   // {
   //  if ( ImgIn[i] < S) ImgOut[i]=0; else ImgOut[i]=255;
   //  }


 for (int i=0; i < nH; i++)
   for (int j=0; j < nW; j++)
     {       
       ImgOut[i*nW+j] = sqrt((ImgIn[(i+1)*nW+j] * ImgIn[(i+1)*nW+j]) + (ImgIn[i*nW+(j+1)] * ImgIn[i*nW+(j+1)]));
     }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
