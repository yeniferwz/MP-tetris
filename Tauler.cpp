#include "Tauler.h"
#include "joc.h"
#include <fstream>
#include <iostream>
#include <algorithm> 
#include <string>

using namespace std;

Tauler::Tauler() {

    for (int i = 0; i < MAX_FILA; ++i) {
        for (int j = 0; j < MAX_COL; ++j) {
            m_tauler[i][j] = NO_COLOR;
        }
    }
}

void getValors(ColorFigura tauler[MAX_FILA][MAX_COL])
{
    for (int i = 0; i < MAX_FILA; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            //tauler[i][j] = m_tauler[i][j + 2];
        }
    }
}

void Tauler::setValor(int fila, int col, ColorFigura valor)
{
    if (fila >= 0 && fila < MAX_FILA && col >= 0 && col < MAX_COL)
    {
        this->m_tauler[fila][col] = valor;
    }
}

bool Tauler::esMovimentValid(const Figura& figura, int nouX, int nouY, int nouGir) const {

    for (int i = 0; i < 4; ++i) {
        int x = nouX + figura.getOffsetX(nouGir, i); //calcula la nueva posi
        int y = nouY + figura.getOffsetY(nouGir, i); //calcula la nueva posi
        if (x < 0 || x >= MAX_COL || y < 0 || y >= MAX_FILA) {
            return false; // figura  fuera de los limites
        }
        if (m_tauler[y][x] != ' ') {
            return false; // posi ocupada
        }
    }
    return true;
}

void Tauler::fixaFigura(const Figura& figura) {
    //x,y mal, color mal
    cout <<"funcio fixa figura:"<< figura << endl;
    for (int i = 0; i < 4; ++i) {
        int x = figura.getX() + figura.getOffsetX(figura.getGir(), i);
        int y = figura.getY() + figura.getOffsetY(figura.getGir(), i);
        if (x >= 0 && x < MAX_COL && y >= 0 && y < MAX_FILA) {
            cout << "tauler: " << m_tauler[x][y] << "fila: "<<y<<" col:"<<x<<" color: " << figura.getColorFigura() << endl;
            m_tauler[y][x] = ColorFigura(figura.getTipus());
        }
    }
}

int Tauler::eliminaFilesCompletes() {
    int filesEliminades = 0;
    for (int fila = 0; fila < MAX_FILA; ++fila) {
        bool filaCompleta = true;
        for (int col = 0; col < MAX_COL; ++col) {
            if (m_tauler[fila][col] == NO_COLOR) {
                filaCompleta = false; //fila no completa
                break;
            }
        }
        if (filaCompleta) {
            for (int filaMoure = fila; filaMoure > 0; --filaMoure) {
                for (int col = 0; col < MAX_COL; ++col) {
                    m_tauler[filaMoure][col] = m_tauler[filaMoure - 1][col]; //filas hacia abajo
                }
            }
            for (int col = 0; col < MAX_COL; ++col) {
                m_tauler[0][col] = COLOR_NEGRE; //fila superior nueva vacia
            }
            ++filesEliminades;
        }
    }
    return filesEliminades;
}

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
}

void Tauler::guardaTauler(const string& nomFitxer, Figura& figuraActual) {
    ofstream fitxer(nomFitxer);
    if (fitxer.is_open()) {
        if (figuraActual.getTipus() != NO_FIGURA) 
            fixaFigura(figuraActual);
        for (int i = 0; i < MAX_FILA; ++i) {
            for (int j = 0; j < MAX_COL; ++j) {
                fitxer << static_cast<int>(m_tauler[i][j]);
            }
            fitxer << '\n';
        }
        fitxer.close();
    }
    else {
        std::cerr << "Error al guardar el tauler a " << nomFitxer << std::endl;
    }
}

void Tauler::carregaTauler(const string& nomFitxer) {
    std::ifstream fitxer(nomFitxer);
    if (fitxer.is_open()) {
        int valor;
        for (int i = 0; i < MAX_FILA; ++i) {
            for (int j = 0; j < MAX_COL; ++j) {
                if (fitxer >> valor) {
                    m_tauler[i][j] = static_cast<ColorFigura>(valor);
                }
            }
        }
        fitxer.close();
    }
    else {
        std::cerr << "Error al cargar el tauler de " << nomFitxer << std::endl;
    }
}

void Tauler::mostraTauler() const {
    for (int i = 0; i < MAX_FILA; ++i) {
        for (int j = 0; j < MAX_COL; ++j) {
            std::cout << m_tauler[i][j];
        }
        std::cout << '\n';
    }
}
