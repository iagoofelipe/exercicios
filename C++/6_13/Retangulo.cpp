#include <iostream>
#include <string>
#include <math.h>

#include "Retangulo.h"

COORDENADA getCoordenada(double x, double y) {
    COORDENADA c;
    c.x = x;
    c.y = y;
    return c;
}

void Retangulo::showMsg(std::string msg) {
    std::cout << BLUE << "[PROCESS] " << NORMAL << spacerString(msg, STRING_SIZE);
}

void Retangulo::showMsg(std::string s, bool v) {
        std::cout << BLUE << spacerString(s, STRING_RESULT_SIZE) << (v ? GREEN : RED) << v << NORMAL << std::endl;
}

void Retangulo::showPassed() {
    std::cout << GREEN << "Passed" << NORMAL << std::endl;
}

void Retangulo::showError() {
    std::cout << RED << "Error" << NORMAL << std::endl;
    error = true;
}

void Retangulo::showError(std::string msg) {
    std::cout << RED << "Error\n" << msg << NORMAL << std::endl;
    error = true;
}

std::string Retangulo::spacerString(std::string s, int size) {
    int s_size = s.size();
    int max = size - s_size;

    if(size > s_size)
        for(int i=0; i < max; i++)
            s += STRING_SPACER;

    return s;
}

