#ifndef FIGURA_H
#define FIGURA_H

#include <fstream>
#include <iostream>
#include "InfoJoc.h"
#include "GraphicManager.h"

using namespace std;

enum DireccioGir {
    GIR_HORARI,
    GIR_ANTI_HORARI
};

typedef enum
{
    POSICIO_0 = 0,
    POSICIO_1,
    POSICIO_2,
    POSICIO_3
}Gir;

const int MAX_ALCADA = 4;
const int MAX_AMPLADA = 4;

class Figura {
public:
    Figura();
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    void setX(int x) { this->m_x = x; }
    void setY(int y) { this->m_y = y; }
    int getGir() const { return m_gir; }
    void setGir(int gir) { this->m_gir = gir; }
    int getAlcada() const { return m_alcada; }
    ColorFigura getColorFigura(int columna, int fila) const { return m_figura[columna][fila]; }
    TipusFigura getTipus() const { return m_tipus; }
    void setTipus(TipusFigura tipus) { m_tipus = tipus; }

    void inicialitzaFigura(TipusFigura tipusFigura, int x, int y, Gir gir);
    void ajustarPosicioInicial(int fila, int columna, Gir gir);
    void aplicarGirInicial(Gir gir);
    void transposarMatriu(ColorFigura& aux);
    void girarFigura(DireccioGir gir);
    void moure(int dx, int dy);
    void dibuixaFigura() const;
private:
    TipusFigura m_tipus;
    ColorFigura m_figura[MAX_ALCADA][MAX_AMPLADA];
    int m_x; //filas
    int m_y; // columnas
    int m_gir; // Estat de giro actual de la figura
    int m_alcada; //atribut per controlar tamany de m_figura
};

//classes nodes per utilitzar llistes dinamiques amb nodes enllacats
class NodeFigura {
public:
    //getters
    Figura& getFigura() { return m_nodeFigura; }
    NodeFigura* getNextFigura() { return m_nextFigura; }
    //setters
    void setFigura(const Figura& nodeFigura) { m_nodeFigura = nodeFigura; }
    void setNextFigura(NodeFigura* seguent) { m_nextFigura = seguent; }

private:
    Figura m_nodeFigura;
    NodeFigura* m_nextFigura;

};


class NodeMoviment {
public:
    //getters
    TipusMoviment& getMoviment() { return m_nodeMoviment; }
    NodeMoviment* getNextMoviment() { return m_nextMoviment; }

    //setters
    void setMoviment(const TipusMoviment& nodeMoviment) { m_nodeMoviment = nodeMoviment; }
    void setNextMoviment(NodeMoviment* seguent) { m_nextMoviment = seguent; }

private:
    TipusMoviment m_nodeMoviment;
    NodeMoviment* m_nextMoviment;
};

#endif
