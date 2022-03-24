#include <stdio.h>
#include <iostream>
#include "image_ppm.h"

int maxIntensiteVosisin(OCTET* Image, int i, int j, int nH, int nW) {
    int Vkinit, Vkfin, Vpinit, Vpfin, max;

    if (i == 0) { Vkinit = i; Vkfin = i + 1; }
    else if (i == nH) { Vkfin = i; Vkinit = i - 1; }
    else { Vkinit = i - 1; Vkfin = i + 1; }

    if (j == 0) { Vpinit = j; Vpfin = j + 1; }
    else if (j == nH) { Vpfin = j; Vpinit = j - 1; }
    else { Vpinit = j - 1; Vpfin = j + 1; }

    max = 0;
    for (int k = Vkinit; k <= Vkfin; k++) {
        for (int p = Vpinit; p <= Vpfin; p++) {
            if ((int)Image[k * nW + p] > max) {
                max = (int)Image[k * nW + p];
            }
        }
    }
    return max;
}

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;

    if (argc != 3)
    {
        printf("Wrong Usage \n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);

    OCTET* ImgIn, * ImgOut, * ImgR, * ImgV, * ImgB,* T_R,* T_V,* T_B; //T stands for temporary.

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);

    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;

    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nTaille);


    allocation_tableau(ImgOut, OCTET, nTaille3);


    allocation_tableau(ImgR, OCTET, nTaille);
    allocation_tableau(ImgV, OCTET, nTaille);
    allocation_tableau(ImgB, OCTET, nTaille);


    planR(ImgR, ImgIn, nTaille);
    planB(ImgB, ImgIn, nTaille);
    planV(ImgV, ImgIn, nTaille);

    allocation_tableau(T_R, OCTET, nTaille);
    allocation_tableau(T_V, OCTET, nTaille);
    allocation_tableau(T_B, OCTET, nTaille);

   
    //blach = arka plan
    //noir = objet

    //dilatation eger beyaz komsusu varsa o da beyaz oluyo obje büyüyo. 
    //erosion eger siyah komsusu varsa o da siyah oluyo obejet küçülüyo

    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++)
        {
            T_R[i * nW + j] = maxIntensiteVosisin(ImgR, i, j, nH, nW);
            T_B[i * nW + j] = maxIntensiteVosisin(ImgB, i, j, nH, nW);
            T_V[i * nW + j] = maxIntensiteVosisin(ImgV, i, j, nH, nW);
        }
    }

    for (int i = 0; i < nTaille3; i += 3) {
        ImgOut[i] = T_R[i / 3];
        ImgOut[i + 1] = T_V[i / 3];
        ImgOut[i + 2] = T_B[i / 3];
    }

    ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn); free(ImgOut);

    return 1;
}
