import math
from typing import Tuple, Iterable

Coordenada = Tuple[float, float]

PI = 3.14159265358979323846
STRING_SIZE = 60
STRING_RESULT_SIZE = 40
STRING_SPACER = ' '

# ANSI colors
BLUE = "\033[34m"
GREEN = "\033[32m"
RED = "\033[31m"
NORMAL = "\033[m"

class Retangulo:
    error = False
    __primeiroQuadrante = False
    __verticesDiferentes = False
    __ladosParalelos = False
    __distInternasEquivalentes = False
    __isRet = False

    __coordenadas:Tuple[Coordenada] = None
    __A:Coordenada = None
    __B:Coordenada = None
    __C:Coordenada = None
    __D:Coordenada = None

    __distancias = dict(AB=0.0, BC=0.0, CD=0.0, DA=0.0)

    def __init__(self, matriz) -> None:
        self.__ordem = 20

    def __getCoorByIndex(self, __index:int) -> Coordenada:
        if __index < 0 or __index > 3:
            raise IndexError("indice fora do range [0:3]")
        values = [self.__A, self.__B, self.__C, self.__D]
        return values[__index]

    def __showMsg(self, msg:str, v:bool=None) -> None:
        if v == None:
            print(BLUE, "[PROCESS]", NORMAL, msg.ljust(STRING_SIZE, STRING_SPACER), end="")
        else:
            color = GREEN if v else RED
            print(BLUE, msg.ljust(STRING_RESULT_SIZE, STRING_SPACER), color, v, NORMAL)

    def __showPassed(self) -> None:
        print(GREEN, "Passed", NORMAL)
    
    def __showError(self, msg:str=None) -> None:
        if msg:
            print(RED, "Error\n", msg, NORMAL)
        else:
            print(RED, "Error", NORMAL)

        self.error = True

    def __calcDistancia(self, p1:Coordenada, p2:Coordenada) -> float:
        """ calcula a distância entre dois pontos """
        return math.sqrt(pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2))

    def __orderCoordenadas(self) -> None:
        """ organiza os pontos do retângulo, evitando erros nos cálculos """
        """ 
        Representação do retângulo para as coordenadas
    
        supEsq (A)  - menor X e maior Y
        maior (B)   - maior X e maior Y
        infDir (C)  - maior X e menor Y
        menor (D)   - menor X e menor Y

        supEsq (A)         maior (B)
        -------------------
        |                 |
        |                 |
        |                 |
        -------------------
        menor (D)        infDir (C)
        """
        menor, maior, supEsq, infDir = 0, 0, 0, 0

        menorX = self.__coordenadas[0][0]
        maiorX = self.__coordenadas[0][0]
        menorY = self.__coordenadas[0][1]
        maiorY = self.__coordenadas[0][1]

        for i, (x, y) in enumerate(self.__coordenadas):
            # separando menor
            if x <= menorX and y <= menorY:
                menorX = x
                menorY = y
                menor = i
            
            # separando maior
            if x >= maiorX and y >= maiorY:
                maiorX = x
                maiorY = y
                maior = i

        # separando superior esquerdo e inferior direito
        ops = []
        for i in range(4):
            if i not in (maior, menor):
                ops.append(i)
            
        if self.__coordenadas[ops[0]][0] < self.__coordenadas[ops[1]][0]: # se X do primeiro valor que nao foi menor nem maior for menor que X do outro valor que nao foi menor nem maior
            supEsq = ops[0]
            infDir = ops[1]
        else:
            supEsq = ops[1]
            infDir = ops[0]
        
        # atribuindo valores corretos
        self.__A = self.__coordenadas[supEsq]
        self.__B = self.__coordenadas[maior]
        self.__C = self.__coordenadas[infDir]
        self.__D = self.__coordenadas[menor]


    # verifica se cada coordenada está no primeiro quadrante sem que x ou y seja maior que a ordem da matriz
    def __checkCoordenadas(self) -> bool:
        for c in self.__coordenadas:
            if c[0] <= 0 or c[0] > self.__ordem or c[1] <= 0 or c[1] > self.__ordem:
                return False
        return True


    # verifica se há coordenadas iguais
    def __checkDupliCoordenadas(self) -> bool:
        for i in range(4):
            x1, y1 = self.__getCoorByIndex(i)
            for j in range(4):
                x2, y2 = self.__getCoorByIndex(i)
                if i == j:
                    continue
                if x1 == x2 and y1 == y2:
                    return True
        return False


    # verifica se forma um retângulo (4 ângulos retos internamente)
    def __isRetangulo(self) -> bool:
        AB = self.__calcDistancia(self.__A, self.__B)
        BC = self.__calcDistancia(self.__B, self.__C)
        CD = self.__calcDistancia(self.__C, self.__D)
        DA = self.__calcDistancia(self.__D, self.__A)
        AC = self.__calcDistancia(self.__A, self.__C) # distancia interna
        BD = self.__calcDistancia(self.__B, self.__D) # distancia interna

        self.__distancias["AB"] = AB
        self.__distancias["BC"] = BC
        self.__distancias["CD"] = CD
        self.__distancias["DA"] = DA
        self.__distancias["AC"] = AC # distancia interna
        self.__distancias["BD"] = BD # distancia interna

        self.__showMsg("verificando angulos internos...")
        angs = [
            self.getAngulo(self.__A, self.__B, self.__D), # A
            self.getAngulo(self.__B, self.__C, self.__A), # B
            self.getAngulo(self.__C, self.__D, self.__B), # C
            self.getAngulo(self.__D, self.__A, self.__C)  # D
        ]

        for ang in angs:
            # evitando falso positivo por impresição do cálculo (margem de erro)
            if ang < 90 or ang >= 91:
                self.__showError("Angulos internos diferentes de 90 graus")
                print("A:", angs[0])
                print("B:", angs[1])
                print("C:", angs[2])
                print("D:", angs[3])
                return False
        
        self.__showPassed()
        self.__showMsg("verificando se possui lados paralelos...")
        if AB != CD or DA != BC: # impossível formar angulo de 90 graus com lados não paralelos
            self.__showError("Nao possui lados paralelos")
            return False
        
        self.__ladosParalelos = True
        self.__showPassed()
        
        self.__showMsg("verificando se distancias internas sao equivalentes...")
        if AC != BD:
            self.__showError("Distancias internas distintas")
            return False

        self.__distInternasEquivalentes = True
        self.__showPassed()

        self.__isRet = True
        return True


    # armazena as coordenadas
    def setCoordenadas(self, *coordenadas:Coordenada) -> None:
        if not coordenadas:
            coordenadas = []
            for i in ("A", "B", "C", "D"):
                print(f"\nCoordenadas {i}")
                coordenadas.append([float(input("\tX: ")), float(input("\tY: "))])
        
        self.__coordenadas = coordenadas

        self.__showMsg("verificando quadrante...")
        if not self.__checkCoordenadas():
            self.__showError("O retangulo nao esta no primeiro quadrante ou possui valores maiores que 20!")
            return
        
        self.__primeiroQuadrante = True
        self.__showPassed()

        self.__showMsg("ordenando coordenadas...")
        self.__orderCoordenadas()
        self.__showPassed()

        self.__showMsg("verificando pontos iguais...")
        if not self.__checkDupliCoordenadas():
            self.__showError("O retangulo possui vertices iguais, invalidando sua existencia!")
            return
        
        self.__verticesDiferentes = True
        self.__showPassed()

        self.__isRetangulo()


    # exibe as coordenadas do retângulo
    def displayCoordenadas(self) -> None:
        print(BLUE, "A ", GREEN, tuple(self.__A), NORMAL)
        print(BLUE, "B ", GREEN, tuple(self.__B), NORMAL)
        print(BLUE, "C ", GREEN, tuple(self.__C), NORMAL)
        print(BLUE, "D ", GREEN, tuple(self.__D), NORMAL)

    # exibe descrição do retângulo
    def displayResult(self) -> None:
        print("\nResultados encontrados")

        self.__showMsg("Primeiro quadrante:", self.__primeiroQuadrante)
        self.__showMsg("Vertices diferentes:", self.__verticesDiferentes)
        self.__showMsg("Lados paralelos:", self.__ladosParalelos)
        self.__showMsg("Distancias internas equivalentes:", self.__distInternasEquivalentes)
        self.__showMsg("E um retangulo:", self.__isRet)

        # if not isRet:
        #     return

        print("\nMedidas")
        print(BLUE, "Area:      ", GREEN, self.getArea(), NORMAL)
        print(BLUE, "Perimetro: ", GREEN, self.getPerimetro(), NORMAL)

        print("\nComprimento dos Lados")
        print(BLUE, "AB: ", GREEN, self.__distancias["AB"], NORMAL)
        print(BLUE, "BC: ", GREEN, self.__distancias["BC"], NORMAL)
        print(BLUE, "CD: ", GREEN, self.__distancias["CD"], NORMAL)
        print(BLUE, "DA: ", GREEN, self.__distancias["DA"], NORMAL)

        print("\nCoordenadas dos vertices")
        self.displayCoordenadas()

    def getPerimetro(self) -> float:
        return sum(tuple(self.__distancias.values())[:4])

    def getArea(self) -> float:
        return self.__distancias["CD"] *  self.__distancias["BC"]
    
    # calcula o angulo beta dos pontos ABC (angulo de B)
    def getAngulo(self, A:Coordenada, B:Coordenada, C:Coordenada) -> float:
        a = self.__calcDistancia(B, C)
        b = self.__calcDistancia(A, C)
        c = self.__calcDistancia(B, A)

        angRad = math.acos((pow(a, 2) - pow(b, 2) - pow(c, 2)) / (-2 * b * c))

        return (angRad * 180 / PI)