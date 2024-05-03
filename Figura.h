#pragma once
#ifndef FIGURA_H
#define FIGURA_H

typedef enum
{
    COLOR_NEGRE = 0,
    COLOR_GROC,
    COLOR_BLAUCEL,
    COLOR_MAGENTA,
    COLOR_TARONJA,
    COLOR_BLAUFOSC,
    COLOR_VERMELL,
    COLOR_VERD,
    NO_COLOR
} ColorFigura;


typedef enum
{
    NO_FIGURA = 0,
    FIGURA_O,
    FIGURA_I,
    FIGURA_T,
    FIGURA_L,
    FIGURA_J,
    FIGURA_Z,
    FIGURA_S,
} TipusFigura;

const int MAX_ALCADA = 4;
const int MAX_AMPLADA = 4;

typedef enum
{
    GIR_HORARI = 0,
    GIR_ANTI_HORARI
} DireccioGir;

class Figura
{
public:
    //constructor i destructor
    Figura();//constructor per defecte
    //~Figura();

    //getters i setters
    TipusFigura getTipus() const { return m_tipusFigura; }
    ColorFigura getColor() const { return m_colorFigura; }
    int getX() const {return m_x;}
    int getY() const {return m_y;}
    int getAlcada() const { return m_alcada; }
    int getAmplada() const { return m_amplada; }
    void getForma(int forma[MAX_ALCADA][MAX_AMPLADA]) const;

    //metodes
    void inicialitza(const TipusFigura& tipus, int x, int y);
    void inicialitzaForma(TipusFigura tipus);
    void buidarFormaFigura();
    void moureAdalt();
    void moureAbaix();
    void moureLateral(int dirX);
    void girarFigura(DireccioGir direccio);
    void transposarMatriu();

private:
    TipusFigura m_tipusFigura;
    ColorFigura m_colorFigura;
    int m_x; //files
    int m_y; //columnes
    int m_alcada;
    int m_amplada;
    int m_forma[MAX_ALCADA][MAX_AMPLADA]; //la matriu que representa la forma de la figura
};


#endif // FIGURA_H
