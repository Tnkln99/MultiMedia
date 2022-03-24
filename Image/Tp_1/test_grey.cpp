// test_couleur.cpp : Seuille une image en niveau de gris
#include <iostream>
#include <stdio.h>
#include "image_ppm.h"


int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, S, S2, S3;
  //std::cout << argc << std::endl;
  if (argc != 4)
     {
       printf("Wrong Usage \n");
       exit (1) ;
     }
  
  
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   sscanf (argv[3],"%d",&S);
   /*sscanf(argv[4], "%d", &S2);
   sscanf(argv[5], "%d", &S3);*/

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nH = 512;
   nW = 512;
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);
	
   //   for (int i=0; i < nTaille; i++)
   // {
   //  if ( ImgIn[i] < S) ImgOut[i]=0; else ImgOut[i]=255;
   //  }


for (int i = 0; i < nH; i++)
  for (int j=0; j < nW; j++)
    if (ImgIn[i * nW + j] < S) {
          ImgOut[i * nW + j] = 0;
    }
    else {
          ImgOut[i * nW + j] = 255;
    }
/*
for (int i = 0; i < nH; i++) {
  for (int j=0; j < nW; j++){
    if (ImgIn[i*nW+j] < S) 
      ImgOut[i*nW+j]=10;
    else if (ImgIn[i*nW+j] < S2)
      ImgOut[i*nW+j]=150; 
    else 
      ImgOut[i*nW+j]=255;
  }
}

for (int i = 0; i < nH; i++) {
    for (int j = 0; j < nW; j++) {
        if (ImgIn[i * nW + j] < S)
            ImgOut[i * nW + j] = 10;
        else if (ImgIn[i * nW + j] < S2)
            ImgOut[i * nW + j] = 150;
        else if (ImgIn[i * nW + j] < S3)
            ImgOut[i * nW + j] = 200;
        else 
            ImgOut[i * nW + j] = 255;
    }
}*/
  
  
  
   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

   return 1;
}
