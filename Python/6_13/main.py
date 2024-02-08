""" 
Crie uma classe em C++ chamada Retangulo que armazena as
coordenadas cartesianas dos quatro cantos do retângulo. O construtor chama uma função set
que recebe quatro conjuntos de coordenadas e verifica se cada um deles está no primeiro
quadrante sem que nenhum valor de coordenada x ou y seja maior que 20.0. A função set
também verifica se as coordenadas fornecidas de fato especificam um retângulo. As funções
membro calculam o comprimento, largura, perimetro e area. O comprimento é
maior das duas dimensões. Inclua uma função predicado quadrado, que determina se o
retângulo é um quadrado.

"""

from retangulo import Retangulo
LINE = "------------------------------------------------------------------------"

def menu(layout: int) -> None:
    op = -1
    while True:
        match layout:
            case 1:
                print(
                    LINE,
                    "Escolha um preset:",
                    "\t1. Coordenadas A(02, 02) | B(04, 03) | C(03, 04) | D(01, 03)",
                    "\t2. Coordenadas A(05, 15) | B(15, 15) | C(15, 05) | D(05, 05)",
                    "\t0. Sair", "",
                    sep="\n"
                )

            case _:
                print(
                    LINE,
                    "Analisando retangulos a partir de suas coordenadas", "",
                    "Escolha uma opcao:",
                    "\t1. Inserir coordenadas (X, Y) manualmente",
                    "\t2. Utilizar preset de coordenadas",
                    "\t0. Sair", "",
                    sep="\n"
                )

        op = input("Opcao: ")
        
        if not op.isdigit():
            continue

        op = int(op)
        if layout == 1 and op in (0,1,2):
            return op

def main():
    r = Retangulo(20)
    op = None

    while True:
        preset = None
        op = menu(0) # layout inicial

        match op:
            case 0:
                return
            
            case 1:
                r.setCoordenadas()

            case 2:
                preset = menu(1) # layout de presets

        match preset:
            case 1:
                A = (5, 15)
                B = (15, 15)
                C = (15, 5)
                D = (5, 5)
                r.setCoordenadas(A, B, C, D)

            case 2:
                A = (1, 3)
                B = (3, 4)
                C = (4, 3)
                D = (2, 2)
                r.setCoordenadas(A, B, C, D)

        r.displayResult()

if __name__ == "__main__":
    main()