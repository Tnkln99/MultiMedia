// test_couleur.cpp : Seuille une image en niveau de gris
#include <iostream>
#include <stdio.h>
#include "image_ppm.h"


int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, cpt, seuilleMoyenne, nombreDeSeuille;



    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    sscanf(argv[3], "%d", &nombreDeSeuille);

    int* tabSeuille = new int[nombreDeSeuille];

    for (int i = 4; i < nombreDeSeuille+4; i++) {
        sscanf(argv[i], "%d", &tabSeuille[i-4]);
    }

    OCTET* ImgIn, * ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nH = 512;
    nW = 512;
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

    std::cout << tabSeuille[nombreDeSeuille] << std::endl;

    
    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            cpt = 1;
            while (!(ImgIn[i * nW + j] >= tabSeuille[cpt - 1] && ImgIn[i * nW + j] <= tabSeuille[cpt])) {
                cpt++;
            }
            seuilleMoyenne = (tabSeuille[cpt - 1] + tabSeuille[cpt]) / 2;
            if (ImgIn[i * nW + j] > tabSeuille[nombreDeSeuille-1]) {
                ImgOut[i * nW + j] = 255;
            }
            else if (ImgIn[i * nW + j] < tabSeuille[0]) {
                ImgOut[i * nW + j] = 0;
            }
            else {
                //std::cout << ImgOut[i * nW + j] << " ";
                ImgOut[i * nW + j] = seuilleMoyenne;
            }
        }
    }



    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn); free(ImgOut);

    return 1;
}
