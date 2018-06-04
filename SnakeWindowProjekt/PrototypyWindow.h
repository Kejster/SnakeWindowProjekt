#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include <ctime>
#include <sstream>
#include <fstream>

using namespace std;


class CGame;
class CPosition;
class CBoard;
class CSnake;

enum POZIOM_TRUDNOSCI { LATWY, NORMALNY, SREDNI, TRUDNY, OP };
enum STAN_GRY { ROZGRYWKA, KONIEC };
enum KIERUNEK_RUCHU { GORA = 'G', DOL = 'D', LEWO = 'L', PRAWO = 'P' };
enum EFEKTY {
	NIC = 'N', DO_TYLU = 'T', PRZYSPIESZENIE = 'P', SPOWOLNIENIE = 'S', ODWROTNIE_KIERUNKI = 'O', GLITCH = 'G',
	DODATKOWY_OWOC = 'D'
};

enum POLE {
	PUSTE = 0, OWOC = -1, EFEKT = -2, GLOWA_DEAD = -3,
	SCIANA_GL = 1, SCIANA_GP = 2, SCIANA_DL = 3, SCIANA_DP = 4, SCIANA_POZIOMO = 5, SCIANA_PIONOWO = 6,
	GLOWA_G = 7, GLOWA_D = 8, GLOWA_L = 9, GLOWA_P = 10,
	CIALO_POZIOMO = 11, CIALO_PIONOWO = 12,
	OGON_G = 13, OGON_D = 14, OGON_L = 15, OGON_P = 16,
	SKRET_GL = 17, SKRET_GP = 18, SKRET_DL = 19, SKRET_DP = 20
};


//------------------------------------------------------------------------------
class CGame {
private:
	STAN_GRY stanGry;
	POZIOM_TRUDNOSCI poziomTrudnosci;
	unsigned ileSekundNaRuch;
	string historiaEfektow;
	unsigned int licznikEfektow;
	unsigned short iluGraczy;

public:
	CBoard * plansza;
	CSnake* waz[2];

	CGame(unsigned int, POZIOM_TRUDNOSCI, unsigned short);
	~CGame();

	inline STAN_GRY PodanieStanuGry() const { return stanGry; }
	inline float Okres() const { return ileSekundNaRuch; }

	void SprawdzanieRuchu(unsigned short);
	void LosowanieObiektow(unsigned short);
};
//------------------------------------------------------------------------------

class CPosition {
private:
	unsigned short pozycja_X;
	unsigned short pozycja_Y;

public:
	CPosition(unsigned short wielkosc, short przesuniecie, short ustawienie) {
		switch (ustawienie) {
		case 1: { pozycja_X = (wielkosc - 1) / 2;   pozycja_Y = (wielkosc - 1) / 2 + przesuniecie;  break; }
		case 2: { pozycja_X = (wielkosc - 1) / 2 + 3; pozycja_Y = (wielkosc - 1) / 2 + przesuniecie;  break; }
		case 3: { pozycja_X = (wielkosc - 1) / 2 - 3; pozycja_Y = (wielkosc - 1) / 2 + przesuniecie;  break; }
		};
	}
	//---------------------------------------------------------------                  
	inline unsigned X() const { return pozycja_X; }
	inline void X(short nowaPozycja_X) { pozycja_X += nowaPozycja_X; }
	inline void Xnowe(unsigned short nowe_X) { pozycja_X = nowe_X; }

	inline unsigned Y() const { return pozycja_Y; }
	inline void Y(short nowaPozycja_Y) { pozycja_Y += nowaPozycja_Y; }
	inline void Ynowe(unsigned short nowe_Y) { pozycja_Y = nowe_Y; }

	inline bool PozycjeRowne(CPosition* wsk) {
		if (pozycja_X == wsk->X() && pozycja_Y == wsk->Y())
			return true;
		else return false;
	}
	inline bool PozycjeRowne(unsigned int y, unsigned int x) {
		if (pozycja_X == x && pozycja_Y == y)
			return true;
		else return false;
	}
};
//------------------------------------------------------------------------------

class CBoard {
private:
	const unsigned int wielkoscPlanszy;
	POLE** plansza;
	string historiaRuchow[2];
	CSnake* waz[2];

public:
	CBoard(unsigned int, CSnake*, CSnake*);
	~CBoard();

	inline unsigned int PodanieWielkosci() const { return wielkoscPlanszy; }
	inline POLE** PodaniePlanszy() const { return plansza; }
	inline POLE PodaniePola(unsigned i, unsigned j) const { return plansza[i][j]; }
	inline char PodanieKierunkuOdKonca(unsigned indeks, unsigned ktoryOdKonca) const {
		return historiaRuchow[indeks][historiaRuchow[indeks].length() - ktoryOdKonca];
	}

	void ZaznaczanieRuchu_EX(unsigned short);
};
//------------------------------------------------------------------------------

class CSnake {
private:
	unsigned int dlugosc;
	CPosition* pozycjaGlowy;
	CPosition* pozycjaTylka;
	KIERUNEK_RUCHU kierunekRuchu;
	EFEKTY efekt;
	bool czyZjadlOwoc;
	bool czyUmarl;

public:
	CSnake(unsigned int, unsigned short);
	~CSnake();

	inline void ZmianaKierunku(KIERUNEK_RUCHU nowyKierunek) { kierunekRuchu = nowyKierunek; }
	inline KIERUNEK_RUCHU Kierunek() const { return kierunekRuchu; }
	inline EFEKTY Efekt() const { return efekt; }
	inline void Efekt(EFEKTY nowyEfekt) { efekt = nowyEfekt; }
	inline void ResetEfektu() { efekt = NIC; }
	inline unsigned Dlugosc() const { return dlugosc; }
	inline void CzyZjadlOwoc(bool odp) { czyZjadlOwoc = odp;  if (odp == true) ++dlugosc; }
	inline bool CzyZjadlOwoc() const { return czyZjadlOwoc; }
	inline bool CzyUmarl() const { return czyUmarl; }

	inline int pgx() const { return pozycjaGlowy->X(); }
	inline int pgy() const { return pozycjaGlowy->Y(); }
	inline int ptx() const { return pozycjaTylka->X(); }
	inline int pty() const { return pozycjaTylka->Y(); }


	friend class CGame;
	friend class CBoard;
};

//--------------------------ZWYKLE, ODDZIELNE FUNCKJE---------------------------
HFONT CreateLogFont(HDC, const std::string&, unsigned, bool, bool, bool, bool);
void WpisanieWynikuDoTablicy(unsigned, POZIOM_TRUDNOSCI);
string WypisanieWynikuZTablicy(POZIOM_TRUDNOSCI);

