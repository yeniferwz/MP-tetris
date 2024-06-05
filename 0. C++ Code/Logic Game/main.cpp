//
//  main.cpp
//
//  Copyright � 2018 Compiled Creations Limited. All rights reserved.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)

#include <iostream>
//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED
#include <windows.h>
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <conio.h>      /* getch */ 

#elif __APPLE__
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop

#endif

#include "./Partida.h"
#include "./InfoJoc.h"
#include "Joc.h"
#include "Tetris.h"

using namespace std;

//procediment que mostra el menu principal
void mostrarMenu()
{
    cout << endl;
    cout << "MENU PRINCIPAL" << endl;
    cout << "================" << endl;
    cout << "1. Joc en mode normal" << endl;
    cout << "2. Joc en mode test" << endl;
    cout << "3. Mostrar puntuacions" << endl;
    cout << "4. Sortir" << endl;
    cout << "Tria la teva opcio: ";
}

//procediment que llegeix els fitxers necessaris per a la partida en mode test
void llegirFitxers(string& nomInicial, string& fitxerFigures, string& fitxerMoviments)
{
    cout << "Nom del fitxer amb l'estat inicial del tauler: ";
    getline(cin, nomInicial);
    nomInicial = "./data/Games/" + nomInicial;
    cout << "Nom del fitxer amb la sequencia de figures: ";
    getline(cin, fitxerFigures);
    fitxerFigures = "./data/Games/" + fitxerFigures;
    cout << "Nom del fitxer amb la sequencia de moviments: ";
    getline(cin, fitxerMoviments);
    fitxerMoviments = "./data/Games/" + fitxerMoviments;
}

int main(int argc, const char* argv[])
{
    //Instruccions necesaries per poder incloure la llibreria i que trobi el main
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);

    //Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
    Screen pantalla(SCREEN_SIZE_X, SCREEN_SIZE_Y);
    Tetris tetris("./data/Games/puntuacions.txt");
    bool sortir = false;
    string nomInicial, fitxerFigures, fitxerMoviments, nomJugador;
    int punts;
    
    //bucle principal del joc
    do {
        mostrarMenu();
        char opcio;
        cin >> opcio;
        switch (opcio) {
        case '1':
            punts = tetris.juga(MODE_NORMAL, "", "", "", pantalla);
            cout << "Nom Jugador: "; //Demana el nom del jugador per a guardar la puntuacio
            cin >> nomJugador;
            tetris.actualitzaPuntuacions(nomJugador, punts); //Actualitza la puntuacio
            break;
        case '2':
            llegirFitxers(nomInicial, fitxerFigures, fitxerMoviments); //Llegeix els fitxers del test
            punts = tetris.juga(MODE_TEST, nomInicial, fitxerFigures, fitxerMoviments, pantalla);
            break;
        case '3':
            tetris.mostraPuntuacions(); //Mostra les puntuacions
            break;
        case '4':
            sortir = true; //Finalitza el joc
            break;
        default:
            cout << "Opcio no valida, escull una opcio del menu" << endl;
        }
    } while (sortir == false);

    tetris.guardaPuntuacions("./data/Games/puntuacions.txt");

    //Instruccio necesaria per alliberar els recursos de la llibreria 
    return 0;
}

