#include <iostream>
#include <string>

#define STRING_SIZE 60
#define STRING_RESULT_SIZE 40
#define STRING_SPACER ' '
#define PI 3.14159265358979323846
#define RAD_TO_GRAU(X) {X * (180)/PI}

struct COORDENADA {
    double x;
    double y;
};

struct Distancias {
    double AB, BC, CD, DA;
};

COORDENADA getCoordenada(double x, double y);

class Retangulo {
    protected:
        COORDENADA A, B, C, D;
        COORDENADA _coordenadas[4];
        COORDENADA coordenadas[4] = {A, B, C, D};
        Distancias distancias;


        bool primeiroQuadrante = false;
        bool verticesDiferentes = false;
        bool ladosParalelos = false;
        bool distInternasEquivalentes = false;
        bool isRet = false;

        char BLUE[255]      = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
        char GREEN[255]     = { 0x1b, '[', '1', ';', '3', '2', 'm', 0 };
        char RED[255]       = { 0x1b, '[', '1', ';', '4', '9', ';', '3', '1', 'm', 0 };
        char NORMAL[255]    = { 0x1b, '[', '1', ';', '3', '9', 'm', 0 };

        void showMsg(std::string msg);
        void showMsg(std::string s, bool v);

        void showPassed();
        void showError();
        void showError(std::string msg);
        std::string spacerString(std::string s, int size);

        // calcula a distância entre dois pontos
        double calcDistancia(COORDENADA p1, COORDENADA p2);

        // organiza os pontos do retângulo, evitando erros nos cálculos
        void orderCoordenadas();

        // verifica se cada coordenada está no primeiro quadrante sem que x ou y seja maior que 20.0
        bool checkCoordenadas();

        // verifica se há coordenadas iguais
        bool checkDupliCoordenadas();

        // verifica se forma um retângulo (4 ângulos retos internamente)
        bool isRetangulo();

    public:
        bool error = false;

        // armazena as coordenadas digitadas pelo usuário
        void setCoordenadas();

        // armazena as coordenadas passadas por parâmetro
        void setCoordenadas(COORDENADA A, COORDENADA B, COORDENADA C, COORDENADA D);

        // exibe as coordenadas do retângulo
        void displayCoordenadas();

        // exibe descrição do retângulo
        void displayResult();

        double getPerimetro();
        double getArea();
        
        // calcula o angulo beta dos pontos ABC (angulo de B)
        double getAngulo(COORDENADA A, COORDENADA B, COORDENADA C);
};