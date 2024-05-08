#ifndef JOC_H
#define JOC_H

#include "Tauler.h"
#include "Figura.h"

class Joc {
private:
    Tauler m_tauler;
    Figura m_figuraActual;
public:
    Joc();
    void inicialitza(const string& nomFitxer);
    bool mouFigura(int dx);
    int baixaFigura();
    bool giraFigura(DireccioGir direccio);
    void escriuTauler(const string& nomFitxer);
};

#endif
