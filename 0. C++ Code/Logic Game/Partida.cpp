#include "Partida.h"
#include "InfoJoc.h"
#include "GraphicManager.h"
#include <fstream>

//Constructor de la classe Partida
Partida::Partida()
{
    m_temps = 0.0;
    m_puntuacio = 0;
    m_mode = MODE_NORMAL;
    m_nivel = 1;
    m_velocitat = VELOCITAT_NIVEL_1;
    m_primeraFigura = nullptr;
    m_primerMoviment = nullptr;

    m_figures = m_primeraFigura;
    m_moviments = m_primerMoviment;
    m_fiPartida = false;
    srand(time(0));
}

//Constructor de la classe Partida amb mode
Partida::Partida(Mode mode)
{
    m_temps = 0.0;
    m_puntuacio = 0;
    m_mode = mode;
    m_nivel = 1;
    m_velocitat = VELOCITAT_NIVEL_1;
    m_primeraFigura = nullptr;
    m_primerMoviment = nullptr;

    m_figures = m_primeraFigura;
    m_moviments = m_primerMoviment;
    m_fiPartida = false;
    srand(time(0));
}


void Partida::llegirFigures(const string& fitxerFigures)
{
    ifstream fitxer(fitxerFigures);

    if (fitxer.is_open()) {
        int tipus, fila, columna, gir;
        fitxer >> tipus >> fila >> columna >> gir;

        while (!fitxer.eof()) {
            //crea una figura amb les dades llegides
            Figura figura;
            figura.setGir(gir);
            figura.setTipus(static_cast<TipusFigura>(tipus));
            figura.setX(columna);
            figura.setY(fila);

            //llista dinmaica de figura en la classe partida
            NodeFigura* nodeFiguraActual = new NodeFigura;
            nodeFiguraActual->setFigura(figura);
            nodeFiguraActual->setNextFigura(nullptr);
            
            //si es la primera figura
            if (m_primeraFigura == nullptr)
                m_primeraFigura = nodeFiguraActual;
            else {
                bool trobat = false;
                NodeFigura* seguent = m_primeraFigura;
                //recorre la llista fins a trobar lultim node
                while (!trobat) {
                    if (seguent->getNextFigura() == nullptr) {
                        seguent->setNextFigura(nodeFiguraActual);
                        trobat = true;
                    }
                    else {
                        seguent = seguent->getNextFigura();
                    }
                }
                //llegeix les dades de la seguent figura
                fitxer >> tipus >> fila >> columna >> gir;
                figura.inicialitzaFigura(static_cast<TipusFigura>(tipus), fila, columna, static_cast<Gir>(gir));
            }
        }
        fitxer.close();
    }
}

void Partida::llegirMoviments(const string& fitxerMoviments)
{
    ifstream fitxer;
    fitxer.open(fitxerMoviments);

    if (fitxer.is_open()) {
        int tipusMoviment;
        fitxer >> tipusMoviment;
        //llegeix els moviments del fitxer
        TipusMoviment tipusM = static_cast<TipusMoviment>(tipusMoviment);
        NodeMoviment* movimentActual = new NodeMoviment;
        while (!fitxer.eof()) {
            movimentActual->setMoviment(tipusM);
            movimentActual->setNextMoviment(nullptr);
            //si es el primer moviment
            if (m_primerMoviment == nullptr)
                m_primerMoviment = movimentActual;
            else {
                bool trobat = false;
                NodeMoviment* next = m_primerMoviment;
                while (!trobat) {
                    if (next->getNextMoviment() == nullptr) {
                        next->setNextMoviment(movimentActual);
                        trobat = true;
                    }
                    else
                        next = next->getNextMoviment();
                }
            }
            fitxer >> tipusMoviment;
            tipusM = static_cast<TipusMoviment>(tipusMoviment);
        }
    }
}

//funcio que inicialitza la partida en funcio del mode
void Partida::inicialitza(const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments)
{
    if (m_mode == MODE_TEST) {
        m_joc.inicialitza(fitxerInicial);
        llegirFigures(fitxerFigures);
        llegirMoviments(fitxerMoviments);
    }
    else if (m_mode == MODE_NORMAL){
        //inicialitza el joc amb una figura aleatoria
        m_fiPartida = m_joc.inicialitzaNovaFigura();
    }
}

void Partida::actualitzarPuntuacio(int filesCompletades)
{
     //suma 10 punts per una figura col.locada al tauler
    if (filesCompletades == 0)
        m_puntuacio += FIGURA_COLOCADA;
    else if (filesCompletades > 0) {
        m_puntuacio += filesCompletades * FILA; //100 punts per cada fila completada
        //incrementa puntuacions segons files completades
        switch (filesCompletades) {
        case 2:
            m_puntuacio += ELIMINA_DOS; break;
        case 3:
            m_puntuacio += ELIMINA_TRES; break;
        case 4:
            m_puntuacio += ELIMINA_QUATRE; break;
        }
        //incrementa el nivell i la velocitat
        if (m_puntuacio > (m_nivel * CANVI_NIVELL)) {
            m_nivel++;
            m_velocitat *= CANVI_VELOCITAT;
        }
    }
}


