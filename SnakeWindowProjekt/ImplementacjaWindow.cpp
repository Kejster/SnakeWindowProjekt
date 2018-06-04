#include "PrototypyWindow.h"


//----------------------------MAKRA I MAKRODEFINICJE----------------------------

#define OPERACJE_SPRAWDZANIA(GLOWA_Y,GLOWA_X,indeks) { \
                     POLE punkt = plansza->PodaniePola(GLOWA_Y, GLOWA_X); \
                     if (punkt == OWOC) \
                        waz[indeks]->CzyZjadlOwoc(true); \
                     else if (punkt == EFEKT) { \
                       if (historiaEfektow[licznikEfektow] == 'D') \
                          waz[indeks]->CzyZjadlOwoc(true); \
                       else waz[0]->efekt = static_cast<EFEKTY>(historiaEfektow[licznikEfektow]); \
                       ++licznikEfektow; \
                     } \
                     else { \
                       unsigned ind2 = (indeks == 0) ? 1 : 0; \
                       if ( static_cast<int>(punkt) > 0 && \
                                (waz[indeks]->pozycjaTylka->PozycjeRowne(GLOWA_Y, GLOWA_X) == false || \
                                   ( waz[ind2] != NULL && (GLOWA_Y != waz[ind2]->pty() || GLOWA_X != waz[ind2]->ptx()) )) ) { \
                          stanGry = KONIEC; \
                          waz[indeks]->czyUmarl = true; \
                       } \
                     } \
                     break; \
}

//-----------------------------METODY KLASY CGAME-------------------------------
CGame::CGame(unsigned int wielkoscPlanszy, POZIOM_TRUDNOSCI trudnosc, unsigned short iluGraczyGra)
	: stanGry(ROZGRYWKA), poziomTrudnosci(trudnosc), historiaEfektow(""), licznikEfektow(0), iluGraczy(iluGraczyGra) {
	switch (poziomTrudnosci) {
	case LATWY:    ileSekundNaRuch = (unsigned)(1.0 * 500);  break; //bedzie przetwarzane na milisekundy, dlatego *500
	case NORMALNY: ileSekundNaRuch = (unsigned)(0.7 * 500);  break;               //czytajac -> razy pol sekundy
	case SREDNI:   ileSekundNaRuch = (unsigned)(0.5 * 500);  break;
	case TRUDNY:   ileSekundNaRuch = (unsigned)(0.3 * 500);  break;
	case OP:       ileSekundNaRuch = (unsigned)(0.15 * 500);
	}

	if (iluGraczyGra == 1) {
		waz[0] = new CSnake(wielkoscPlanszy, 1); // podstawowe ustawienie weza - w srodku
		waz[1] = NULL;
	}
	else {
		waz[0] = new CSnake(wielkoscPlanszy, 2); //2 wariacja razem z
		waz[1] = new CSnake(wielkoscPlanszy, 3); //3 wariacja ustawienia
	}
	plansza = new CBoard(wielkoscPlanszy, waz[0], waz[1]);
}

CGame::~CGame() {
	if (plansza != nullptr)
		delete plansza;
	if (waz[0] != nullptr)
		delete waz[0];
	if (waz[1] != nullptr)
		delete waz[1];
}

void CGame::SprawdzanieRuchu(unsigned short indeks) {
	switch (waz[indeks]->kierunekRuchu) {
	case GORA:  OPERACJE_SPRAWDZANIA(waz[indeks]->pozycjaGlowy->Y() - 1, waz[indeks]->pozycjaGlowy->X(), indeks);
	case DOL:   OPERACJE_SPRAWDZANIA(waz[indeks]->pozycjaGlowy->Y() + 1, waz[indeks]->pozycjaGlowy->X(), indeks);
	case LEWO:  OPERACJE_SPRAWDZANIA(waz[indeks]->pozycjaGlowy->Y(), waz[indeks]->pozycjaGlowy->X() - 1, indeks);
	case PRAWO: OPERACJE_SPRAWDZANIA(waz[indeks]->pozycjaGlowy->Y(), waz[indeks]->pozycjaGlowy->X() + 1, indeks);
	};
}

