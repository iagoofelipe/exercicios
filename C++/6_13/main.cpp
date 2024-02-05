/* 

Crie uma classe em C++ chamada Retangulo que armazena as
coordenadas cartesianas dos quatro cantos do retângulo. O construtor chama uma função set
que recebe quatro conjuntos de coordenadas e verifica se cada um deles está no primeiro
quadrante sem que nenhum valor de coordenada x ou y seja maior que 20.0. A função set
também verifica se as coordenadas fornecidas de fato especificam um retângulo. As funções
membro calculam o comprimento, largura, perimetro e area. O comprimento é
maior das duas dimensões. Inclua uma função predicado quadrado, que determina se o
retângulo é um quadrado.

*/

#include <iostream>
#include "Retangulo.h"

using namespace std;
#define CLS() {system("CLS");}
#define P_LINE() {cout << "------------------------------------------------------------------------" << endl;}

int menu(int layout);

int main() {

    int op, preset;
    COORDENADA A, B, C, D;
    
    for(;;op = 0, preset = 0) {
        Retangulo r;
        op = menu(0); // layout inicial

        switch (op) {
            case 1:
                r.setCoordenadas();
                break;
            
            case 2:
                preset = menu(1); // layout de presets
                break;
        }

        if(op == 0)
            break;
        
        switch (preset) {
            case 1:
                A = getCoordenada(5, 15);
                B = getCoordenada(15, 15);
                C = getCoordenada(15, 5);
                D = getCoordenada(5, 5);

                r.setCoordenadas(A, B, C, D);
                break;
            
            case 2:
                A = getCoordenada(1, 3);
                B = getCoordenada(3, 4);
                C = getCoordenada(4, 3);
                D = getCoordenada(2, 2);

                r.setCoordenadas(A, B, C, D);
                break;
        }

        r.displayResult();
    }

    return 0;
}


int menu(int layout) {
    int op;
    do {
        switch (layout) {
            case 1:
                P_LINE();
                cout
                    << "Escolha um preset:\n"
                    << "\t1. Coordenadas A(02, 02) | B(04, 03) | C(03, 04) | D(01, 03)\n"
                    << "\t2. Coordenadas A(05, 15) | B(15, 15) | C(15, 05) | D(05, 05)\n"
                    << "\t0. Sair\n"
                    << "Opcao: ";
                break;
            
            default:
                P_LINE();
                cout
                    << "Analisando retangulos a partir de suas coordenadas\n\n"
                    << "Escolha uma opcao:\n"
                    << "\t1. Inserir coordenadas (X, Y) manualmente\n"
                    << "\t2. Utilizar preset de coordenadas\n"
                    << "\t0. Sair\n\n"
                    << "Opcao: ";
                break;
        }

        cin >> op;
    } while(op < 0 || op > 2);

    return op;
}