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

//funcio que mou la figura lateralment amb la tecla
bool Joc::teclaMouFigura(int col) {
    bool potMoure = false;
    int dx = (col > 0) ? 1 : -1;

    if (m_tauler.esMovimentValid(m_figuraActual, dx, 0)) { //comprovar moviment
        m_figuraActual.moure(dx, 0);
        potMoure = true;
    }
    return potMoure;
}

//funcio que baixa la figura una posicio si el moviment es correcte, retorna les files completades
int Joc::baixaFigura() {
    int filesCompletades = 0;

    if (m_tauler.esMovimentValid(m_figuraActual,1,0))
        m_figuraActual.moure(1, 0); //augmentant la Y

    filesCompletades = m_tauler.eliminaFilesCompletes();

    return filesCompletades;
}

//funcio que baixa la figura automaticament una posicio si el moviment es correcte, retorna les files completades
int Joc::baixaFiguraAutomatic() {
    int filesCompletades = -1;

    if (m_tauler.movimentValidGrafica(m_figuraActual, 0, 1)) 
        m_figuraActual.moure(0,1);

    filesCompletades = m_tauler.eliminaFilesCompletes();

    return filesCompletades;
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

void Joc::dibuixa()
{
    m_tauler.dibuixaTauler();
    m_figuraActual.dibuixaFigura();
}

//funcio que genera una nova figura amb tipus i gir aleatori que es posa en la part superior del tauler
bool Joc::inicialitzaNovaFigura()
{
    bool quedaEspaiPerNovaFigura = false;
    TipusFigura tipusFigura = static_cast<TipusFigura>((rand() % N_TIPUS_FIGURES) + 1);
    int gir = (rand() % 4);
    int colMaxima = N_COL_TAULER - (tipusFigura == FIGURA_I ? 2 : (tipusFigura == FIGURA_O ? 1 : 2));
    int columna = rand() % colMaxima;
    int fila = 1;

    //fila per moure seria 1 ja que sha a la part mes superior del tauler

    for (int i = 0; i < gir; i++) {
        m_figuraActual.girarFigura(GIR_HORARI);
    }

    m_figuraActual.inicialitzaFigura(static_cast<TipusFigura>(tipusFigura), fila, columna, static_cast<Gir>(gir));
    if (m_tauler.movimentValidGrafica(m_figuraActual, columna, 1))
        quedaEspaiPerNovaFigura = true;

    return quedaEspaiPerNovaFigura;
}

int Joc::baixaFiguraCompletament()
{
    int filesCompletades;
    do {
        filesCompletades = baixaFigura();
    } while (filesCompletades == 0);

    //util per afegir les puntuacions
    return filesCompletades;
}