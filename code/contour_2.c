#include <stdio.h>
#include <math.h>
#include "image_ppm.h"

int main(int argc, char **argv) {

  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, S, SB, SH;
  double ix, iy, norme;
  
  if (argc <= 4)
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm SeuilHaut SeuilBas\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   sscanf (argv[3],"%d",&SH);
   sscanf (argv[3],"%d",&SB);

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


   for (int i=1; i < nH - 1; i++) {
     for (int j=1; j < nW - 1; j++) {

       
      if ( ImgIn[i*nW+j] > SH) {
     
         ImgOut[i*nW+j]=255;
      }

      if ( ImgIn[i*nW+j] < SB) {
     
         ImgOut[i*nW+j] = 0;
      }

      if(ImgIn[i*nW+j] > SH || ImgIn[(i+1)*nW+j]  > SH || ImgIn[i*nW+(j+1)]  > SH || ImgIn[(i+1)*nW+(j+1)]  > SH) {
         
         ImgOut[i*nW+j]=255;
      }
  }
}

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
