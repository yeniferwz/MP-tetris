#include "Tetris.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"

using namespace std;


//Constructor de la classe Tetris, llegira tots els punts del fitxer fitxerPuntuacions que li passa per parametres
Tetris::Tetris(const string& fitxerPuntuacions)
{
	ifstream fitxer;
	fitxer.open(fitxerPuntuacions);

	if (fitxer.is_open())
	{
		PuntuacioJugador pj;
		fitxer >> pj.nomJugador>>pj.punts;
		while (!fitxer.eof()) {
			m_puntuacions.push_back(pj);
			fitxer >> pj.nomJugador>>pj.punts;
		}
		fitxer.close();
	}
}

//funcion que sencarrega a actualitzar el llistat de puntuacions en ordre creixent
void Tetris::actualitzaPuntuacions(const string& nomJugador, int punts)
{
	list<PuntuacioJugador>::iterator it = m_puntuacions.begin();

	bool trobat = false;
	while (!trobat && (it != m_puntuacions.end())) { //busca la posicio on sha de posar la puntuacio
		if ((*it).punts > punts)
			trobat = true;
		else
			it++;
	}
	PuntuacioJugador pj;
	pj.nomJugador = nomJugador;
	pj.punts = punts;
	m_puntuacions.insert(it, pj);
}

//funcio que mostra el llistat de puntuacions
void Tetris::mostraPuntuacions() const
{
	cout << endl;
	cout << "LLISTAT DE PUNTUACIONS: " << endl;
	cout << "==================" << endl;
	list<PuntuacioJugador>::const_iterator it; 
	int i = 1; //contador per mostrar la posicio
	for (it = m_puntuacions.begin(); it != m_puntuacions.end(); it++) {
		cout << i << ". " << (*it).nomJugador << " - " << (*it).punts << endl;;
		i++;
	}
	cout << endl;
}

//funcio que primer actualitza el llistat de puntuacions
//despres es guardara en un fitxer en ordre
void Tetris::guardaPuntuacions(const string& fitxerPuntuacions)
{
	ofstream fitxer;
	fitxer.open(fitxerPuntuacions);
	if (fitxer.is_open()) {
		list<PuntuacioJugador>::iterator it;
		for (it = m_puntuacions.begin(); it != m_puntuacions.end(); it++) {
			fitxer << (*it).nomJugador << " " << (*it).punts << endl; //guarda el nom i els punts
		}
		fitxer.close();
	}
}

int Tetris::juga(Mode mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments, Screen& pantalla)
{
	pantalla.show(); //mostra la pantalla

	Partida partit(mode);
	m_partida.inicialitza(fitxerInicial, fitxerFigures, fitxerMoviments);

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	float deltaTime = 0;
	bool pantallaShow = true;

	do{
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

		//capturar events del ratoli i teclats
		pantalla.processEvents();

		//actualitza la partida segons el mode que escolleix usuari
		m_partida.actualitza(deltaTime);

		//actualitza la pantalla
		pantalla.update();

	} while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));

	if (Keyboard_GetKeyTrg(KEYBOARD_ESCAPE))
		SDL_Quit(); //tanca la finestra si es prem la tecla ESC

	int punts = partit.getPunts(); //retorna els punts de la partida

	return punts;
}