// calcula a distância entre dois pontos
double Retangulo::calcDistancia(COORDENADA p1, COORDENADA p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// organiza os pontos do retângulo, evitando erros nos cálculos
void Retangulo::orderCoordenadas() {
    /* 
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

    */

   int menor, maior, supEsq, infDir;

    double 
        menorX = _coordenadas[0].x, menorY = _coordenadas[0].y,
        maiorX = _coordenadas[0].x, maiorY = _coordenadas[0].y;

    for(int i=0; i < 4; i++) {
        COORDENADA c = _coordenadas[i];
        
        // separando menor
        if(c.x <= menorX && c.y <= menorY) {
            menorX = c.x;
            menorY = c.y;
            menor = i;
        }

        // separando maior
        if(c.x >= maiorX && c.y >= maiorX) {
            maiorX = c.x;
            maiorY = c.y;
            maior = i;
        }
    }

    // separando superior esquerdo e inferior direito
    int ops[2], aux = 0;
    for(int i=0; i < 4; i++) {
        if(i == maior || i == menor)
            continue;
        
        ops[aux++] = i;
    }

    if(_coordenadas[ops[0]].x < _coordenadas[ops[1]].x) {
        supEsq = ops[0];
        infDir = ops[1];
    } else {
        supEsq = ops[1];
        infDir = ops[0];
    }

    // atribuindo valores corretos
    Retangulo::A = _coordenadas[supEsq]; // A
    Retangulo::B = _coordenadas[maior];  // B
    Retangulo::C = _coordenadas[infDir]; // C
    Retangulo::D = _coordenadas[menor];  // D
}

// armazena as coordenadas digitadas pelo usuário
void Retangulo::setCoordenadas() {
    using namespace std;
    COORDENADA cA, cB, cC, cD;

    cout << "\nCoordenadas A \n\tX: ";
    cin >> cA.x;
    cout << "\tY: ";
    cin >> cA.y;

    cout << "\nCoordenadas B \n\tX: ";
    cin >> cB.x;
    cout << "\tY: ";
    cin >> cB.y;

    cout << "\nCoordenadas C \n\tX: ";
    cin >> cC.x;
    cout << "\tY: ";
    cin >> cC.y;

    cout << "\nCoordenadas D \n\tX: ";
    cin >> cD.x;
    cout << "\tY: ";
    cin >> cD.y;

    setCoordenadas(cA, cB, cC, cD);
}

// armazena as coordenadas passadas por parâmetro
void Retangulo::setCoordenadas(COORDENADA A, COORDENADA B, COORDENADA C, COORDENADA D) {
    // verificar se todos os valores pertencem ao primeiro quadrante e são inferiores ou iguais a 20
    _coordenadas[0] = A;
    _coordenadas[1] = B;
    _coordenadas[2] = C;
    _coordenadas[3] = D;

    showMsg("verificando quadrante...");
    if(!checkCoordenadas()) {
        showError("O retangulo nao esta no primeiro quadrante ou possui valores maiores que 20!");
        return;
    }

    primeiroQuadrante = true;
    showPassed();


    showMsg("ordenando coordenadas...");
    orderCoordenadas();
    showPassed();

    showMsg("verificando pontos iguais...");
    if(checkDupliCoordenadas()) {
        showError("O retangulo possui vertices iguais, invalidando sua existencia!");
        return;
    }

    verticesDiferentes = true;
    showPassed();

    isRetangulo();
}
    
// exibe as coordenadas do retângulo
void Retangulo::displayCoordenadas() {
    using namespace std;
    cout << BLUE << "A " << GREEN << "(" << Retangulo::A.x << ", " << Retangulo::A.y << ")" << NORMAL << endl;
    cout << BLUE << "B " << GREEN << "(" << Retangulo::B.x << ", " << Retangulo::B.y << ")" << NORMAL << endl;
    cout << BLUE << "C " << GREEN << "(" << Retangulo::C.x << ", " << Retangulo::C.y << ")" << NORMAL << endl;
    cout << BLUE << "D " << GREEN << "(" << Retangulo::D.x << ", " << Retangulo::D.y << ")" << NORMAL << endl;
}

// verifica se cada coordenada está no primeiro quadrante sem que x ou y seja maior que 20.0
bool Retangulo::checkCoordenadas() {
    for(COORDENADA c: _coordenadas) {
        if(c.x <= 0 || c.x > 20 || c.y <= 0 || c.y > 20)
            return false;
    }
    return true;
}

// verifica se há coordenadas iguais
bool Retangulo::checkDupliCoordenadas() {
    for(int i=0; i < 4; i++) {
        COORDENADA c = coordenadas[i];

        for(int j=0; j < 4; j++) {
            COORDENADA c2 = coordenadas[j];
            if(i == j)
                continue;
            if(c.x == c2.x && c.y == c2.y)
                return true;
        }
    }
    return false;
}

// verifica se forma um retângulo (4 ângulos retos internamente)
bool Retangulo::isRetangulo() {
    double 
        AB = calcDistancia(Retangulo::A, Retangulo::B),
        BC = calcDistancia(Retangulo::B, Retangulo::C),
        CD = calcDistancia(Retangulo::C, Retangulo::D),
        DA = calcDistancia(Retangulo::D, Retangulo::A),
        AC = calcDistancia(Retangulo::A, Retangulo::C), // distancia interna
        BD = calcDistancia(Retangulo::B, Retangulo::D); // distancia interna

    distancias.AB = AB;
    distancias.BC = BC;
    distancias.CD = CD;
    distancias.DA = DA;

    showMsg("verificando angulos internos...");
    double 
        angA = getAngulo(Retangulo::A, Retangulo::B, Retangulo::D),
        angB = getAngulo(Retangulo::B, Retangulo::C, Retangulo::A),
        angC = getAngulo(Retangulo::C, Retangulo::D, Retangulo::B),
        angD = getAngulo(Retangulo::D, Retangulo::A, Retangulo::C);

    // evitando falso positivo por impresição do cálculo (margem de erro)
    if(angA < 90 || angA >= 91 || angB < 90 || angB >= 91 || angC < 90 || angC >= 91 || angD < 90 || angD >= 91) {
        showError("Angulos internos diferentes de 90");
        std::cout << "A: " << angA << std::endl;
        std::cout << "B: " << angB << std::endl;
        std::cout << "C: " << angC << std::endl;
        std::cout << "D: " << angD << std::endl;
        return false;
    }
    showPassed();

    showMsg("verificando se possui lados paralelos...");
    if(AB != CD || DA != BC) { // impossível formar angulo de 90 graus com lados não paralelos
        showError("Nao possui lados paralelos");
        return false;
    }

    ladosParalelos = true;
    showPassed();

    showMsg("verificando se distancias internas sao equivalentes...");
    if(AC != BD) {
        showError("Distancias internas distintas");
        return false;
    }

    distInternasEquivalentes = true;
    showPassed();

    isRet = true;
    return true;
}

// exibe descrição do retângulo
void Retangulo::displayResult() {
    using namespace std;
    cout << boolalpha;
    cout << "\nResultados encontrados" << endl;

    showMsg("Primeiro quadrante:", primeiroQuadrante);
    showMsg("Vertices diferentes:", verticesDiferentes);
    showMsg("Lados paralelos:", ladosParalelos);
    showMsg("Distancias internas equivalentes:", distInternasEquivalentes);
    showMsg("E um retangulo:", isRet);

    // if(!isRet)
    //     return;

    cout << "\nMedidas" << endl;
    cout << BLUE << "Area:      " << GREEN << getArea() << NORMAL << endl;
    cout << BLUE << "Perimetro: " << GREEN << getPerimetro() << NORMAL << endl;

    cout << "\nComprimento dos Lados" << endl;
    cout << BLUE << "AB: " << GREEN << distancias.AB << NORMAL << endl;
    cout << BLUE << "BC: " << GREEN << distancias.BC << NORMAL << endl;
    cout << BLUE << "CD: " << GREEN << distancias.CD << NORMAL << endl;
    cout << BLUE << "DA: " << GREEN << distancias.DA << NORMAL << endl;

    cout << "\nCoordenadas dos vertices" << endl;
    displayCoordenadas();
}

// calcula o angulo dos pontos ABC (angulo de C)
double Retangulo::getAngulo(COORDENADA A, COORDENADA B, COORDENADA C) {
    double
        a = calcDistancia(B, C),
        b = calcDistancia(A, C),
        c = calcDistancia(B, A);

    double angulo = RAD_TO_GRAU(acos((pow(a, 2) - pow(b, 2) - pow(c, 2)) / (-2 * b * c)));
    return angulo;
}

double Retangulo::getPerimetro() {
    return distancias.AB + distancias.BC + distancias.CD + distancias.DA;
}
double Retangulo::getArea() {
    return distancias.CD * distancias.BC;
}