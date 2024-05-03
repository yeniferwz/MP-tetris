#include "Figura.h"

Figura::Figura()
{
	m_x = 0;
	m_y = 0;
	m_tipusFigura = NO_FIGURA;
	m_colorFigura = NO_COLOR;
	for(int i = 0; i < MAX_AMPLADA; i++){
		for(int j = 0; j < MAX_ALCADA; j++){
			m_forma[i][j] = NO_COLOR;
		}
	}
}

void Figura::buidarFormaFigura()
{
	for (int i = 0; i < m_alcada; i++)
		for (int j = 0; j < m_amplada; j++)
			m_forma[i][j] = 0;
}

void Figura::getForma(int forma[MAX_ALCADA][MAX_AMPLADA]) const
{
	for (int i = 0; i < m_alcada; i++)
		for (int j = 0; j < m_amplada; j++)
			forma[i][j] = m_forma[i][j];
}


void Figura::inicialitzaForma(TipusFigura tipus)
{
	m_tipusFigura = tipus;
	switch (tipus)
	{
	case FIGURA_J:
		m_alcada = 3, m_amplada = 3;
		buidarFormaFigura();
		m_forma[0][0] = 1;
		m_forma[1][0] = 1;
		m_forma[1][1] = 1;
		m_forma[1][2] = 1;
		m_colorFigura = COLOR_BLAUFOSC;
		break;
	case FIGURA_L:
		m_alcada = 3, m_amplada = 3;
		buidarFormaFigura();
		m_forma[0][2] = 1;
		m_forma[1][0] = 1;
		m_forma[1][1] = 1;
		m_forma[1][2] = 1;
		m_colorFigura = COLOR_TARONJA;
		break;
	case FIGURA_T:
		m_alcada = 3, m_amplada = 3;
		buidarFormaFigura();
		m_forma[0][1] = 1;
		m_forma[1][0] = 1;
		m_forma[1][1] = 1;
		m_forma[1][2] = 1;
		m_colorFigura = COLOR_MAGENTA;
		break;
	case FIGURA_S:
		m_alcada = 3, m_amplada = 3;
		buidarFormaFigura();
		m_forma[0][1] = 1;
		m_forma[0][2] = 1;
		m_forma[1][0] = 1;
		m_forma[1][1] = 1;
		m_colorFigura = COLOR_VERD;
		break;
	case FIGURA_Z:
		m_alcada = 3, m_amplada = 3;
		buidarFormaFigura();
		m_forma[0][0] = 1;
		m_forma[0][1] = 1;
		m_forma[1][1] = 1;
		m_forma[1][2] = 1;
		m_colorFigura = COLOR_VERMELL;
		break;
	case FIGURA_I:
		m_alcada = 4, m_amplada = 4;
		buidarFormaFigura();
		m_forma[1][0] = 1;
		m_forma[1][1] = 1;
		m_forma[1][2] = 1;
		m_forma[1][3] = 1;
		m_colorFigura = COLOR_BLAUCEL;
		break;
	case FIGURA_O:
		m_alcada = 2, m_amplada = 2;
		buidarFormaFigura();
		m_forma[0][0] = 1;
		m_forma[0][1] = 1;
		m_forma[1][0] = 1;
		m_forma[1][1] = 1;
		m_colorFigura = COLOR_GROC;
		break;
	}
}

void Figura::inicialitza(const TipusFigura& tipus, int x, int y)
{
	m_x = x;
	m_y = y;
	m_tipusFigura = tipus;
	inicialitzaForma(tipus);
}

void Figura::transposarMatriu()
{
	int matriuT[MAX_ALCADA][MAX_AMPLADA];
	//construeix la matriu transposada
	for (int i = 0; i < MAX_ALCADA; i++) 
	{
		for (int j = 0; j < MAX_AMPLADA; j++)
		{
			matriuT[j][i] = m_forma[i][j];
		}
	}
}

void Figura::girarFigura(DireccioGir direccio)
{
	int matriuT[MAX_ALCADA][MAX_AMPLADA];
	//construeix la matriu transposada
	for (int i = 0; i < MAX_ALCADA; i++) 
	{
		for (int j = 0; j < MAX_AMPLADA; j++)
		{
			matriuT[j][i] = m_forma[i][j];
		}
	}

	if (direccio == GIR_HORARI) {
		//invertir columnes
		for (int i = 0; i < MAX_ALCADA; i++)
		{
			for (int j = 0; j < MAX_AMPLADA / 2; j++)
			{
				int aux = matriuT[i][j];
				matriuT[i][j] = matriuT[i][MAX_AMPLADA - 1 - j];
				matriuT[i][MAX_AMPLADA - 1 - j] = aux;
			}
		}
	}
	else if (direccio == GIR_ANTI_HORARI) { //invertir files
		for (int i = 0; i < MAX_ALCADA / 2; i++)
		{
			for (int j = 0; j < MAX_AMPLADA; j++)
			{
				int aux = matriuT[i][j];
				matriuT[i][j] = matriuT[MAX_ALCADA - 1 - i][j];
				matriuT[MAX_ALCADA - 1 - i][j] = aux;
			}
		}
	}

	for(int i = 0; i < MAX_ALCADA; i++){
		for(int j = 0; j < MAX_AMPLADA; j++){
			m_forma[i][j] = matriuT[i][j];
		}
	}
}

void Figura::moureAbaix() { m_y++; }

void Figura::moureLateral(int dirX) { m_y += dirX; }