void CGame::LosowanieObiektow(unsigned short indeks) {
	unsigned int wielkosc = plansza->PodanieWielkosci() - 2; // -2 bo sciany

	unsigned short licznik = 0;                            // sprawdza czy sa jeszcze puste pola
	for (unsigned int i = 1; i < wielkosc; ++i) {
		for (unsigned int j = 1; j < wielkosc; ++j)
			if (plansza->PodaniePlanszy()[i][j] == PUSTE) {
				++licznik;
				if (licznik == 2)
					break;
			}
		if (licznik == 2)
			break;
	}
	if (licznik == 0) return;


	unsigned int y;
	unsigned int x;
	//--------------------LOSOWANIE OWOCU---------------------
	while (true) {
		y = rand() % wielkosc + 1;
		x = rand() % wielkosc + 1;
		if (plansza->PodaniePlanszy()[y][x] == PUSTE) {
			plansza->PodaniePlanszy()[y][x] = OWOC;
			break;
		}
	};
	waz[indeks]->czyZjadlOwoc = false;

	//--------------------LOSOWANIE EFEKTU--------------------
	if (licznik > 1 && ((waz[0]->dlugosc + 1) % 3 == 0
		|| (waz[1] != NULL && (waz[1]->dlugosc + 1) % 3 == 0))) { //miejsca na kolejny efekt
		while (true) {
			y = rand() % wielkosc + 1;
			x = rand() % wielkosc + 1;
			if (plansza->PodaniePlanszy()[y][x] == PUSTE) {
				plansza->PodaniePlanszy()[y][x] = EFEKT;
				break;
			}
		};
		switch (rand() % 6) {  //losowanie efektu
		case 0: historiaEfektow += 'T';  break;
		case 1: historiaEfektow += 'O';  break;
		case 2: historiaEfektow += 'S';  break;
		case 3: historiaEfektow += 'D';  break;
		case 4: historiaEfektow += 'P';  break;
		case 5: historiaEfektow += 'G';  break;
		};
	}
}

//----------------------------METODY KLASY CBOARD-------------------------------
CBoard::CBoard(unsigned int wielkosc, CSnake* wsk, CSnake* wsk2)
	: wielkoscPlanszy(wielkosc), plansza(new POLE*[wielkoscPlanszy]) {
	for (unsigned int i = 0; i < wielkoscPlanszy; ++i)
		plansza[i] = new POLE[wielkoscPlanszy];

	for (unsigned int i = 0; i < wielkoscPlanszy; ++i)
		for (unsigned int j = 0; j < wielkoscPlanszy; ++j)
			if (i == 0 && j == 0)
				plansza[i][j] = SCIANA_GL;
			else if (i == 0 && j == wielkoscPlanszy - 1)
				plansza[i][j] = SCIANA_GP;
			else if (i == wielkoscPlanszy - 1 && j == 0)
				plansza[i][j] = SCIANA_DL;
			else if (i == wielkoscPlanszy - 1 && j == wielkoscPlanszy - 1)
				plansza[i][j] = SCIANA_DP;
			else if (i == 0 || i == wielkosc - 1)
				plansza[i][j] = SCIANA_POZIOMO;
			else if (j == 0 || j == wielkosc - 1)
				plansza[i][j] = SCIANA_PIONOWO;
			else plansza[i][j] = PUSTE;


			waz[0] = wsk;
			waz[1] = wsk2;
			if (waz[1] == NULL) {
				plansza[(wielkoscPlanszy - 1) / 2 - 1][(wielkoscPlanszy - 1) / 2] = GLOWA_G;    //pozycja startowa weza, w srodku planszy
				plansza[(wielkoscPlanszy - 1) / 2][(wielkoscPlanszy - 1) / 2] = CIALO_PIONOWO;
				plansza[(wielkoscPlanszy - 1) / 2 + 1][(wielkoscPlanszy - 1) / 2] = OGON_D;  //pozycja startowa tylka weza, o 1 nizej
				historiaRuchow[0] = "GG";
			}
			else {
				plansza[(wielkoscPlanszy - 1) / 2 - 1][(wielkoscPlanszy - 1) / 2 + 3] = GLOWA_G;    //pozycja startowa weza, w srodku planszy
				plansza[(wielkoscPlanszy - 1) / 2][(wielkoscPlanszy - 1) / 2 + 3] = CIALO_PIONOWO;
				plansza[(wielkoscPlanszy - 1) / 2 + 1][(wielkoscPlanszy - 1) / 2 + 3] = OGON_D;  //pozycja startowa tylka weza, o 1 nizej

				plansza[(wielkoscPlanszy - 1) / 2 + 1][(wielkoscPlanszy - 1) / 2 - 3] = GLOWA_D;    //pozycja startowa weza, w srodku planszy
				plansza[(wielkoscPlanszy - 1) / 2][(wielkoscPlanszy - 1) / 2 - 3] = CIALO_PIONOWO;
				plansza[(wielkoscPlanszy - 1) / 2 - 1][(wielkoscPlanszy - 1) / 2 - 3] = OGON_G;  //pozycja startowa tylka weza, o 1 nizej

				historiaRuchow[0] = "GG";
				historiaRuchow[1] = "DD";
			}

}

