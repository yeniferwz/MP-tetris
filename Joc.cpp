#include "Joc.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

Joc::Joc() : m_tauler(), m_figuraActual() {
    // Constructor 
}

void Joc::inicialitza(const string& nomFitxer) {
    ifstream fitxer(nomFitxer);
    if (!fitxer.is_open()) {
        std::cerr << "Error al obrir el fitxer " << nomFitxer << std::endl;
        return;
    }

    int tipus, fila, columna, gir, color;
    fitxer >> tipus >> fila >> columna >> gir;

    // Inicializa la figura actual 
    m_figuraActual.inicialitzaFigura(static_cast<TipusFigura>(tipus), static_cast<ColorFigura>(color), columna, fila, gir);

    // Inicializa el tauler 

    for (int i = 0; i < MAX_FILA; ++i) {
        for (int j = 0; j < MAX_COL; ++j) {
            cout << "COLOR: " << color << endl;
            fitxer >> color;
            m_tauler.setValor(i, j, static_cast<ColorFigura>(color));
        }
    }

    fitxer.close();
}

bool Joc::mouFigura(int dirX) {
    int nouX = m_figuraActual.getX() + dirX;
    // Comprova si el moviment es valid per cada bloc 
    if (m_tauler.esMovimentValid(m_figuraActual, nouX, m_figuraActual.getY(), m_figuraActual.getGir())) {
        m_figuraActual.moure(dirX, 0);
        return true;
    }
    return false;
}

int Joc::baixaFigura() {
    int nouY = m_figuraActual.getY() + 1;
    if (!m_tauler.esMovimentValid(m_figuraActual, m_figuraActual.getX(), nouY, m_figuraActual.getGir())) {
        m_tauler.fixaFigura(m_figuraActual);
        int filesEliminades = m_tauler.eliminaFilesCompletes();
        // Prepara  seguent figura
        return filesEliminades;
    }
    m_figuraActual.moure(0, 1);
    return 0;
}

bool Joc::giraFigura(DireccioGir direccio) {
    int nouGir = m_figuraActual.getGir();
    nouGir = (direccio == GIR_HORARI) ? (nouGir + 1) % 4 : (nouGir - 1 + 4) % 4;
    if (m_tauler.esMovimentValid(m_figuraActual, m_figuraActual.getX(), m_figuraActual.getY(), nouGir)) {
        m_figuraActual.girarFigura(direccio == GIR_HORARI);
        return true;
    }
    return false;
}

void Joc::escriuTauler(const string& nomFitxer) {
    //if (m_figuraActual.getTipus() != NO_FIGURA)
        //m_tauler.fixaFigura(m_figuraActual);
    m_tauler.guardaTauler(nomFitxer, m_figuraActual);
}
