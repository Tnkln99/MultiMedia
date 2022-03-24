// test_couleur.cpp : Seuille une image en niveau de gris
#include <iostream>
#include <stdio.h>
#include "image_ppm.h"
#include <cmath>


int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, S, S2, x, t;
    float Y;
    const double pi = std::acos(-1);
    if (argc != 5)
    {
        printf("Wrong Usage \n");
        exit(1);
    }


    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    sscanf(argv[3], "%d", &S);
    sscanf(argv[4], "%d", &S2);


    
 

    OCTET* ImgIn, * ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nH = 512;
    nW = 512;
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

  

    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            if (ImgIn[i * nW + j] <= S)
                ImgOut[i * nW + j] = 0;
            else if (ImgIn[i * nW + j] >= S2)
                ImgOut[i * nW + j] = 255;
            else {
                x = ImgIn[i * nW + j];
                t = (x - S) / (S2 - S);
                Y = (std::sin((t * pi / 2) * pi / 180)) * 255;
                if (Y < 0) Y = -1 * Y;
                ImgOut[i * nW + j] = Y;
            }
        }
    }



    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn); free(ImgOut);

    return 1;
}
