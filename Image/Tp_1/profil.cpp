#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250];
  int nH, nW, nTaille;
  int profil[256];  

  for (int i = 0; i < 256; i++)
      profil[i]=0;
  
   int indication;
   int indice;

   if(argc<4){
       printf("Usage wrong \n"); 
       exit (1) ;
   }


   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%d",&indication) ;
   sscanf (argv[3],"%d",&indice) ;

   

   

   OCTET *ImgIn;
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nH = 512;
   nW = 512;
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    if(indication == 1){
        for (int i=0; i < nH; i++){
            profil[ImgIn[indice*nW+i]]++;  
        }
    }
    else{
        for (int i=0; i < nW; i++){
            profil[ImgIn[i*nW+indice]]++;  
        }
    }
std::ofstream outfile("data/profil.dat");


for (int i = 0; i < 256; i++)
{
    outfile<<i<<" "<<profil[i]<<" "<<std::endl;
}
   free(ImgIn);

   return 1;
}
