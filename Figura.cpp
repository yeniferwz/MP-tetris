#include "Figura.h"
#include <iostream>

using namespace std;

Figura::Figura() : m_tipus(NO_FIGURA), m_color(NO_COLOR), m_x(0), m_y(0), m_gir(0) {}


void Figura::inicialitzaFigura(TipusFigura tipusFigura, ColorFigura colorFigura, int posX, int posY, int girInicial) {
    m_tipus = tipusFigura;
    m_color = colorFigura;
    m_x = posX;
    m_y = posY;
    m_gir = girInicial;
}


void Figura::girarFigura(bool horari) {
    if (horari) {
        m_gir = (m_gir + 1) % 4; // Suponiendo que hay 4 posiciones de giro (0-3)
    }
    else {
        m_gir = (m_gir - 1 + 4) % 4; // Asegura que el valor de 'gir' sigui positivo
    }
}


void Figura::moure(int dx, int dy) {
    m_x += dx;
    m_y += dy;
}

// getters para obtener las figuras
int Figura::getX() const {
    return m_x;
}

int Figura::getY() const {
    return m_y;
}

int Figura::getGir() const {
    return m_gir;
}

TipusFigura Figura::getTipus() const {
    return m_tipus;
}

ColorFigura Figura::getColorFigura() const {
    return m_color;
}

//1r indice: array tridimensional, 2n indice: 
int Figura::getOffsetX(int gir, int bloque) const {
    static const int desplazamientos[4][4][2] = {
        {{0, 0}, {1, 0}, {0, 1}, {1, 1}}, // O 0
        {{0, 0}, {-1, 0}, {0, 1}, {-1, 1}}, // O 1
        {{0, 0}, {1, 0}, {0, -1}, {1, -1}}, // O 2
        {{0, 0}, {-1, 0}, {0, -1}, {-1, -1}} // O 3
    };
    // gir y bloque esta dins de los limites
    return desplazamientos[gir % 4][bloque % 4][0];
}

int Figura::getOffsetY(int gir, int bloque) const {
    static const int desplazamientos[4][4][2] = {
        {{0, 0}, {1, 0}, {0, 1}, {1, 1}}, // Orientación 0
        {{0, 0}, {-1, 0}, {0, 1}, {-1, 1}}, // Orientación 1
        {{0, 0}, {1, 0}, {0, -1}, {1, -1}}, // Orientación 2
        {{0, 0}, {-1, 0}, {0, -1}, {-1, -1}} // Orientación 3
    };
    return desplazamientos[gir % 4][bloque % 4][1];
}

ifstream& operator>>(ifstream& input, Figura& figura)
{
    int tipus, fila, columna, gir;

    input >> tipus >> fila >> columna >> gir;
    TipusFigura tipusFigura = static_cast<TipusFigura>(tipus);
    figura.inicialitzaFigura(static_cast<TipusFigura>(tipusFigura),columna, fila, gir);
    return input;
}

ostream& operator<<(ostream& os, const Figura& figura)
{
    os << "Tipus: " << figura.getTipus() << " color: " << figura.getColorFigura() << " x: " << figura.getX() << " y: " << figura.getY() << endl;
    os << "gir: " << figura.getGir() << endl;
    return os;
}
