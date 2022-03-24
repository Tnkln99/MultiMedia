#include <stdio.h>
#include <iostream>
#include "image_ppm.h"

bool existVosisinBlanc(OCTET* Image, int i, int j,int nH,int nW) {
    int Vkinit, Vkfin, Vpinit,Vpfin;

    

    //std::cout << (int)Image[i * nW + j] << std::endl;

    if (i == 0) {Vkinit = i; Vkfin = i + 1;}
    else if (i == nH) { Vkfin = i; Vkinit = i - 1; }
    else { Vkinit = i - 1; Vkfin = i + 1; }

    //std::cout << Vkinit << " " << Vkfin << std::endl;



    if (j == 0) { Vpinit = j; Vpfin = j + 1; }
    else if (j == nH) { Vpfin = j; Vpinit = j - 1; }
    else { Vpinit = j - 1; Vpfin = j + 1; }

    //std::cout << Vpinit << " " << Vpfin << std::endl;


    for (int k = Vkinit; k <= Vkfin; k++) {
        for (int p = Vpinit; p <= Vpfin; p++) {
            if ((int)Image[k * nW + p] == 255) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, S;

    int voisins[3][3];

    if (argc != 3)
    {
        printf("Wrong Usage \n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    //sscanf(argv[3], "%d", &S);

    OCTET* ImgIn, * ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);
    //blach = arka plan
    //noir = objet

    //dilatation eger beyaz komsusu varsa o da beyaz oluyo obje büyüyo. 
    //erosion eger siyah komsusu varsa o da siyah oluyo obejet küçülüyo

    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++)
        {
            if (existVosisinBlanc(ImgIn,i,j,nH,nW)) {
                //std::cout << "entrer" << std::endl;
                ImgOut[i * nW + j] = 255;
            }
            else {
                ImgOut[i * nW + j] = 0;
            }
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn); free(ImgOut);

    return 1;
}
