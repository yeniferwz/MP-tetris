#ifndef JOC_H
#define JOC_H

#include "Tauler.h"
#include "Figura.h"

class Joc {
public:
    Joc();
    void inicialitza(const string& nomFitxer);
    bool mouFigura(int dirY);
    int baixaFigura();
    bool giraFigura(const DireccioGir direccio);
    void escriuTauler(const string& nomFitxer);
private:
    Tauler m_tauler;
    Figura m_figuraActual;
};

#endif