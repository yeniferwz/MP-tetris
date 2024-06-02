#include "Figura.h"
#include <iostream>

using namespace std;

//constructor de la Figura
Figura::Figura() : m_x(0), m_y(0), m_gir(0), m_tipus(NO_FIGURA)
{
    //inicialitza la matriu de la figura a color negre
    for (int i = 0; i < MAX_ALCADA; i++) {
        for (int j = 0; j < MAX_AMPLADA; j++) {
            m_figura[i][j] = COLOR_NEGRE;
        }
    }
}

//anar amb compte fila-->Y, columna -->X
void Figura::inicialitzaFigura(TipusFigura tipusFigura, int fila, int columna, Gir girInicial)
{
    //neteja de la matriu
    for (int i = 0; i < MAX_ALCADA; i++) {
        for (int j = 0; j < MAX_AMPLADA; j++)
            m_figura[i][j] = COLOR_NEGRE;
    }
    m_tipus = tipusFigura;

    //assignar color i tipus a la figura corresponent, ajustant inicialment el tamany de la figura
    switch (tipusFigura)
    {
    case FIGURA_O:
        m_alcada = 2;
        m_figura[0][0] = m_figura[1][1] = m_figura[0][1] = m_figura[1][0] = COLOR_GROC;
        break;
    case FIGURA_I:
        m_alcada = 4;
        m_figura[1][0] = m_figura[1][1] = m_figura[1][2] = m_figura[1][3] = COLOR_BLAUCEL;
        break;
    case FIGURA_T:
        m_alcada = 3;
        m_figura[0][1] = m_figura[1][0] = m_figura[1][1] = m_figura[1][2] = COLOR_MAGENTA;
        break;
    case FIGURA_L:
        m_alcada = 3;
        m_figura[0][2] = m_figura[1][0] = m_figura[1][1] = m_figura[1][2] = COLOR_TARONJA;
        break;
    case FIGURA_J:
        m_alcada = 3;
        m_figura[0][0] = m_figura[1][0] = m_figura[1][1] = m_figura[1][2] = COLOR_BLAUFOSC;
        break;
    case FIGURA_Z:
        m_alcada = 3;
        m_figura[0][0] = m_figura[0][1] = m_figura[1][1] = m_figura[1][2] = COLOR_VERMELL;
        break;
    case FIGURA_S:
        m_alcada = 3;
        m_figura[0][1] = m_figura[1][0] = m_figura[1][1] = m_figura[0][2] = COLOR_VERD;
        break;
    }

    //ajustar la posicio inicial per basat en el tipus i orientacio de la figura
    ajustarPosicioInicial(fila, columna, girInicial);
    if (girInicial != POSICIO_0)
        aplicarGirInicial(girInicial);
}

void Figura::ajustarPosicioInicial(int fila, int columna, Gir gir)
{
    //les columnes es representa per leix X, i les files per leix Y
    m_x = columna - 1;
    m_y = fila - 1;

    //ajustar per la figura I, 4x4 controlar el tamany en el tauler
    if (m_tipus == FIGURA_I) {
        if (gir == POSICIO_1) {
            m_x = columna + 2;
            m_y = fila;
        }
        else if (gir == POSICIO_2) {
            m_x = columna;
            m_y = fila - 2;
        }
    }
}

void Figura::aplicarGirInicial(Gir gir)
{
    if (gir != POSICIO_0) {
        switch (gir) {
        case 1:
            girarFigura(GIR_HORARI);
            break;
        case 2:
            girarFigura(GIR_HORARI);
            girarFigura(GIR_HORARI);
            break;
        case 3:
            girarFigura(GIR_ANTI_HORARI);
            break;
        }
    }
}

void Figura::transposarMatriu(ColorFigura& aux)
{
    //transposar la matriu
    for (int i = 0; i < m_alcada; i++) {
        for (int j = i; j < m_alcada; j++) {
            aux = m_figura[i][j];
            m_figura[i][j] = m_figura[j][i];
            m_figura[j][i] = aux;
        }
    }
}

void Figura::girarFigura(const DireccioGir direccio) {
    //crear una matriu auxiliar per intercanviar valors
    ColorFigura aux;
    transposarMatriu(aux);

    if (direccio == GIR_HORARI) {
        for (int i = 0; i < m_alcada; i++) {
            for (int j = 0; j < m_alcada / 2; j++) {
                aux = m_figura[i][j];
                m_figura[i][j] = m_figura[i][m_alcada - j - 1]; //intercanvia el valor actual amb el seu oposat en la fila
                m_figura[i][m_alcada - j - 1] = aux;
            }
        }
    }
    else {
        for (int i = 0; i < m_alcada / 2; i++) {
            for (int j = 0; j < m_alcada; j++) {
                aux = m_figura[i][j];
                m_figura[i][j] = m_figura[m_alcada - 1 - i][j];  //intercanvia el valor actual amb el seu oposat en la columna
                m_figura[m_alcada - 1 - i][j] = aux;
            }
        }
    }
}

//funcio que sencarregar de moure la figura, eix X representa les columnes, eix Y les files
void Figura::moure(int col, int fila) {
    m_x += col;
    m_y += fila;
}

/*
ifstream& operator>>(ifstream& input, Figura& figura)
{
    int tipus, fila, columna, gir, color;

    input >> tipus >> fila >> columna >> gir >> color;
    TipusFigura tipusFigura = static_cast<TipusFigura>(tipus);
    figura.inicialitzaFigura(static_cast<TipusFigura>(tipusFigura), static_cast<ColorFigura>(color), columna, fila, gir);
    return input;
}
*/

/*
ostream& operator<<(ostream& os, const Figura& figura)
{
    os << "Tipus: " << figura.getTipus() << " color: " << figura.getColorFigura() << " x: " << figura.getX() << " y: " << figura.getY() << endl;
    os << "gir: " << figura.getGir() << endl;
    return os;
}*/