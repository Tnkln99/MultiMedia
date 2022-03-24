#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250];
  int nH, nW, nTaille;
  int histo[256];  

  for (int i = 0; i < 256; i++)
      histo[i]=0;
  
  if (argc != 2) {
      std::cout << "wrong usage" << std::endl;
      exit(1);
   }
   sscanf (argv[1],"%s",cNomImgLue) ;
   

   OCTET *ImgIn;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nH = 512;
   nW = 512;
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

for (int i=0; i < nH; i++){
  for (int j=0; j < nW; j++){
      histo[ImgIn[i*nW+j]]++;
  }
}

//std::cout<<"ola";

std::ofstream outfile("data/histo.dat");


for (int i = 0; i < 256; i++)
{
    outfile<<i<<" "<<histo[i]<<" "<<std::endl;
}
   free(ImgIn);

   return 1;
}
