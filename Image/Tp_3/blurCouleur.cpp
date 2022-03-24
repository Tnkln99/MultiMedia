// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"
#include <iostream>


int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, nR, nG, nB, somR, somV, somB;

    if (argc != 3)
    {
        printf("Wrong Usage \n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);


    OCTET* ImgIn, * ImgOut,* ImgR,* ImgV,* ImgB;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;

    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);


    allocation_tableau(ImgOut, OCTET, nTaille3);


    allocation_tableau(ImgR, OCTET, nTaille);
    allocation_tableau(ImgV, OCTET, nTaille);
    allocation_tableau(ImgB, OCTET, nTaille);


    planR(ImgR, ImgIn, nTaille);
    planB(ImgB, ImgIn, nTaille);
    planV(ImgV, ImgIn, nTaille);

    somR = 0;
    somV = 0;
    somB = 0;
    for (int i = 1; i < nH - 1; i++) {
        for (int j = 1; j < nW - 1; j++)
        {
            somR = (int)ImgR[(i - 1) * nW + j] + (int)ImgR[i * nW + j - 1] + (int)ImgR[i * nW + j] + (int)ImgR[i * nW + j + 1] + (int)ImgR[(i + 1) * nW + j];
            ImgR[i * nW + j] = somR / 5;
            somV = (int)ImgV[(i - 1) * nW + j] + (int)ImgV[i * nW + j - 1] + (int)ImgV[i * nW + j] + ImgV[i * nW + j + 1] + (int)ImgV[(i + 1) * nW + j];
            ImgV[i * nW + j] = somV / 5;
            somB = (int)ImgB[(i - 1) * nW + j] + (int)ImgB[i * nW + j - 1] + (int)ImgB[i * nW + j] + (int)ImgB[i * nW + j + 1] + (int)ImgB[(i + 1) * nW + j];
            ImgB[i * nW + j] = somB / 5;
        }
    }

    for (int i = 0; i < nTaille3; i += 3) {
        ImgOut[i] = ImgR[i / 3];
        ImgOut[i+1] = ImgV[i / 3];
        ImgOut[i + 2] = ImgB[i / 3];

    }

    ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    return 1;
}
