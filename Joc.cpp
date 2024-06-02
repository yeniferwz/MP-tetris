#include "Joc.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

// Constructor
Joc::Joc() {
    for (int i = 0; i < MAX_FILA; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            m_tauler.setValor(i, j, COLOR_NEGRE);
        }
    }
}

void Joc::inicialitza(const string& nomFitxer) {
    ifstream fitxer;
    fitxer.open(nomFitxer);
    if (fitxer.is_open()) {
        int tipus, fila, columna, gir;
        fitxer >> tipus >> fila >> columna >> gir;
        int color;
        for (int i = 0; i < MAX_FILA; i++) {
            for (int j = 0; j < MAX_COL; j++) {
                fitxer >> color;
                m_tauler.setValor(i, j, static_cast<ColorFigura>(color));
            }
        }
        m_figuraActual.inicialitzaFigura(static_cast<TipusFigura>(tipus), columna, fila, static_cast<Gir>(gir));
    }
    fitxer.close();
}

//funcio que mou la figura lateralment
//-1 --> moure esquerra, 1 --> moure dreta, en funcio de leix X
bool Joc::mouFigura(int colMoure) {
    bool potMoure = false;
    int dx = (colMoure > 0) ? 1 : -1;

    if (m_tauler.esMovimentValid(m_figuraActual, 0, dx)) { //comprovar moviment
        m_figuraActual.moure(0, dx);
        potMoure = true;
    }
    return potMoure;
}

//funcio que baixa la figura una posicio si el moviment es correcte
int Joc::baixaFigura() {
    int filesEliminades = 0;

    if (m_tauler.esMovimentValid(m_figuraActual,1,0))
        m_figuraActual.moure(1, 0); //augmentant la Y

    return filesEliminades;
}

//funcio que gira a figura a partir de la orientacio que pasa per parametres
bool Joc::giraFigura(const DireccioGir dir) {
    bool potGirar = false;

    if (m_tauler.esGirValid(m_figuraActual, dir)) {
        m_figuraActual.girarFigura(dir);
        potGirar = true;
    }

    return potGirar;
}

void Joc::escriuTauler(const string& nomFitxer) {
    m_tauler.fixaFigura(m_figuraActual);

    ofstream fitxer(nomFitxer);

    if (fitxer.is_open()) {
        for (int i = 0; i < MAX_FILA; i++) {
            for (int j = 0; j < MAX_COL; j++) {
                fitxer << m_tauler.getTauler(i, j);
            }
            fitxer << endl;
        }
    }
    fitxer.close();
}