void Partida::actualitzaModeNormal(float deltaTime, int& filesCompletades)
{
    if (Keyboard_GetKeyTrg(KEYBOARD_LEFT))
        m_joc.teclaMouFigura(MOV_LEFT);
    else if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT))
        m_joc.teclaMouFigura(MOV_RIGHT);
    
    if (Keyboard_GetKeyTrg(KEYBOARD_UP))
        m_joc.giraFigura(GIR_HORARI);
    else if (Keyboard_GetKeyTrg(KEYBOARD_DOWN))
        m_joc.giraFigura(GIR_ANTI_HORARI);

    if (Keyboard_GetKeyTrg(KEYBOARD_SPACE)) {
        //baixa la figura fins a quedar col.locada al tauler
        //genera una nova figura aleatoriament, shauria de veure si la poscio de la nova figura en el tauler
        //no provoca colisions i que estigui dins del tauler, en cas contrari vol dir que el joc sacaba
        filesCompletades = m_joc.baixaFiguraCompletament();
        actualitzarPuntuacio(filesCompletades);
        m_fiPartida = m_joc.inicialitzaNovaFigura(); //suma 10 punts per cada figura col.locada
        m_temps = 0.0;
    }
    else {
        m_temps += deltaTime;
        if (m_temps >= m_velocitat) {
            m_temps = 0;
            //filesCompletades = m_joc.baixaFiguraAutomatic();
            filesCompletades = m_joc.baixaFiguraAutomatic();
            if (filesCompletades > 0) {
                m_fiPartida = m_joc.inicialitzaNovaFigura();
                actualitzarPuntuacio(filesCompletades);
            }
        }
    }

}

void Partida::actualitzaModeTest(float deltaTime, int& filesCompletades)
{
    m_temps += deltaTime;
    TipusMoviment moviment;
    if (m_temps > m_velocitat) {
        m_temps = 0.0; //reinicia el temps
        if (m_moviments != nullptr) {
            moviment = m_moviments->getMoviment();
            m_moviments = m_moviments->getNextMoviment();
            //moviment en funcio de TipusMoviment
            if (moviment == MOVIMENT_ESQUERRA)
                m_joc.mouFigura(MOV_LEFT);
            else if (moviment == MOVIMENT_DRETA)
                m_joc.mouFigura(MOV_RIGHT);
            else if (moviment == GIR_HORARI)
                m_joc.giraFigura(GIR_HORARI);
            else if (moviment == GIR_ANTI_HORARI)
                m_joc.giraFigura(GIR_ANTI_HORARI);
            else if (moviment == MOVIMENT_BAIXA) {
                filesCompletades = m_joc.baixaFigura();
                if (filesCompletades > 0) {
                    actualitzarPuntuacio(filesCompletades);
                    Figura fig = m_figures->getFigura();
                    int gir = fig.getGir();
                    for (int i = 0; i < fig.getGir(); i++)
                        m_joc.giraFigura(static_cast<DireccioGir>(gir));
                    m_figures = m_figures->getNextFigura();
                }
            }
            else if (moviment == MOVIMENT_BAIXA_FINAL) {
                filesCompletades = m_joc.baixaFiguraCompletament();
                actualitzarPuntuacio(filesCompletades);
                if (m_figures == nullptr)
                    m_fiPartida = true;
                else {
                    Figura fig = m_figures->getFigura();
                    int gir = fig.getGir();
                    for (int i = 0; i < fig.getGir(); i++)
                        m_joc.giraFigura(static_cast<DireccioGir>(gir));
                    m_figures = m_figures->getNextFigura();
                }
            }
        }
        m_temps = 0;
    }
}


void Partida::actualitza(float deltaTime)
{
    int filesCompletades = 0; //100 punts per files completades o eliminades
    if (m_fiPartida == false) {
        if (m_mode == MODE_TEST) {
            actualitzaModeTest(deltaTime, filesCompletades);
        }
        else if (m_mode == MODE_NORMAL){
            actualitzaModeNormal(deltaTime, filesCompletades);
        }
    }
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
    m_joc.dibuixa(); //dibuixa el tauler

    string puntsMsg = "Punts: " + to_string(m_puntuacio);
    string nivellMsg = "Nivel: " + to_string(m_nivel);

    //mostrar missatges per punts i nivel
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_PUNTS, POS_Y_PUNTS, 1, puntsMsg);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_NIVEL, POS_Y_NIVEL, 1, nivellMsg);
    if(m_fiPartida) {
        string msg = "FI PARTIDA";
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_FI, 2, msg);
    }
}