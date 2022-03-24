#include <stdio.h>
#include "image_ppm.h"
#include <fstream>

int main(int argc, char* argv[])
{
  char cNomImgLue[250];
  int nH, nW, nTaille, nR, nG, nB, S;
  int histoC[256][3];

  for(int i=0; i < 256;i++){
      for (int j =0; j<3;j++){
          histoC[i][j] = 0;
      }
  }
   
   sscanf (argv[1],"%s",cNomImgLue) ;

   OCTET *ImgIn;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nH = 256;
   nW = 256;
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
	
   for (int i=0; i < nTaille3; i+=3)
    {
       nR = ImgIn[i];
       nG = ImgIn[i+1];
       nB = ImgIn[i+2];
       histoC[nR][0]++;
       histoC[nG][1]++;
       histoC[nB][2]++;
    }

std::ofstream outfile("data/histoC.dat");


for (int i = 0; i < 256; i++)
{
    outfile<<i;
    for(int j = 0; j < 3; j++){
        outfile<<" "<<histoC[i][j];
    }
    outfile<<"\n";
}
   free(ImgIn);

   return 1;
}