CBoard::~CBoard() {
	for (int i = 0; i < wielkoscPlanszy; ++i)
		if (plansza[i] != nullptr)
			delete[] plansza[i];
	if (plansza != nullptr)
		delete[] plansza;
}

void CBoard::ZaznaczanieRuchu_EX(unsigned short ind) { // ind -> indeks
	switch (waz[ind]->kierunekRuchu) {
	case GORA:
		plansza[waz[ind]->pozycjaGlowy->Y() - 1][waz[ind]->pozycjaGlowy->X()] = GLOWA_G;
		waz[ind]->pozycjaGlowy->Y(-1);
		historiaRuchow[ind] += 'G';
		break;
	case DOL:
		plansza[waz[ind]->pozycjaGlowy->Y() + 1][waz[ind]->pozycjaGlowy->X()] = GLOWA_D;
		waz[ind]->pozycjaGlowy->Y(+1);
		historiaRuchow[ind] += 'D';
		break;
	case LEWO:
		plansza[waz[ind]->pozycjaGlowy->Y()][waz[ind]->pozycjaGlowy->X() - 1] = GLOWA_L;
		waz[ind]->pozycjaGlowy->X(-1);
		historiaRuchow[ind] += 'L';
		break;
	case PRAWO:
		plansza[waz[ind]->pozycjaGlowy->Y()][waz[ind]->pozycjaGlowy->X() + 1] = GLOWA_P;
		waz[ind]->pozycjaGlowy->X(+1);
		historiaRuchow[ind] += 'P';
	};
	if (waz[ind]->czyZjadlOwoc == false) {
		if (waz[ind]->pozycjaGlowy->PozycjeRowne(waz[ind]->pozycjaTylka) == false)
			plansza[waz[ind]->pozycjaTylka->Y()][waz[ind]->pozycjaTylka->X()] = PUSTE;

		switch (historiaRuchow[ind][0]) {
		case 'G': waz[ind]->pozycjaTylka->Y(-1);  break;
		case 'D': waz[ind]->pozycjaTylka->Y(+1);  break;
		case 'L': waz[ind]->pozycjaTylka->X(-1);  break;
		case 'P': waz[ind]->pozycjaTylka->X(+1);
		};

		if (waz[ind]->efekt != DO_TYLU) { //zmniejszanie objetosci historiiRuchow  
			string przechowywaczStr = "";
			for (unsigned int i = 1; i <= waz[ind]->dlugosc + 1; ++i)
				przechowywaczStr += historiaRuchow[ind][i];
			historiaRuchow[ind] = przechowywaczStr;
		}
	}


	if (waz[ind]->efekt == DO_TYLU) {
		unsigned short Y_glowy = waz[ind]->pozycjaGlowy->Y();
		unsigned short X_glowy = waz[ind]->pozycjaGlowy->X();
		waz[ind]->pozycjaGlowy->Xnowe(waz[ind]->pozycjaTylka->X());
		waz[ind]->pozycjaGlowy->Ynowe(waz[ind]->pozycjaTylka->Y());
		waz[ind]->pozycjaTylka->Xnowe(X_glowy);
		waz[ind]->pozycjaTylka->Ynowe(Y_glowy);

		string strOdwrotnie = "";
		for (int i = historiaRuchow[ind].length() - 1; i >= 0; --i)
			switch (historiaRuchow[ind][i]) {
			case 'G': strOdwrotnie += 'D';  break;
			case 'D': strOdwrotnie += 'G';  break;
			case 'L': strOdwrotnie += 'P';  break;
			case 'P': strOdwrotnie += 'L';
			};

		historiaRuchow[ind] = "";
		for (unsigned i = 0; i < strOdwrotnie.length() - 1; ++i)
			historiaRuchow[ind] += strOdwrotnie[i];

		waz[ind]->kierunekRuchu = static_cast<KIERUNEK_RUCHU>(strOdwrotnie[strOdwrotnie.length() - 1]);
		waz[ind]->efekt = NIC;

		switch (historiaRuchow[ind][historiaRuchow[ind].length() - 1]) {  //WZOR GLOWY
		case 'G':  plansza[waz[ind]->pozycjaGlowy->Y()][waz[ind]->pozycjaGlowy->X()] = GLOWA_G;  break;
		case 'D':  plansza[waz[ind]->pozycjaGlowy->Y()][waz[ind]->pozycjaGlowy->X()] = GLOWA_D;  break;
		case 'L':  plansza[waz[ind]->pozycjaGlowy->Y()][waz[ind]->pozycjaGlowy->X()] = GLOWA_L;  break;
		case 'P':  plansza[waz[ind]->pozycjaGlowy->Y()][waz[ind]->pozycjaGlowy->X()] = GLOWA_P;
		};
	}

	//-------------------------------------------------------------------------

	unsigned koniecHistorii = historiaRuchow[ind].length();
	unsigned x = waz[ind]->pozycjaTylka->X(), y = waz[ind]->pozycjaTylka->Y();  //indeksy

	switch (historiaRuchow[ind][0]) { //wariacje dla ogonu
	case 'G': plansza[y][x] = OGON_D;  --y;  break;
	case 'D': plansza[y][x] = OGON_G;  ++y;  break;
	case 'L': plansza[y][x] = OGON_P;  --x;  break;
	case 'P': plansza[y][x] = OGON_L;  ++x;
	};

	for (unsigned i = 1; i < koniecHistorii; ++i) {  //wariacje dla ciala
		switch (historiaRuchow[ind][i]) {
		case 'G': {
			switch (historiaRuchow[ind][i - 1]) {
			case 'G': plansza[y][x] = CIALO_PIONOWO; break;
			case 'L': plansza[y][x] = SKRET_DL; break;
			case 'P': plansza[y][x] = SKRET_DP;
			};
			--y;
			break;
		}
		case 'D': {
			switch (historiaRuchow[ind][i - 1]) {
			case 'D': plansza[y][x] = CIALO_PIONOWO; break;
			case 'L': plansza[y][x] = SKRET_GL; break;
			case 'P': plansza[y][x] = SKRET_GP;
			};
			++y;
			break;
		}
		case 'L': {
			switch (historiaRuchow[ind][i - 1]) {
			case 'G': plansza[y][x] = SKRET_GP; break;
			case 'D': plansza[y][x] = SKRET_DP; break;
			case 'L': plansza[y][x] = CIALO_POZIOMO;
			};
			--x;
			break;
		}
		case 'P': {
			switch (historiaRuchow[ind][i - 1]) {
			case 'G': plansza[y][x] = SKRET_GL; break;
			case 'D': plansza[y][x] = SKRET_DL; break;
			case 'P': plansza[y][x] = CIALO_POZIOMO;
			};
			++x;
			break;
		}
		};
	}
}


