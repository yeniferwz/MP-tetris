#include "Tauler.h"
#include "joc.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

Tauler::Tauler() {
    for (int i = 0; i < MAX_FILA; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            m_tauler[i][j] = COLOR_NEGRE;
        }
    }
}

void getValors(ColorFigura tauler[MAX_FILA][MAX_COL])
{
    for (int i = 0; i < MAX_FILA; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            cout << tauler[i][j];
        }
    }
}

void Tauler::setValor(int fila, int col, ColorFigura valor)
{
    m_tauler[fila][col] = valor;
}

//funcio que comprova que la figura no sobrepassi del tauler provoqui col.lisions
bool Tauler::esMovimentValid(const Figura& figura, int colMoure, int filaMoure) const {
    //figura, col, fila --> figura, x, y

    bool movCorrecte = true;
    Figura figAux = figura; //crea una figura aux per simular el moviment

    //moure colMoure --> columnes, filaMoure --> files
    figAux.moure(colMoure, filaMoure);

    int col = figAux.getX();
    int fila = figAux.getY();

    for (int i = 0; i < figAux.getAlcada(); i++) {
        for (int j = 0; j < figAux.getAlcada(); j++) {
            if (figAux.getColorFigura(i, j) != COLOR_NEGRE) {
                if (col + i < 0 || col + i >= MAX_COL || fila + j < 0 || fila + j >= MAX_FILA)
                    movCorrecte = false;
                else if (m_tauler[col + i][fila + j] != COLOR_NEGRE)
                    movCorrecte = false;
            }
        }
    }
    return movCorrecte;
}

//funcio que verifica quan es gira la figura, que no sobrepassi del tauler ni provoqui col.lisions
bool Tauler::esGirValid(const Figura& figura, DireccioGir dir) const {
    bool potGirar = true;
    Figura figuraAux = figura;
    figuraAux.girarFigura(dir);

    int fila = figuraAux.getY();
    int col = figuraAux.getX();

    for (int i = 0; i < figuraAux.getAlcada() && potGirar; i++) {
        for (int j = 0; j < figuraAux.getAlcada() && potGirar; j++) {
            if (figuraAux.getColorFigura(i, j) != COLOR_NEGRE) {
                if (col + i >= MAX_COL || fila + j >= MAX_FILA || col + i < 0 || fila + j < 0) {
                    potGirar = false;
                }else if (m_tauler[col + i][fila + j] != COLOR_NEGRE)
                    potGirar = false;
            }
        }
    }

    return potGirar;
}

void Tauler::fixaFigura(const Figura& figura) {
    //en el tablero de tetris, el eje X representa las columnas
    //eje Y, representa las filas

    int columna = figura.getX();
    int fila = figura.getY();
    cout << "col" << columna << " fila" << fila << endl;
    for (int i = 0; i < figura.getAlcada(); i++)
    {
        for (int j = 0; j < figura.getAlcada(); j++)
        {
            if (figura.getColorFigura(i, j) != COLOR_NEGRE) {
                m_tauler[columna + i][fila + j] = figura.getColorFigura(i, j);
            }
        }
    }
    eliminaFilesCompletes(); //despres de fixar la figura, comprova si hi ha files per eliminar
}

//funcio que elimina les files completades i es desplaca les files superior abaix
int Tauler::eliminaFilesCompletes() {
    int filesEliminades = 0;
    int fila = MAX_FILA - 1; //0..7

    while (fila >= 0) {
        bool filaCompleta = true;
        int col = 0;
        while (col < MAX_COL&& filaCompleta) {
            if (m_tauler[fila][col] == COLOR_NEGRE) {
                filaCompleta = false;
            }
            col++;
        }
        if (filaCompleta) {
            filesEliminades++;
            for (int filaMoure = fila; filaMoure > 0; filaMoure--) { //moure de dalt abaix
                for (int colMoure = 0; colMoure < MAX_COL; colMoure++) {
                    m_tauler[filaMoure][colMoure] = m_tauler[filaMoure - 1][colMoure];
                }
            }
            // elimina la fila superior
            for (int colLimpia = 0; colLimpia < MAX_COL; colLimpia++) {
                m_tauler[0][colLimpia] = COLOR_NEGRE;
            }
            //aqui no incrementa la fila ja que potser que la fila que acabem de moure cap abaix podria estar completa
        }
        else {
            fila--;
        }
    }
    return filesEliminades;
}

/*
ifstream& operator>>(ifstream& input, Tauler& tauler)
{
    int color;
    ColorFigura colorFigura;
    for (int i = 0; i < MAX_FILA; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            input >> color;
            colorFigura = static_cast<ColorFigura>(color);
            tauler.setValor(i, j, colorFigura);
        }
    }
    return input;
}

ofstream& operator<<(ofstream& output, const Tauler tauler)
{
    for (int i = 0; i < MAX_FILA; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            output << tauler.getTauler(i, j) << " ";
        }
        output << endl;
    }
    return output;
}*/


void Tauler::mostraTauler() const {
    for (int i = 0; i < MAX_FILA; ++i) {
        for (int j = 0; j < MAX_COL; ++j) {
            std::cout << m_tauler[i][j];
        }
        std::cout << '\n';
    }
}