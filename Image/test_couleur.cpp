// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"
#include <iostream>


int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nR, nG, nB, S, S2, S3;
  char Indicateur;
  
  if (argc != 6) 
     {
       printf("Wrong Usage \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   sscanf (argv[3],"%d",&S);
   sscanf (argv[4], "%d", &S2);
   sscanf(argv[5], "%d", &S3);


   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nH = 256;
   nW = 256;
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);
	
   for (int i=0; i < nTaille3; i+=3)
     {
       nR = ImgIn[i];
       nG = ImgIn[i+1];
       nB = ImgIn[i+2];
       if (nR < S) ImgOut[i] = 0; else ImgOut[i] = 255;
       if (nG < S2) ImgOut[i+1]=0; else ImgOut[i+1]=255;
       if (nB < S3) ImgOut[i+2]=0; else ImgOut[i+2]=255;
     }

   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}
