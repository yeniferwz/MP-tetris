#pragma once
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

class Figura {
private:
    TipusFigura m_tipus;
    ColorFigura m_color;
    int m_x, m_y; // Posicion actual en el tablero
    int m_gir; // Estat de giro actual de la figura
public:
    int getOffsetX(int gir, int bloque) const;
    int getOffsetY(int gir, int bloque) const;
    Figura();
    void inicialitzaFigura(TipusFigura tipusFigura, ColorFigura color, int x, int y, int gir);
    void girarFigura(bool horari);
    void moure(int dx, int dy);
    int getX() const;
    int getY() const;
    int getGir() const;
    ColorFigura getColorFigura() const;
    TipusFigura getTipus() const;

};

ifstream& operator>>(ifstream& input, Figura& figura);
ostream& operator<<(ostream& os, const Figura& figura);

#endif
