#ifndef TAULER_H
#define TAULER_H

#include "Figura.h"
#include <fstream>
#include <iostream>
#include "InfoJoc.h"
using namespace std;

const int MAX_FILA = 22;
const int MAX_COL = 11;

class Tauler {
public:
    Tauler();
    ColorFigura getTauler(int i, int j) const { return m_tauler[i][j]; }
    void setValor(int fila, int col, ColorFigura valor);
    bool esMovimentValid(const Figura& figura, int nouX, int nouY) const;
    bool esGirValid(const Figura& figura, DireccioGir dir) const;
    void fixaFigura(const Figura& figura);
    int eliminaFilesCompletes();
    void dibuixaTauler() const;
    bool movimentValidGrafica(const Figura& figura, int colMoure, int filaMoure) const;
private:
    ColorFigura m_tauler[MAX_FILA][MAX_COL]; // Representacio del tablero 
};
#endif