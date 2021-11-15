#include <stdio.h>
#include <math.h>
#include "image_ppm.h"

int main(int argc, char **argv) {

  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, S, S1, S2;
  double ix, iy;
  
  if (argc <= 2)
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
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

       ix = ((ImgIn[(i+1)*nW+j]) - (ImgIn[i*nW+j]));
       iy = ((ImgIn[i*nW+(j+1)]) - (ImgIn[i*nW+j]));        
       ImgOut[i*nW+j] = sqrt((ix * ix) + (iy * iy));

     }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