//-----------------------------METODY KLASY CSNAKE------------------------------
CSnake::CSnake(unsigned int wielkosc, unsigned short ustawienie = 1)
	: dlugosc(1), efekt(NIC), czyZjadlOwoc(true), czyUmarl(false) {
	if (ustawienie != 3) {
		pozycjaGlowy = new CPosition(wielkosc, -1, ustawienie);
		pozycjaTylka = new CPosition(wielkosc, 1, ustawienie); //2, czyli o 2 przesuniecie tylka w dol      
		kierunekRuchu = GORA;
	}
	else {
		pozycjaGlowy = new CPosition(wielkosc, 1, ustawienie); //2, czyli o 2 przesuniecie glowy w dol
		pozycjaTylka = new CPosition(wielkosc, -1, ustawienie);
		kierunekRuchu = DOL;
	}
}

CSnake::~CSnake() {
	if (pozycjaGlowy != nullptr)
		delete pozycjaGlowy;
	if (pozycjaTylka != nullptr)
		delete pozycjaTylka;
}

//--------------------------ZWYKLE, ODDZIELNE FUNCKJE---------------------------

HFONT CreateLogFont(HDC hdcKontekst, const std::string& strNazwa, unsigned uWysPunkty,
	bool bPogrubienie = false, bool bKursywa = false, bool bPodkreslenie = false, bool bPrzekreslenie = false)
{
	if (strNazwa.empty() || uWysPunkty == 0)
		return NULL;

	/* tworzymy czcionkê */

	//deklarujemy i zerujemy strukturê LOGFONT    
	LOGFONT Font;
	ZeroMemory(&Font, sizeof(LOGFONT));

	//wype³niamy strukturê LOGFONT 
	CopyMemory(Font.lfFaceName, strNazwa.c_str(), strNazwa.size() + 1);
	Font.lfCharSet = DEFAULT_CHARSET;
	Font.lfHeight = -MulDiv(uWysPunkty,
		GetDeviceCaps(hdcKontekst, LOGPIXELSY), 72);
	Font.lfWeight = (bPogrubienie ? FW_BOLD : FW_NORMAL);
	Font.lfItalic = bKursywa;
	Font.lfUnderline = bPodkreslenie;
	Font.lfStrikeOut = bPrzekreslenie;

	//wywo³ujemy funkcjê CreateFontIndirect() 
	return CreateFontIndirect(&Font);
}

