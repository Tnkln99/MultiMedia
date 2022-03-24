#include <stdio.h>
#include "image_ppm.h"
#include <iostream>


int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, Gx, Gy;

    if (argc != 3)
    {
        printf("Wrong Usage \n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);

    OCTET* ImgIn, * ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++)
        {
            Gx = -1 * ImgIn[(i - 1) * nW + (j - 1)] + 0 * ImgIn[(i - 1) * nW + j] + ImgIn[(i - 1) * nW + (j + 1)] + -2 * ImgIn[i * nW + (j - 1)] + 0 * ImgIn[i * nW + j] + 2 * ImgIn[i * nW + (j + 1)] + -1 * ImgIn[(i + 1) * nW + (j - 1)] + 0 * ImgIn[(i + 1) * nW + j] + ImgIn[(i + 1) * nW + (j + 1)];
            Gy = -1 * ImgIn[(i - 1) * nW + (j - 1)] + -2 * ImgIn[(i - 1) * nW + j] + -1 * ImgIn[(i - 1) * nW + (j + 1)] + 0 * ImgIn[i * nW + (j - 1)] + 0 * ImgIn[i * nW + j] + 0 * ImgIn[i * nW + (j + 1)] + ImgIn[(i + 1) * nW + (j - 1)] + 2 * ImgIn[(i + 1) * nW + j] + ImgIn[(i + 1) * nW + (j + 1)];
            ImgOut[i * nW + j] = sqrt(pow(Gx, 2) + pow(Gy, 2));
        }
    }


    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn); free(ImgOut);

    return 1;
}
