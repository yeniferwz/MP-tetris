#ifndef TETRIS_H
#define TETRIS_H
#include "Partida.h"
#include <iostream>
#include <list>
#include <string>
#include <Windows.h>
#include "../Graphic Lib/libreria.h"


//tipus de dades per a les puntuacions
typedef struct
{
	string nomJugador;
	int punts;
}PuntuacioJugador;

class Tetris {
public:
	Tetris(const string& fitxerPuntuacions);
	int juga(Mode mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments, Screen& pantalla);
	void mostraPuntuacions() const;
	void guardaPuntuacions(const string& fitxerPuntuacions);
	void actualitzaPuntuacions(const string& fitxerPuntuacions, int punts);
private:
	Partida m_partida;
	list<PuntuacioJugador> m_puntuacions; //llista de puntuacions per a cada jugador que es guardara en un fitxer
};

#endif