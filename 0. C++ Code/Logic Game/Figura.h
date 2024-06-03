#ifndef FIGURA_H
#define FIGURA_H

#include <fstream>
#include <iostream>

using namespace std;

enum DireccioGir {
    GIR_HORARI,
    GIR_ANTI_HORARI
};
typedef enum {
    COLOR_NEGRE = 0,
    COLOR_GROC,
    COLOR_BLAUCEL,
    COLOR_MAGENTA,
    COLOR_TARONJA,
    COLOR_BLAUFOSC,
    COLOR_VERMELL,
    COLOR_VERD,
    NO_COLOR
} ColorFigura;

typedef enum {
    NO_FIGURA = 0,
    FIGURA_O,
    FIGURA_I,
    FIGURA_T,
    FIGURA_L,
    FIGURA_J,
    FIGURA_Z,
    FIGURA_S
} TipusFigura;

typedef enum
{
    POSICIO_0 = 0,
    POSICIO_1,
    POSICIO_2,
    POSICIO_3
}Gir;

const int MAX_ALCADA = 4;
const int MAX_AMPLADA = 4;

class Figura {
public:
    Figura();
    void inicialitzaFigura(TipusFigura tipusFigura, int x, int y, Gir gir);
    void ajustarPosicioInicial(int fila, int columna, Gir gir);
    void aplicarGirInicial(Gir gir);
    void transposarMatriu(ColorFigura& aux);
    void girarFigura(DireccioGir gir);
    void moure(int dx, int dy);
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    void setX(int x) { this->m_x = x; }
    void setY(int y) { this->m_y = y; }
    int getGir() const { return m_gir; }
    int getAlcada() const { return m_alcada; }
    ColorFigura getColorFigura(int columna, int fila) const { return m_figura[columna][fila]; }
    TipusFigura getTipus() const { return m_tipus; }
private:
    TipusFigura m_tipus;
    ColorFigura m_figura[MAX_ALCADA][MAX_AMPLADA];
    int m_x; //filas
    int m_y; // columnas
    int m_gir; // Estat de giro actual de la figura
    int m_alcada; //atribut per controlar tamany de m_figura
};

//ifstream& operator>>(ifstream& input, Figura& figura);
//ostream& operator<<(ostream& os, const Figura& figura);

#endif
