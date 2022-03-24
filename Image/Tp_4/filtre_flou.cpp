#include <stdio.h>
#include "image_ppm.h"
#include <iostream>



int SommeVoisins8(OCTET* Image, int i, int j, int nH, int nW) {
    int Vkinit, Vkfin, Vpinit, Vpfin, som;



    //std::cout << (int)Image[i * nW + j] << std::endl;

    if (i == 0) { Vkinit = i; Vkfin = i + 1; }
    else if (i == nH) { Vkfin = i; Vkinit = i - 1; }
    else { Vkinit = i - 1; Vkfin = i + 1; }

    //std::cout << Vkinit << " " << Vkfin << std::endl;



    if (j == 0) { Vpinit = j; Vpfin = j + 1; }
    else if (j == nH) { Vpfin = j; Vpinit = j - 1; }
    else { Vpinit = j - 1; Vpfin = j + 1; }

    //std::cout << Vpinit << " " << Vpfin << std::endl;

    som = 0;
    for (int k = Vkinit; k <= Vkfin; k++) {
        for (int p = Vpinit; p <= Vpfin; p++) {
            som = (int)Image[k * nW + p] + som;
        }
    }
    return som/9;
}


int SommeVoisins24(OCTET* Image, int i, int j, int nH, int nW) {
    int Vkinit, Vkfin, Vpinit, Vpfin, som;



    //std::cout << (int)Image[i * nW + j] << std::endl;

    if (i == 0) { Vkinit = i; Vkfin = i + 2; }
    else if (i == nH) { Vkfin = i; Vkinit = i - 2; }
    else if (i == 1) { Vkinit = i - 1; Vkfin = i + 2; }
    else { Vkinit = i - 2; Vkfin = i + 2; }

    //std::cout << Vkinit << " " << Vkfin << std::endl;



    if (j == 0) { Vpinit = j; Vpfin = j + 2; }
    else if (j == nH) { Vpfin = j; Vpinit = j - 2; }
    else if(j == 1) { Vpinit = j - 1; Vpfin = j + 2; }
    else { Vpinit = j - 2; Vpfin = j + 2; }

    //std::cout << Vpinit << " " << Vpfin << std::endl;

    som = 0;
    for (int k = Vkinit; k <= Vkfin; k++) {
        for (int p = Vpinit; p <= Vpfin; p++) {
            som = (int)Image[k * nW + p] + som;
        }
    }
    return som / 25;
}
int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, typeDeBlur, som;

    if (argc != 4)
    {
        printf("Wrong Usage \n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    sscanf(argv[3], "%d", &typeDeBlur);

    OCTET* ImgIn, * ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

    if (typeDeBlur == 2) {
        for (int i = 0; i < nH; i++) {
            for (int j = 0; j < nW; j++)
            {
                ImgOut[i * nW + j] = SommeVoisins8(ImgIn, i, j, nH, nW);
            }
        }
    }
    else if (typeDeBlur == 1) {
        //std::cout << "ola"<<std::endl;
        som = 0;
        for (int i = 0; i < nTaille; i++)
            ImgOut[i] = ImgIn[i];
        for (int i = 1; i < nH-1; i++) {
            for (int j = 1; j < nW-1; j++)
            {
                som = ImgIn[(i - 1) * nW + j] + ImgIn[i * nW + j - 1] + ImgIn[i * nW + j] + ImgIn[i * nW + j + 1] + ImgIn[(i + 1) * nW + j];
                ImgOut[i * nW + j] = som / 5;
            }
        }
    }
    else if (typeDeBlur == 3) {
        for (int i = 0; i < nH; i++) {
            for (int j = 0; j < nW; j++)
            {
                ImgOut[i * nW + j] = (int)SommeVoisins24(ImgIn, i, j, nH, nW);
            }
        }
    }
    else {
        std::cout << "wrong usage of type de blur" << std::endl;
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn); free(ImgOut);

    return 1;
}
