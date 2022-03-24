// test_couleur.cpp : Seuille une image en niveau de gris
#include <iostream>
#include <stdio.h>
#include "image_ppm.h"


int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;
    int histo[256];
    int sum, sumB, a1, a2, b1, b2, var_max, S = 0;
    float variance;

    for (int i = 0; i < 256; i++)
        histo[i] = 0;


    if (argc != 3)
    {
        printf("Wrong Usage \n");
        exit(1);
    }


    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);

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
            histo[ImgIn[i * nW + j]]++;
        }
    }


    for (int i = 0; i < 256; i++) {
        sum += i * histo[i];
    }

    for (int j = 0; j < 256; j++) {
        a1 += histo[j];
        if (a1 == 0) {
            continue;
        }
        a2 = nTaille - a1;

        sumB += j * histo[j];
        b1 = sumB / a1;
        b2 = (sum - sumB) / a2;

        variance = a1 * a2 * ((b1 - b2) * (b1 - b2));

        if (variance > var_max) {
            S = j;
            var_max = variance;
        }
    }

    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            if (ImgIn[i * nW + j] > S)
                ImgOut[i * nW + j] = 255;
            else 
                ImgOut[i * nW + j] = 0;
        }
    }


   



    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn); free(ImgOut);

    return 1;
}