void WpisanieWynikuDoTablicy(unsigned wynik, POZIOM_TRUDNOSCI poziom_trudnosci) {
	fstream tablicaWynikow;
	string sciezkaDostepu;
	switch (poziom_trudnosci) {
	case LATWY:    sciezkaDostepu = "TabliceWynikow/tablicaWynikowLATWY.txt";     break;
	case NORMALNY: sciezkaDostepu = "TabliceWynikow/tablicaWynikowNORMALNY.txt";  break;
	case SREDNI:   sciezkaDostepu = "TabliceWynikow/tablicaWynikowSREDNI.txt";    break;
	case TRUDNY:   sciezkaDostepu = "TabliceWynikow/tablicaWynikowTRUDNY.txt";    break;
	case OP:       sciezkaDostepu = "TabliceWynikow/tablicaWynikowOP.txt";
	};
	tablicaWynikow.open(sciezkaDostepu.c_str(), ios::in | ios::out);

	stringstream zawartosc;
	string str;
	getline(tablicaWynikow, str); //pierwsze 2 linijki
	zawartosc << str << "\n";
	tablicaWynikow >> str;  zawartosc << str << "    ";
	tablicaWynikow >> str;  zawartosc << str << "\n";

	string miejsce;
	int wartosc, poprzedniaWartosc; //stara wartosc uzywana do przesuwania wynikow w dol
	bool wstawione = false;
	for (unsigned i = 1; i <= 15; ++i) {  //miejsca i wyniki
		tablicaWynikow >> miejsce;
		tablicaWynikow >> wartosc;
		zawartosc << miejsce;
		if (wynik > wartosc && wstawione == false) {
			if (i < 10) zawartosc << "  \t" << wynik << "\n";
			else zawartosc << "\t" << wynik << "\n";
			wstawione = true;
			poprzedniaWartosc = wartosc;
		}
		else if (wstawione == false) {
			if (i < 10) zawartosc << "  \t" << wartosc << "\n";
			else zawartosc << "\t" << wartosc << "\n";
		}
		else {
			if (i < 10) zawartosc << "  \t" << poprzedniaWartosc << "\n";
			else zawartosc << "\t" << poprzedniaWartosc << "\n";
			poprzedniaWartosc = wartosc;
		}
	}

	tablicaWynikow.clear();
	tablicaWynikow.seekp(0);
	tablicaWynikow.write(zawartosc.str().c_str(), zawartosc.str().length());

	tablicaWynikow.close();
}

string WypisanieWynikuZTablicy(POZIOM_TRUDNOSCI poziom_trudnosci) {
	fstream tablicaWynikow;

	string sciezkaDostepu;
	switch (poziom_trudnosci) {
	case LATWY:    sciezkaDostepu = "TabliceWynikow/tablicaWynikowLATWY.txt";     break;
	case NORMALNY: sciezkaDostepu = "TabliceWynikow/tablicaWynikowNORMALNY.txt";  break;
	case SREDNI:   sciezkaDostepu = "TabliceWynikow/tablicaWynikowSREDNI.txt";    break;
	case TRUDNY:   sciezkaDostepu = "TabliceWynikow/tablicaWynikowTRUDNY.txt";    break;
	case OP:       sciezkaDostepu = "TabliceWynikow/tablicaWynikowOP.txt";
	};
	tablicaWynikow.open(sciezkaDostepu.c_str(), ios::in | ios::out);

	stringstream zawartosc;
	string str;
	getline(tablicaWynikow, str);  //pierwsze 2 linijki
	zawartosc << str << "\n";
	tablicaWynikow >> str;  zawartosc << str << "    ";
	tablicaWynikow >> str;  zawartosc << str << "\n";

	for (unsigned i = 1; i <= 15; ++i) {  //miejsca i wyniki
		tablicaWynikow >> str;
		zawartosc << str;
		if (i < 10) zawartosc << "  \t";
		else zawartosc << "\t";
		tablicaWynikow >> str;
		zawartosc << str << "\n";
	}

	tablicaWynikow.close();
	return zawartosc.str();
}


