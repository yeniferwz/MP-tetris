#ifndef PARTIDA_H
#define PARTIDA_H

#include <stdio.h>
#include <string>
#include <iostream>
#include "InfoJoc.h"
#include "Joc.h"

using namespace std;

class Partida 
{
public:
    Partida();
    Partida(Mode mode);
    void inicialitza(const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments);
    void actualitzaModeNormal(float deltaTime, int& filesCompletades);
    void actualitzaModeTest(float deltaTime, int& filesCompletades);
    void actualitza(float deltaTime);
    void llegirFigures(const string& fitxerFigures);
    void llegirMoviments(const string& fitxerMoviments);
    void actualitzarPuntuacio(int filesCompletades);
    int getPunts() const { return m_puntuacio; }
private:
    Joc m_joc;
    Mode m_mode;
    int m_puntuacio;
    int m_nivel;
    double m_temps;
    double m_velocitat;
    bool m_fiPartida;

    NodeFigura* m_primeraFigura;
    NodeFigura* m_figures;

    NodeMoviment* m_primerMoviment;
    NodeMoviment* m_moviments;

};

#endif 
