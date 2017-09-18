#include <iostream>
#include "CNTree.h"

using namespace std;

int main()
{
    int **a_lo_bruto;
    a_lo_bruto = new int *[8];
    for(int i=0;i<8;i++)
        a_lo_bruto[i] = new int[8];

    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            a_lo_bruto[i][j] =0;
        }
    a_lo_bruto[0][1] = 1;
    a_lo_bruto[0][3] = 1;    a_lo_bruto[0][5] = 1;    a_lo_bruto[0][7] = 1;    a_lo_bruto[1][0] = 1;    a_lo_bruto[1][2] = 1;    a_lo_bruto[1][4] = 1;    a_lo_bruto[1][6] = 1;    a_lo_bruto[2][1] = 1;    a_lo_bruto[2][3] = 1;    a_lo_bruto[2][5] = 1;    a_lo_bruto[2][7] = 1;
    a_lo_bruto[5][0] = 2;    a_lo_bruto[5][2] = 2; // 5 2    a_lo_bruto[5][4] = 2;    a_lo_bruto[5][6] = 2; //5 6    a_lo_bruto[6][1] = 2;    a_lo_bruto[6][3] = 2;    a_lo_bruto[6][5] = 2;    a_lo_bruto[6][7] = 2;    a_lo_bruto[7][0] = 2;    a_lo_bruto[7][2] = 2;    a_lo_bruto[7][4] = 2;    a_lo_bruto[7][6] = 2;
    CNTree prueba1(a_lo_bruto,6,1);
    prueba1.natalidad(prueba1.c_root);
    //prueba1.imprimirComportamiento(prueba1.c_root);


    int neo = prueba1.camino(prueba1.c_root);

    prueba1.c_root->c_hijos[neo]->imprimir_tablero();
    //prueba1.imprimirComportamiento(prueba1.c_root->c_hijos[0]->c_hijos[0]);


    return 0;
}
