// test_couleur.cpp : Seuille une image en niveau de gris

#include <stdio.h>
#include "image_ppm.h"
#include <iostream>

int main(int argc, char* argv[])
{
    char cNomImgSeuille[250], cNomImgDilate[250], cNomImgEcrite[250];
    int nH, nW, nTaille, S;
    float somM_2;

    if (argc != 4)
    {
        printf("Wrong Usage \n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgSeuille);
    sscanf(argv[2], "%s", cNomImgDilate);
    sscanf(argv[3], "%s", cNomImgEcrite);

    OCTET *ImgSeuille, *ImgDilat, *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgSeuille, &nH, &nW);
    lire_nb_lignes_colonnes_image_pgm(cNomImgDilate, &nH, &nW);//ils sont la meme taille donc ca passe.
    nTaille = nH * nW;

    allocation_tableau(ImgSeuille, OCTET, nTaille);
    allocation_tableau(ImgDilat, OCTET, nTaille);

    lire_image_pgm(cNomImgSeuille, ImgSeuille, nH * nW);
    lire_image_pgm(cNomImgDilate, ImgDilat, nH * nW);

    allocation_tableau(ImgOut, OCTET, nTaille);

    somM_2 = 0;
    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++){
            if (ImgSeuille[i * nW + j] == 255 && ImgDilat[i * nW + j] == ImgSeuille[i * nW + j]) {
                ImgOut[i * nW + j] = 255;
            }
            else if (ImgSeuille[i * nW + j] == 0 && ImgDilat[i * nW + j] == ImgSeuille[i * nW + j]) {
                ImgOut[i * nW + j] = 255;
            }
            else {
                ImgOut[i * nW + j] = 0;
                somM_2 += 0.0625;
            }
        }
    }

    std::cout << "forest lost is: " << somM_2 << " km^2" << std::endl;

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgSeuille); free(ImgDilat);  free(ImgOut);

    return 1;
}
