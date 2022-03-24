// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"

bool existeVoisins255(OCTET* ImgOut, int i, int j, int nH, int nW) {
    int Vkinit, Vkfin, Vpinit, Vpfin;   

    if (i == 0) { Vkinit = i; Vkfin = i + 1; }
    else if (i == nH) { Vkfin = i; Vkinit = i - 1; }
    else { Vkinit = i - 1; Vkfin = i + 1; }

    if (j == 0) { Vpinit = j; Vpfin = j + 1; }
    else if (j == nH) { Vpfin = j; Vpinit = j - 1; }
    else { Vpinit = j - 1; Vpfin = j + 1; }

    
    for (int k = Vkinit; k <= Vkfin; k++) {
        for (int p = Vpinit; p <= Vpfin; p++) {
            if ((int)ImgOut[i * nW + j] == 255) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, S, S1;

    if (argc != 5)
    {
        printf("Usage: ImageIn.pgm ImageOut.pgm Seuil Seui2 \n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    sscanf(argv[3], "%d", &S);
    sscanf(argv[4], "%d", &S1);

    OCTET* ImgIn, * ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);


    for (int i = 0; i < nH; i++)
        for (int j = 0; j < nW; j++)
        {
            if (ImgIn[i * nW + j] <= S) ImgOut[i * nW + j] = 0;
            else if (ImgIn[i * nW + j] >= S1) ImgOut[i * nW + j] = 255;
            else ImgOut[i * nW + j] = ImgIn[i * nW + j];
        }

    for (int i = 0; i < nH; i++)
        for (int j = 0; j < nW; j++)
        {
            if ((ImgOut[i * nW + j] > S && ImgOut[i * nW + j] < S1 && existeVoisins255(ImgOut, i, j, nH, nW)) || ImgOut[i * nW + j] == 255) {
                ImgOut[i * nW + j] = 255;
            }
            else {
                ImgOut[i * nW + j] = 0;
            }
        }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn); free(ImgOut);

    return 1;
}
