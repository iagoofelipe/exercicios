class Matriz:
    MAX_ELEMENT_SIZE = 3

    def __init__(self, ordem:int) -> None:
        """ Gerenciando matriz """
        if ordem < 1 or ordem > 40:
            raise ValueError("A ordem deve estar entre 1 e 40")
        
        self.__ordem = ordem
        self.generate()

    def generate(self):
        """ gerando estrutura da matriz """
        self.__struct = []
        
        for i in range(self.__ordem): # adicionando linhas
            self.__struct.append([])
            
            for _ in range(self.__ordem): # adicionando colunas
                self.__struct[i].append("")
    
    def print(self):
        for i in range(self.__ordem, 0, -1):
            print(str(i).rjust(2, " "), "|", end="")
            row = self.__struct[i-1]

            for col in row:
                print(col.rjust(self.MAX_ELEMENT_SIZE, " "), end="")
            print()

        cols = "".join(list(map(lambda x: str(x).rjust(self.MAX_ELEMENT_SIZE," "), range(1, self.__ordem+1)))) # linha de numeros como str
        print("-" * (self.__ordem * self.MAX_ELEMENT_SIZE + 5))
        print("   ", cols)
    
    def setElementByPosition(self, x:int, y:int, v:str):
        if len(v) > self.MAX_ELEMENT_SIZE:
            raise ValueError("O comprimento do elemento deve ser entre 0 e 4")
        if x < 1 or x > self.__ordem or y < 1 or y > self.__ordem:
            raise ValueError(f"coordenada ({x}, {y}) invalida!")

        self.__struct[y-1][x-1] = v


if __name__ == "__main__":
    m = Matriz(20)
    # adicionando retangulo
    m.setElementByPosition(2, 5, "*")
    m.setElementByPosition(10, 5, "*")
    m.setElementByPosition(2, 2, "*")
    m.setElementByPosition(10, 2, "*")
    m.print()