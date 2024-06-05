#ifndef JOC_H
#define JOC_H

#include "Tauler.h"
#include "Figura.h"
#include "GraphicManager.h"
#include "InfoJoc.h"

class Joc {
public:
    Joc();
    void inicialitza(const string& nomFitxer);
    bool mouFigura(int dirY);
    int baixaFigura();
    bool giraFigura(const DireccioGir direccio);
    void escriuTauler(const string& nomFitxer);
    void dibuixa();
    bool inicialitzaNovaFigura();
    int baixaFiguraCompletament();
    bool teclaMouFigura(int col);
    int baixaFiguraAutomatic();
private:
    Tauler m_tauler;
    Figura m_figuraActual;
};

#endif