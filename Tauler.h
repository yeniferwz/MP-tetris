#pragma once
#ifndef TAULER_H
#define TAULER_H

#include "Figura.h"
#include <fstream>
#include <iostream>
using namespace std;

const int MAX_FILA = 8;
const int MAX_COL = 8;

class Tauler {
private:
    ColorFigura m_tauler[MAX_FILA][MAX_COL]; // Representacio del tablero 
public:
    static const int MAX_FILA = 8;
    static const int MAX_COL = 8;
    Tauler();
    int getTauler(int i, int j) const { return m_tauler[i][j]; }
    void setValor(int fila, int col, ColorFigura valor);
    void getValors(ColorFigura tauler[MAX_FILA][MAX_COL]);
    bool esMovimentValid(const Figura& figura, int nouX, int nouY, int nouGir) const;
    void fixaFigura(const Figura& figura);
    int eliminaFilesCompletes();
    void guardaTauler(const string& nomFitxer, Figura& figuraActual);
    void carregaTauler(const string& nomFitxer);
    void mostraTauler() const; //mostrar el tablero en consola
};

ifstream& operator>>(ifstream& input, Tauler& tauler);
ofstream& operator<<(ofstream& output, const Tauler tauler);

#endif
