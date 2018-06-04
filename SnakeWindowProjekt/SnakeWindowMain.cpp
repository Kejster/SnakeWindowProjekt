#include "PrototypyWindow.h"


#define RYSOWANIE(hdcKontekst, nazwaBitMapy) { \
        HDC pamiec = CreateCompatibleDC(hdcKontekst); \
        DeleteObject( SelectObject(pamiec, nazwaBitMapy) ); \
        StretchBlt(hdcKontekst, 0, 0, 50, 50, pamiec, 0, 0, 50, 50, SRCCOPY); \
        DeleteDC(pamiec); \
}

#define RYSOWANIE_EX(hdcKontekst, nazwaBitMapy, szerokosc, wysokosc) { \
        HDC pamiec = CreateCompatibleDC(hdcKontekst); \
        DeleteObject( SelectObject(pamiec, nazwaBitMapy) ); \
        StretchBlt(hdcKontekst, 0, 0, szerokosc, wysokosc, pamiec, 0, 0, szerokosc, wysokosc, SRCCOPY); \
        DeleteDC(pamiec); \
}

#define RYSOWANIE_DEAD_GLOWA(indeksWeza) { \
           switch ( static_cast<char>(gra->waz[indeksWeza]->Kierunek()) ) { \
                  case 'G': { \
                       switch (gra->plansza->PodanieKierunkuOdKonca(indeksWeza, 1)) { \
                              case 'G': { RYSOWANIE(kontekstPod_okien, hbmpGlowaG_DEAD); break; } \
                              case 'L': { RYSOWANIE(kontekstPod_okien, hbmpGlowaSkretDL_G_DEAD); break; } \
                              case 'P': { RYSOWANIE(kontekstPod_okien, hbmpGlowaSkretDP_G_DEAD); break; } \
                       }; \
                       break; \
                  } \
                  case 'D':  { \
                       switch (gra->plansza->PodanieKierunkuOdKonca(indeksWeza, 1)) { \
                              case 'D': { RYSOWANIE(kontekstPod_okien, hbmpGlowaD_DEAD); break; } \
                              case 'L': { RYSOWANIE(kontekstPod_okien, hbmpGlowaSkretGL_D_DEAD); break; } \
                              case 'P': { RYSOWANIE(kontekstPod_okien, hbmpGlowaSkretGP_D_DEAD); break; } \
                       }; \
                       break; \
                  } \
                  case 'L':  { \
                       switch (gra->plansza->PodanieKierunkuOdKonca(indeksWeza, 1)) { \
                              case 'G': { RYSOWANIE(kontekstPod_okien, hbmpGlowaSkretGP_L_DEAD); break; } \
                              case 'D': { RYSOWANIE(kontekstPod_okien, hbmpGlowaSkretDP_L_DEAD); break; } \
                              case 'L': { RYSOWANIE(kontekstPod_okien, hbmpGlowaL_DEAD); break; } \
                       }; \
                       break; \
                  } \
                  case 'P':  { \
                       switch (gra->plansza->PodanieKierunkuOdKonca(indeksWeza, 1)) { \
                              case 'G': { RYSOWANIE(kontekstPod_okien, hbmpGlowaSkretGL_P_DEAD); break; } \
                              case 'D': { RYSOWANIE(kontekstPod_okien, hbmpGlowaSkretDL_P_DEAD); break; } \
                              case 'P': { RYSOWANIE(kontekstPod_okien, hbmpGlowaP_DEAD); break; } \
                       }; \
                       break; \
                  } \
           }; \
}

HBITMAP hbmpTrawa = (HBITMAP)LoadImage(NULL, "Grafika/hbmpTrawaTlo.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBRUSH hbrPedzelTrawy = CreatePatternBrush(hbmpTrawa);

HBITMAP hbmpScianaPoziomo = (HBITMAP)LoadImage(NULL, "Grafika/hbmpScianaPoziomo.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpScianaPionowo = (HBITMAP)LoadImage(NULL, "Grafika/hbmpScianaPionowo.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpScianaGL = (HBITMAP)LoadImage(NULL, "Grafika/hbmpScianaGL.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpScianaGP = (HBITMAP)LoadImage(NULL, "Grafika/hbmpScianaGP.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpScianaDL = (HBITMAP)LoadImage(NULL, "Grafika/hbmpScianaDL.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpScianaDP = (HBITMAP)LoadImage(NULL, "Grafika/hbmpScianaDP.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);


HBITMAP hbmpGlowaG = (HBITMAP)LoadImage(NULL, "Grafika/hbmpGlowaG.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpGlowaD = (HBITMAP)LoadImage(NULL, "Grafika/hbmpGlowaD.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpGlowaL = (HBITMAP)LoadImage(NULL, "Grafika/hbmpGlowaL.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpGlowaP = (HBITMAP)LoadImage(NULL, "Grafika/hbmpGlowaP.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

HBITMAP hbmpGlowaG_DEAD = (HBITMAP)LoadImage(NULL, "Grafika/hbmpGlowaG_DEAD.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpGlowaD_DEAD = (HBITMAP)LoadImage(NULL, "Grafika/hbmpGlowaD_DEAD.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpGlowaL_DEAD = (HBITMAP)LoadImage(NULL, "Grafika/hbmpGlowaL_DEAD.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpGlowaP_DEAD = (HBITMAP)LoadImage(NULL, "Grafika/hbmpGlowaP_DEAD.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

HBITMAP hbmpGlowaSkretGL_D_DEAD = (HBITMAP)LoadImage(NULL, "Grafika/hbmpGlowaSkretGL_D_DEAD.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpGlowaSkretGL_P_DEAD = (HBITMAP)LoadImage(NULL, "Grafika/hbmpGlowaSkretGL_P_DEAD.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpGlowaSkretGP_L_DEAD = (HBITMAP)LoadImage(NULL, "Grafika/hbmpGlowaSkretGP_L_DEAD.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpGlowaSkretGP_D_DEAD = (HBITMAP)LoadImage(NULL, "Grafika/hbmpGlowaSkretGP_D_DEAD.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpGlowaSkretDL_P_DEAD = (HBITMAP)LoadImage(NULL, "Grafika/hbmpGlowaSkretDL_P_DEAD.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpGlowaSkretDL_G_DEAD = (HBITMAP)LoadImage(NULL, "Grafika/hbmpGlowaSkretDL_G_DEAD.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpGlowaSkretDP_L_DEAD = (HBITMAP)LoadImage(NULL, "Grafika/hbmpGlowaSkretDP_L_DEAD.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpGlowaSkretDP_G_DEAD = (HBITMAP)LoadImage(NULL, "Grafika/hbmpGlowaSkretDP_G_DEAD.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

HBITMAP hbmpOgonG = (HBITMAP)LoadImage(NULL, "Grafika/hbmpOgonG.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpOgonD = (HBITMAP)LoadImage(NULL, "Grafika/hbmpOgonD.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpOgonL = (HBITMAP)LoadImage(NULL, "Grafika/hbmpOgonL.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpOgonP = (HBITMAP)LoadImage(NULL, "Grafika/hbmpOgonP.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

HBITMAP hbmpCialoPoziomo = (HBITMAP)LoadImage(NULL, "Grafika/hbmpCialoPoziomo.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpCialoPionowo = (HBITMAP)LoadImage(NULL, "Grafika/hbmpCialoPionowo.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

HBITMAP hbmpSkretGL = (HBITMAP)LoadImage(NULL, "Grafika/hbmpSkretGL.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpSkretGP = (HBITMAP)LoadImage(NULL, "Grafika/hbmpSkretGP.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpSkretDL = (HBITMAP)LoadImage(NULL, "Grafika/hbmpSkretDL.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpSkretDP = (HBITMAP)LoadImage(NULL, "Grafika/hbmpSkretDP.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

HBITMAP hbmpOwoc = (HBITMAP)LoadImage(NULL, "Grafika/hbmpOwoc.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpEfekt = (HBITMAP)LoadImage(NULL, "Grafika/hbmpEfekt.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpBlad = (HBITMAP)LoadImage(NULL, "Grafika/hbmpBlad.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

HBITMAP hbmpKlawiszW = (HBITMAP)LoadImage(NULL, "Grafika/hbmpKlawiszW.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpKlawiszS = (HBITMAP)LoadImage(NULL, "Grafika/hbmpKlawiszS.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpKlawiszA = (HBITMAP)LoadImage(NULL, "Grafika/hbmpKlawiszA.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpKlawiszD = (HBITMAP)LoadImage(NULL, "Grafika/hbmpKlawiszD.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpKlawiszSpacja = (HBITMAP)LoadImage(NULL, "Grafika/hbmpKlawiszSpacja.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

HBITMAP hbmpKlawiszW_Zaznaczone = (HBITMAP)LoadImage(NULL, "Grafika/hbmpKlawiszW_Zaznaczone.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpKlawiszS_Zaznaczone = (HBITMAP)LoadImage(NULL, "Grafika/hbmpKlawiszS_Zaznaczone.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpKlawiszA_Zaznaczone = (HBITMAP)LoadImage(NULL, "Grafika/hbmpKlawiszA_Zaznaczone.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpKlawiszD_Zaznaczone = (HBITMAP)LoadImage(NULL, "Grafika/hbmpKlawiszD_Zaznaczone.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpKlawiszSpacja_Zaznaczone = (HBITMAP)LoadImage(NULL, "Grafika/hbmpKlawiszSpacja_Zaznaczone.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

//--------------------------------2 GRACZ---------------------------------------
HBITMAP hbmpKlawiszStrzalka_G = (HBITMAP)LoadImage(NULL, "Grafika/hbmpKlawiszStrzalka_G.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpKlawiszStrzalka_D = (HBITMAP)LoadImage(NULL, "Grafika/hbmpKlawiszStrzalka_D.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpKlawiszStrzalka_L = (HBITMAP)LoadImage(NULL, "Grafika/hbmpKlawiszStrzalka_L.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpKlawiszStrzalka_P = (HBITMAP)LoadImage(NULL, "Grafika/hbmpKlawiszStrzalka_P.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

HBITMAP hbmpKlawiszStrzalka_G_Zaznaczone = (HBITMAP)LoadImage(NULL, "Grafika/hbmpKlawiszStrzalka_G_Zaznaczone.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpKlawiszStrzalka_D_Zaznaczone = (HBITMAP)LoadImage(NULL, "Grafika/hbmpKlawiszStrzalka_D_Zaznaczone.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpKlawiszStrzalka_L_Zaznaczone = (HBITMAP)LoadImage(NULL, "Grafika/hbmpKlawiszStrzalka_L_Zaznaczone.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP hbmpKlawiszStrzalka_P_Zaznaczone = (HBITMAP)LoadImage(NULL, "Grafika/hbmpKlawiszStrzalka_P_Zaznaczone.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

//--------------------------------------------------------------------------------------------------------------------

HINSTANCE instancja;
string MainWindowClassName = "mainWindow_SnakeWindow";
string GrafficWindowClassName = "GrafficWindow_SnakeWindow";
string InformWindowClassName = "InformWindow_SnakeWindow";

HWND hwndGlowneOkno;
HWND tablicaPol[13][13];
HWND tablicaKlawiszyMenu[5];
HWND tablicaPolInformacyjnych[3];
HWND tablicaPoczatkowychOkien[7];

HWND tablicaKlawiszyMenu_2[5]; //dla 2 gracza
HWND tablicaPolInformacyjnych_2;

void TworzenieOkien(short);  //funkcja pod WinMain()


POZIOM_TRUDNOSCI poziom_trudnosci;
CGame* gra;
POLE** pole;
KIERUNEK_RUCHU nowyKierunek, nowyKierunek_2;
bool wybieranieIluGraczy = false;
unsigned short iluGraczy;

bool timer2 = false;
UINT IDtimera2 = NULL; //by sprawdzic czy tyka timer
clock_t poczatekOdliczania, czasZatrzymany;
double czasOdliczany;
stringstream odliczanie;
double odliczanyCzas;
bool pauza = false, czyZamknacOkno = false; //oba wstrzymuja timer efektu
bool czyTeSameUstawienia = false;

bool bylEfekt_DO_TYLU = false, efektGlitcha = false;
bool odwrotnieKierunki = false;
EFEKTY poprzedniEfekt = NIC;
stringstream napisOwocow, napisOwocow_2;
bool koniecKoncowegoRysowania = false;
bool odNowa = false, wybieranieTrudnosci = true;

//------------------------------------------------------------------------------

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT uMSG, WPARAM wParam, LPARAM lParam) {
	switch (uMSG)
	{
	case WM_COMMAND: { //okienka poczatkowe - wybor poziomu trudnosci
		bool przyciskiMenu = true;
		switch (wParam) {
		case 100: {  string tablicaWynikow = WypisanieWynikuZTablicy(LATWY); //wpisywanie wyniku 1 gracza
			MessageBox(NULL, tablicaWynikow.c_str(), "TABLICA WYNIKOW POZIOMU: LATWY",
				MB_ICONINFORMATION | MB_OK);
			break;
		}
		case 101: {  string tablicaWynikow = WypisanieWynikuZTablicy(NORMALNY); //wpisywanie wyniku 1 gracza
			MessageBox(NULL, tablicaWynikow.c_str(), "TABLICA WYNIKOW POZIOMU: NORMALNY",
				MB_ICONINFORMATION | MB_OK);
			break;
		}
		case 102: {  string tablicaWynikow = WypisanieWynikuZTablicy(SREDNI); //wpisywanie wyniku 1 gracza
			MessageBox(NULL, tablicaWynikow.c_str(), "TABLICA WYNIKOW POZIOMU: SREDNI",
				MB_ICONINFORMATION | MB_OK);
			break;
		}
		case 103: {  string tablicaWynikow = WypisanieWynikuZTablicy(TRUDNY); //wpisywanie wyniku 1 gracza
			MessageBox(NULL, tablicaWynikow.c_str(), "TABLICA WYNIKOW POZIOMU: TRUDNY",
				MB_ICONINFORMATION | MB_OK);
			break;
		}
		case 104: {  string tablicaWynikow = WypisanieWynikuZTablicy(OP); //wpisywanie wyniku 1 gracza
			MessageBox(NULL, tablicaWynikow.c_str(), "TABLICA WYNIKOW POZIOMU: OP",
				MB_ICONINFORMATION | MB_OK);
			break;
		}
		default: przyciskiMenu = false; //nie byly to indeksy przyciskow menu                          
		};
		if (przyciskiMenu == true) return 0; // reszta kodu nie dotyczy przyciskow menu 

		if (odNowa == false) {
			if (wybieranieIluGraczy == false) {
				if (wParam == 6)  // ustawienia te same
					czyTeSameUstawienia = true;
				else {
					switch (wParam) {
					case 1: poziom_trudnosci = LATWY;    break;
					case 2: poziom_trudnosci = NORMALNY; break;
					case 3: poziom_trudnosci = SREDNI;   break;
					case 4: poziom_trudnosci = TRUDNY;   break;
					case 5: poziom_trudnosci = OP;       break;
					};

					ShowWindow(tablicaPoczatkowychOkien[1], SW_HIDE);
					ShowWindow(tablicaPoczatkowychOkien[4], SW_HIDE);
					ShowWindow(tablicaPoczatkowychOkien[5], SW_HIDE);

					SetWindowText(tablicaPoczatkowychOkien[0], "\n\tProsze wybrac ilu bedzie gralo osob:");
					SetWindowText(tablicaPoczatkowychOkien[2], "1");
					SetWindowText(tablicaPoczatkowychOkien[3], "2");

					wybieranieIluGraczy = true;
					return 0;
				}
			}
			if (czyTeSameUstawienia == false) // jesli sa nowe ustawienia, to i pyta czy inna ilosc graczy
				iluGraczy = (wParam == 2) ? 1 : 2; // 2 przycisk oznacza 1 gracza, a 3 -> 2 graczy!
			wybieranieIluGraczy = false;
			czyTeSameUstawienia = false;

			TworzenieOkien(iluGraczy);

			gra = new CGame(13, poziom_trudnosci, iluGraczy);
			pole = gra->plansza->PodaniePlanszy();
			wybieranieTrudnosci = false;

			for (unsigned i = 0; i < 7; ++i)
				ShowWindow(tablicaPoczatkowychOkien[i], SW_HIDE);
			//-----------------------------------------------------------------     
			for (unsigned i = 0; i < 13; ++i)
				for (unsigned j = 0; j < 13; ++j)
					ShowWindow(tablicaPol[i][j], SW_SHOW);

			for (unsigned i = 0; i < 5; ++i)
				ShowWindow(tablicaKlawiszyMenu[i], SW_SHOW);

			ShowWindow(tablicaPolInformacyjnych[0], SW_SHOW);
			ShowWindow(tablicaPolInformacyjnych[1], SW_SHOW);

			MessageBox(NULL, "Aby rozpoczac gre nacisnij OK.", "START",
				MB_ICONINFORMATION | MB_TASKMODAL | MB_OK);
			nowyKierunek = GORA;
			nowyKierunek_2 = DOL;
			SetTimer(hwndGlowneOkno, 1, 1, NULL);
		}
		else {
			wybieranieTrudnosci = true; //za chwile bedzie wybierany nowy poziom
			delete gra;
			gra = NULL;  //kasujemy stara gre i tworzymy nowa

			for (unsigned i = 0; i < 13; ++i)
				for (unsigned j = 0; j < 13; ++j)
					ShowWindow(tablicaPol[i][j], SW_HIDE);

			for (unsigned i = 0; i < 5; ++i)
				ShowWindow(tablicaKlawiszyMenu[i], SW_HIDE);

			ShowWindow(tablicaPolInformacyjnych[0], SW_HIDE);
			ShowWindow(tablicaPolInformacyjnych[1], SW_HIDE);
			ShowWindow(tablicaPolInformacyjnych[2], SW_HIDE);

			//--------------------------------------------------------------
			ShowWindow(tablicaPolInformacyjnych_2, SW_HIDE);  //okienka 2 gracza
			for (unsigned i = 0; i < 5; ++i)
				ShowWindow(tablicaKlawiszyMenu_2[i], SW_HIDE);
			//--------------------------------------------------------------
			SetWindowText(tablicaPoczatkowychOkien[0], "\n\tProsze wybrac stopien trudnosci:");
			SetWindowText(tablicaPoczatkowychOkien[2], "NORMALNY");
			SetWindowText(tablicaPoczatkowychOkien[3], "SREDNI");
			for (unsigned i = 0; i < 7; ++i)
				ShowWindow(tablicaPoczatkowychOkien[i], SW_SHOW);

			//ustawienie od nowa wartosci
			timer2 = false;
			pauza = false;
			czyZamknacOkno = false;
			bylEfekt_DO_TYLU = false;  efektGlitcha = false;
			odwrotnieKierunki = false;
			poprzedniEfekt = NIC;
			koniecKoncowegoRysowania = false;
			odNowa = false;
		}

		return 0;
	}
	case WM_TIMER: {
		switch ((UINT)wParam) {
		case 1: {
			if (efektGlitcha == true) gra->waz[0]->Efekt(DO_TYLU);

			if (gra->waz[0]->CzyZjadlOwoc() == true)
				gra->LosowanieObiektow(0);

			if (bylEfekt_DO_TYLU == false && koniecKoncowegoRysowania == false) {
				if (odwrotnieKierunki == false) {
					switch (nowyKierunek) {
					case GORA:  if (gra->waz[0]->Kierunek() != DOL)    gra->waz[0]->ZmianaKierunku(GORA);   break;
					case DOL:   if (gra->waz[0]->Kierunek() != GORA)   gra->waz[0]->ZmianaKierunku(DOL);    break;
					case LEWO:  if (gra->waz[0]->Kierunek() != PRAWO)  gra->waz[0]->ZmianaKierunku(LEWO);   break;
					case PRAWO: if (gra->waz[0]->Kierunek() != LEWO)   gra->waz[0]->ZmianaKierunku(PRAWO);  break;
					};
				}
				else               //ODWROTNIE!
					switch (nowyKierunek) {
					case GORA:  if (gra->waz[0]->Kierunek() != GORA)   gra->waz[0]->ZmianaKierunku(DOL);   break;
					case DOL:   if (gra->waz[0]->Kierunek() != DOL)    gra->waz[0]->ZmianaKierunku(GORA);  break;
					case LEWO:  if (gra->waz[0]->Kierunek() != LEWO)   gra->waz[0]->ZmianaKierunku(PRAWO); break;
					case PRAWO: if (gra->waz[0]->Kierunek() != PRAWO)  gra->waz[0]->ZmianaKierunku(LEWO);  break;
					};
			}
			else nowyKierunek = gra->waz[0]->Kierunek();

			if (gra->waz[1] != NULL) { // ruch dla 2 gracza
				if (gra->waz[1]->CzyZjadlOwoc() == true)
					gra->LosowanieObiektow(1);

				if (bylEfekt_DO_TYLU == false && koniecKoncowegoRysowania == false) {
					if (odwrotnieKierunki == false) {
						switch (nowyKierunek_2) {
						case GORA:  if (gra->waz[1]->Kierunek() != DOL)   gra->waz[1]->ZmianaKierunku(GORA);   break;
						case DOL:   if (gra->waz[1]->Kierunek() != GORA)  gra->waz[1]->ZmianaKierunku(DOL);    break;
						case LEWO:  if (gra->waz[1]->Kierunek() != PRAWO) gra->waz[1]->ZmianaKierunku(LEWO);   break;
						case PRAWO: if (gra->waz[1]->Kierunek() != LEWO)  gra->waz[1]->ZmianaKierunku(PRAWO);  break;
						};
					}
					else               //ODWROTNIE!
						switch (nowyKierunek_2) {
						case GORA:  if (gra->waz[1]->Kierunek() != GORA)   gra->waz[1]->ZmianaKierunku(DOL);   break;
						case DOL:   if (gra->waz[1]->Kierunek() != DOL)    gra->waz[1]->ZmianaKierunku(GORA);  break;
						case LEWO:  if (gra->waz[1]->Kierunek() != LEWO)   gra->waz[1]->ZmianaKierunku(PRAWO); break;
						case PRAWO: if (gra->waz[1]->Kierunek() != PRAWO)  gra->waz[1]->ZmianaKierunku(LEWO);  break;
						};
				}
				else nowyKierunek_2 = gra->waz[1]->Kierunek();
			}

			//SPRAWDZANIE STANU GRY!
			gra->SprawdzanieRuchu(0);
			if (gra->waz[1] != NULL) gra->SprawdzanieRuchu(1);  //sprawdzanie ruchu 2 gracza 

			if (gra->PodanieStanuGry() == KONIEC) {  //operacje koncowe
				if (koniecKoncowegoRysowania == true) {
					KillTimer(hwndGlowneOkno, 1);
					KillTimer(hwndGlowneOkno, 2);
					KillTimer(hwndGlowneOkno, 3);

					string wynik;
					if (gra->waz[1] == NULL) {
						wynik = napisOwocow.str();
						wynik += "\n\nCzy chcesz zagrac jeszcze raz?";
						wynik += "\nNacisnij 'Tak', jesli tak, lub 'Nie' aby zakonczyc program.";
					}
					else {
						if (gra->waz[0]->CzyUmarl() == true && gra->waz[1]->CzyUmarl() == true)
							wynik = "REMIS";
						else if (gra->waz[0]->CzyUmarl() == true)
							wynik = "!_WYGRAL GRACZ PO LEWEJ STRONIE_!";
						else wynik = "!_WYGRAL GRACZ PO PRAWEJ STRONIE_!";

						wynik += "\n\nCzy chcecie zagrac jeszcze raz?";
						wynik += "\nNacisnijcie 'Tak', jesli tak, lub 'Nie' aby zakonczyc program.";
					}

					//--------------------------------------------------
					WpisanieWynikuDoTablicy(gra->waz[0]->Dlugosc() - 1, poziom_trudnosci); //wpisywanie wyniku 1 gracza
					if (gra->waz[1] != NULL)
						WpisanieWynikuDoTablicy(gra->waz[1]->Dlugosc() - 1, poziom_trudnosci); // i ewentualnie 2 gracza                         
																							   //--------------------------------------------------

					if (MessageBox(NULL, wynik.c_str(), "Koniec Gry :<",
						MB_ICONQUESTION | MB_TASKMODAL | MB_YESNO) == IDYES) {
						odNowa = true;
						SendMessage(hwndGlowneOkno, WM_COMMAND, NULL, NULL);
						return 0;
					}
					else {
						SendMessage(hwndGlowneOkno, WM_DESTROY, NULL, NULL);
						return 0;
					}
				}
				else {
					koniecKoncowegoRysowania = true;
					if (gra->waz[0]->CzyUmarl() == true)
						pole[gra->waz[0]->pgy()][gra->waz[0]->pgx()] = GLOWA_DEAD;
					if (gra->waz[1] != NULL && gra->waz[1]->CzyUmarl() == true)
						pole[gra->waz[1]->pgy()][gra->waz[1]->pgx()] = GLOWA_DEAD;

					InvalidateRect(hwndGlowneOkno, NULL, FALSE);
				}
			}
			else {  // dalsze czynnosci podczas rozgrywki                    
				if (gra->waz[0]->Efekt() == DO_TYLU) { // jesli 1 zgarnal efekt DO_TYLU, to 2 tez dostaje
					if (gra->waz[1] != NULL) gra->waz[1]->Efekt(DO_TYLU);
					bylEfekt_DO_TYLU = true;
				}
				else bylEfekt_DO_TYLU = false;

				gra->plansza->ZaznaczanieRuchu_EX(0);  //funkcje rysujace
				if (gra->waz[1] != NULL) gra->plansza->ZaznaczanieRuchu_EX(1);

				InvalidateRect(hwndGlowneOkno, NULL, FALSE);

				//-----------------------------------------------------
				//algorytm wykonywajacy operacje na efektach
				if (efektGlitcha == false && gra->waz[0]->Efekt() != NIC) {
					if (timer2 == false || gra->waz[0]->Efekt() != poprzedniEfekt) {  //timer efektu
						IDtimera2 = SetTimer(hwndGlowneOkno, 2, 4500, NULL);
						timer2 = true;

						poczatekOdliczania = clock();
						SetTimer(hwndGlowneOkno, 3, 10, NULL);
						ShowWindow(tablicaPolInformacyjnych[2], SW_SHOW);
						czasZatrzymany = static_cast<clock_t>(0.0);
					}
					odliczanyCzas = 4500;
					switch (gra->waz[0]->Efekt()) {  //nowy czas na ruch, z uwzglednieniem efektow
					case PRZYSPIESZENIE: { SetTimer(hwndGlowneOkno, 1, gra->Okres() / 2, NULL);
						poprzedniEfekt = PRZYSPIESZENIE;  break; }
					case SPOWOLNIENIE: { SetTimer(hwndGlowneOkno, 1, gra->Okres() * 2, NULL);
						poprzedniEfekt = SPOWOLNIENIE;    break; }
					case ODWROTNIE_KIERUNKI: { odwrotnieKierunki = true;
						poprzedniEfekt = ODWROTNIE_KIERUNKI;  break; }
					case GLITCH: {
						odliczanyCzas = rand() % 1501 + 1000;
						IDtimera2 = SetTimer(hwndGlowneOkno, 2, odliczanyCzas, NULL);
						efektGlitcha = true;
						poprzedniEfekt = DO_TYLU; //polega na wielkrotnym wykonaniu tego efektu
						break;
					}
					};
					odliczanyCzas /= 1000;
				}
				else {
					if (efektGlitcha == false) {
						SetTimer(hwndGlowneOkno, 1, gra->Okres(), NULL); //normalny czas timera
						if (IDtimera2 != NULL)
							SetTimer(hwndGlowneOkno, 2, 1, NULL); //wysyla by wylaczyc byc moze dzialajacy jeszcze timer_3
					}
					else SetTimer(hwndGlowneOkno, 1, 50, NULL);
				}
			}

			break;
		}
		case 2: {  //wylancza po okreslonym czasie efekty
			if (pauza == false && czyZamknacOkno == false) {
				gra->waz[0]->ResetEfektu();
				if (gra->waz[1] != NULL) gra->waz[1]->ResetEfektu();

				odwrotnieKierunki = false;
				efektGlitcha = false;

				timer2 = false;
				KillTimer(hwndGlowneOkno, 2);

				KillTimer(hwndGlowneOkno, 3);
				ShowWindow(tablicaPolInformacyjnych[2], SW_HIDE);
			}

			break;
		}
		case 3: {
			odliczanie.str(std::string());
			odliczanie.clear();
			czasOdliczany = (odliczanyCzas - (clock() - poczatekOdliczania) / (double)CLOCKS_PER_SEC);
			odliczanie << "Pozostalo: " << czasOdliczany << "s";
			SendMessage(tablicaPolInformacyjnych[2], WM_PAINT, NULL, NULL);

			break;
		}
		};
		return 0;
	}
	case WM_LBUTTONDOWN: {
		if (hwnd == tablicaKlawiszyMenu[0]) nowyKierunek = GORA;
		else if (hwnd == tablicaKlawiszyMenu[1]) nowyKierunek = LEWO;
		else if (hwnd == tablicaKlawiszyMenu[2]) nowyKierunek = DOL;
		else if (hwnd == tablicaKlawiszyMenu[3]) nowyKierunek = PRAWO;
		else if (hwnd == tablicaKlawiszyMenu[4] || hwnd == tablicaKlawiszyMenu_2[4])
			SendMessage(hwndGlowneOkno, WM_KEYDOWN, VK_SPACE, NULL);
		else if (hwnd == tablicaKlawiszyMenu_2[0]) nowyKierunek_2 = GORA;
		else if (hwnd == tablicaKlawiszyMenu_2[1]) nowyKierunek_2 = LEWO;
		else if (hwnd == tablicaKlawiszyMenu_2[2]) nowyKierunek_2 = DOL;
		else if (hwnd == tablicaKlawiszyMenu_2[3]) nowyKierunek_2 = PRAWO;

		break;
	}
	case WM_KEYDOWN: {
		switch (wParam) {
		case 0x57:      if (gra->waz[1] == NULL) nowyKierunek = GORA;  else nowyKierunek_2 = GORA;  break;  //W
		case VK_UP:     nowyKierunek = GORA;  break;  //STRZALKA W GORE
		case 0x53:      if (gra->waz[1] == NULL) nowyKierunek = DOL;   else nowyKierunek_2 = DOL;   break;  //S
		case VK_DOWN:   nowyKierunek = DOL;   break;  //STRZALKA W DOL
		case 0x41:      if (gra->waz[1] == NULL) nowyKierunek = LEWO;  else nowyKierunek_2 = LEWO;  break;  //A
		case VK_LEFT:   nowyKierunek = LEWO;  break;  //STRZALKA W LEWO
		case 0x44:      if (gra->waz[1] == NULL) nowyKierunek = PRAWO; else nowyKierunek_2 = PRAWO; break;  //D 
		case VK_RIGHT:  nowyKierunek = PRAWO; break;  //STRZALKA W PRAWO
		case VK_SPACE: {
			if (wybieranieTrudnosci == false) {
				KillTimer(hwndGlowneOkno, 1);
				KillTimer(hwndGlowneOkno, 3);
				czasZatrzymany = clock();

				pauza = true;  // do zaznaczania okienka spacji
				InvalidateRect(hwndGlowneOkno, NULL, FALSE);
				MessageBox(NULL, "Nacisnij OK aby kontynuowac.", "Wstrzymanie Gry",
					MB_ICONINFORMATION | MB_TASKMODAL | MB_OK);
				pauza = false;
				InvalidateRect(hwndGlowneOkno, NULL, FALSE);

				if (IDtimera2 != NULL) {
					SetTimer(hwndGlowneOkno, 2, czasOdliczany * 1000, NULL);
					SetTimer(hwndGlowneOkno, 3, 10, NULL);
					poczatekOdliczania += clock() - czasZatrzymany;
				}
				SetTimer(hwndGlowneOkno, 1, 1, NULL);
			}
			break;
		}
		case VK_ESCAPE: SendMessage(hwnd, WM_CLOSE, NULL, NULL);  break;
		};
		break;
	}
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hwnd, &ps);
		//-----------------------------------------------------------------

		if (wybieranieTrudnosci == true) {
			EndPaint(hwnd, &ps);
			return 0;
		}

		if (hwnd == tablicaPolInformacyjnych[0]) {  //okienko ile zjedzono owocow; str jest zadeklarowyny jako globalny
			napisOwocow.str(std::string());
			napisOwocow.clear();
			napisOwocow << "Zjedzono " << gra->waz[0]->Dlugosc() - 1 << " owocow!";

			RECT poleKontekstu;
			HDC kontekst = GetDC(tablicaPolInformacyjnych[0]);
			HFONT czcionka = CreateLogFont(kontekst, "Verdana", 11, true, false, false, false);
			DeleteObject(SelectObject(kontekst, czcionka));
			GetClientRect(tablicaPolInformacyjnych[0], &poleKontekstu);
			DrawText(kontekst, napisOwocow.str().c_str(), napisOwocow.str().length(),
				&poleKontekstu, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
			DeleteDC(kontekst);
		}
		else if (hwnd == tablicaPolInformacyjnych[1]) {  //Okienko efektow
			HDC kontekst = GetDC(tablicaPolInformacyjnych[1]);
			HFONT czcionka;

			string napisEfektu;
			if (efektGlitcha == true) gra->waz[0]->Efekt(GLITCH);
			if (gra->waz[0]->Efekt() != NIC) {
				if (gra->waz[1] == NULL)
					czcionka = CreateLogFont(kontekst, "Verdana", 11, true, false, true, false);
				else czcionka = CreateLogFont(kontekst, "Verdana", 15, true, false, true, false);
				SetTextColor(kontekst, RGB(255, 0, 0));
				switch (gra->waz[0]->Efekt()) {
				case SPOWOLNIENIE:       napisEfektu = "SPOWOLNIENIE";       break;
				case PRZYSPIESZENIE:     napisEfektu = "PRZYSPIESZENIE";     break;
				case ODWROTNIE_KIERUNKI: napisEfektu = "ODWROTNE KIERUNKI";  break;
				case GLITCH:             napisEfektu = ">: !?GLITCH?! :<";   break;

				};
			}
			else {
				napisEfektu = "Nie ma efektu.";
				czcionka = CreateLogFont(kontekst, "Verdana", 9, false, false, false, false);
			}
			DeleteObject(SelectObject(kontekst, czcionka));

			RECT poleKontekstu;
			GetClientRect(tablicaPolInformacyjnych[1], &poleKontekstu);
			if (gra->waz[1] == NULL)
				DrawText(kontekst, napisEfektu.c_str(), napisEfektu.length(),
					&poleKontekstu, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
			else if (gra->waz[0]->Efekt() != NIC)
				DrawText(kontekst, napisEfektu.c_str(), napisEfektu.length(),
					&poleKontekstu, DT_SINGLELINE | DT_CENTER);

			DeleteDC(kontekst);
		}
		else if (hwnd == tablicaPolInformacyjnych[2]) {
			RECT poleKontekstu;
			HDC kontekst = GetDC(tablicaPolInformacyjnych[2]);

			HFONT czcionka = CreateLogFont(kontekst, "Verdana", 11, true, false, false, false);
			DeleteObject(SelectObject(kontekst, czcionka));
			SetTextColor(kontekst, RGB(255, 0, 0));

			GetClientRect(tablicaPolInformacyjnych[2], &poleKontekstu);
			DrawText(kontekst, odliczanie.str().c_str(), odliczanie.str().length(),
				&poleKontekstu, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
			DeleteDC(kontekst);
		}
		else if (gra->waz[1] != NULL && hwnd == tablicaPolInformacyjnych_2) {
			napisOwocow_2.str(std::string()); //okienko ile zjedzono owocow; DLA 2 GRACZA!
			napisOwocow_2.clear();
			napisOwocow_2 << "Zjedzono " << gra->waz[1]->Dlugosc() - 1 << " owocow!";

			RECT poleKontekstu;
			HDC kontekst = GetDC(tablicaPolInformacyjnych_2);
			HFONT czcionka = CreateLogFont(kontekst, "Verdana", 11, true, false, false, false);
			DeleteObject(SelectObject(kontekst, czcionka));
			GetClientRect(tablicaPolInformacyjnych_2, &poleKontekstu);
			DrawText(kontekst, napisOwocow_2.str().c_str(), napisOwocow.str().length(),
				&poleKontekstu, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
			DeleteDC(kontekst);
		}

		//-----------------------------------------------------------------
		EndPaint(hwnd, &ps);

		if (hwnd == hwndGlowneOkno) {
			for (unsigned i = 0; i < 13; ++i)
				for (unsigned j = 0; j < 13; ++j) {
					HDC kontekstPod_okien = GetDC(tablicaPol[j][i]); //odwrotnie bo okienko jest "odwrocone"
					switch (pole[i][j]) {
					case PUSTE: { RYSOWANIE(kontekstPod_okien, hbmpTrawa); break; }

					case SCIANA_POZIOMO: { RYSOWANIE(kontekstPod_okien, hbmpScianaPoziomo); break; }
					case SCIANA_PIONOWO: { RYSOWANIE(kontekstPod_okien, hbmpScianaPionowo); break; }
					case SCIANA_GL: { RYSOWANIE(kontekstPod_okien, hbmpScianaGL); break; }
					case SCIANA_GP: { RYSOWANIE(kontekstPod_okien, hbmpScianaGP); break; }
					case SCIANA_DL: { RYSOWANIE(kontekstPod_okien, hbmpScianaDL); break; }
					case SCIANA_DP: { RYSOWANIE(kontekstPod_okien, hbmpScianaDP); break; }

					case CIALO_POZIOMO: { RYSOWANIE(kontekstPod_okien, hbmpCialoPoziomo); break; }
					case CIALO_PIONOWO: { RYSOWANIE(kontekstPod_okien, hbmpCialoPionowo); break; }

					case SKRET_GL: { RYSOWANIE(kontekstPod_okien, hbmpSkretGL); break; }
					case SKRET_GP: { RYSOWANIE(kontekstPod_okien, hbmpSkretGP); break; }
					case SKRET_DL: { RYSOWANIE(kontekstPod_okien, hbmpSkretDL); break; }
					case SKRET_DP: { RYSOWANIE(kontekstPod_okien, hbmpSkretDP); break; }

					case GLOWA_G: { RYSOWANIE(kontekstPod_okien, hbmpGlowaG); break; }
					case GLOWA_D: { RYSOWANIE(kontekstPod_okien, hbmpGlowaD); break; }
					case GLOWA_L: { RYSOWANIE(kontekstPod_okien, hbmpGlowaL); break; }
					case GLOWA_P: { RYSOWANIE(kontekstPod_okien, hbmpGlowaP); break; }

					case OGON_G: { RYSOWANIE(kontekstPod_okien, hbmpOgonG); break; }
					case OGON_D: { RYSOWANIE(kontekstPod_okien, hbmpOgonD); break; }
					case OGON_L: { RYSOWANIE(kontekstPod_okien, hbmpOgonL); break; }
					case OGON_P: { RYSOWANIE(kontekstPod_okien, hbmpOgonP); break; }

					case OWOC: { RYSOWANIE(kontekstPod_okien, hbmpOwoc); break; }
					case EFEKT: { RYSOWANIE(kontekstPod_okien, hbmpEfekt); break; }

					case GLOWA_DEAD: {
						if (gra->waz[0]->pgx() == j && gra->waz[0]->pgy() == i) {
							RYSOWANIE_DEAD_GLOWA(0);
						}
						else if (gra->waz[1] != NULL) RYSOWANIE_DEAD_GLOWA(1);

						break;
					}

					default: RYSOWANIE(kontekstPod_okien, hbmpBlad);
					};
					DeleteDC(kontekstPod_okien);
				}
			for (unsigned i = 0; i < 5; ++i) {
				HDC kontekstKlawiszyMenu = GetDC(tablicaKlawiszyMenu[i]);
				switch (i) {
				case 0: { if (gra->waz[0]->Kierunek() != GORA) {
					RYSOWANIE_EX(kontekstKlawiszyMenu, hbmpKlawiszStrzalka_G, 60, 60); break;
				}
						else { RYSOWANIE_EX(kontekstKlawiszyMenu, hbmpKlawiszStrzalka_G_Zaznaczone, 60, 60); break; }
				}
				case 1: { if (gra->waz[0]->Kierunek() != LEWO) {
					RYSOWANIE_EX(kontekstKlawiszyMenu, hbmpKlawiszStrzalka_L, 60, 60); break;
				}
						else { RYSOWANIE_EX(kontekstKlawiszyMenu, hbmpKlawiszStrzalka_L_Zaznaczone, 60, 60); break; }
				}
				case 2: { if (gra->waz[0]->Kierunek() != DOL) {
					RYSOWANIE_EX(kontekstKlawiszyMenu, hbmpKlawiszStrzalka_D, 60, 60); break;
				}
						else { RYSOWANIE_EX(kontekstKlawiszyMenu, hbmpKlawiszStrzalka_D_Zaznaczone, 60, 60); break; }
				}
				case 3: { if (gra->waz[0]->Kierunek() != PRAWO) {
					RYSOWANIE_EX(kontekstKlawiszyMenu, hbmpKlawiszStrzalka_P, 60, 60); break;
				}
						else { RYSOWANIE_EX(kontekstKlawiszyMenu, hbmpKlawiszStrzalka_P_Zaznaczone, 60, 60); break; }
				}
				case 4: { if (pauza == false) {
					RYSOWANIE_EX(kontekstKlawiszyMenu, hbmpKlawiszSpacja, 200, 60); break;
				}
						else { RYSOWANIE_EX(kontekstKlawiszyMenu, hbmpKlawiszSpacja_Zaznaczone, 200, 60); break; }
				}

				default: RYSOWANIE(kontekstKlawiszyMenu, hbmpBlad);
				};
				DeleteDC(kontekstKlawiszyMenu);
			}

			if (gra->waz[1] != NULL) {
				for (unsigned i = 0; i < 5; ++i) {
					HDC kontekstKlawiszyMenu = GetDC(tablicaKlawiszyMenu_2[i]);
					switch (i) {
					case 0: { if (gra->waz[1]->Kierunek() != GORA) {
						RYSOWANIE_EX(kontekstKlawiszyMenu, hbmpKlawiszW, 60, 60); break;
					}
							else { RYSOWANIE_EX(kontekstKlawiszyMenu, hbmpKlawiszW_Zaznaczone, 60, 60); break; }
					}
					case 1: { if (gra->waz[1]->Kierunek() != LEWO) {
						RYSOWANIE_EX(kontekstKlawiszyMenu, hbmpKlawiszA, 60, 60); break;
					}
							else { RYSOWANIE_EX(kontekstKlawiszyMenu, hbmpKlawiszA_Zaznaczone, 60, 60); break; }
					}
					case 2: { if (gra->waz[1]->Kierunek() != DOL) {
						RYSOWANIE_EX(kontekstKlawiszyMenu, hbmpKlawiszS, 60, 60); break;
					}
							else { RYSOWANIE_EX(kontekstKlawiszyMenu, hbmpKlawiszS_Zaznaczone, 60, 60); break; }
					}
					case 3: { if (gra->waz[1]->Kierunek() != PRAWO) {
						RYSOWANIE_EX(kontekstKlawiszyMenu, hbmpKlawiszD, 60, 60); break;
					}
							else { RYSOWANIE_EX(kontekstKlawiszyMenu, hbmpKlawiszD_Zaznaczone, 60, 60); break; }
					}
					case 4: { if (pauza == false) {
						RYSOWANIE_EX(kontekstKlawiszyMenu, hbmpKlawiszSpacja, 200, 60); break;
					}
							else { RYSOWANIE_EX(kontekstKlawiszyMenu, hbmpKlawiszSpacja_Zaznaczone, 200, 60); break; }
					}

					default: RYSOWANIE(kontekstKlawiszyMenu, hbmpBlad);
					};
					DeleteDC(kontekstKlawiszyMenu);
				}
			}

			return 0;
		}
		else return 0;
	}
	case WM_CLOSE: {
		czyZamknacOkno = true;
		KillTimer(hwndGlowneOkno, 1);
		KillTimer(hwndGlowneOkno, 3);
		czasZatrzymany = clock();

		if (MessageBox(NULL, "Na pewno chcesz wylaczyc gre?", "Ostrzezenie",
			MB_ICONWARNING | MB_TASKMODAL | MB_YESNO) == IDYES)
			return DefWindowProc(hwnd, uMSG, wParam, lParam);
		else if (wybieranieTrudnosci == false) {
			if (IDtimera2 != NULL) {
				SetTimer(hwndGlowneOkno, 2, czasOdliczany * 1000, NULL);
				SetTimer(hwndGlowneOkno, 3, 10, NULL);
				poczatekOdliczania += clock() - czasZatrzymany;
			}
			SetTimer(hwndGlowneOkno, 1, 1, NULL);

			czyZamknacOkno = false;
			return 0;
		}
		else return 0;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		return 0;
	}
	};
	return DefWindowProc(hwnd, uMSG, wParam, lParam); //dzialania domyslne
}


//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------


int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil) {
	instancja = hThisInstance;
	HMENU hMenu = LoadMenu(hThisInstance, MAKEINTRESOURCE(200));

	WNDCLASSEX wndcGlowneOkno;

	ZeroMemory(&wndcGlowneOkno, sizeof(WNDCLASSEX));
	wndcGlowneOkno.cbSize = sizeof(WNDCLASSEX);
	wndcGlowneOkno.hInstance = hThisInstance;
	wndcGlowneOkno.lpszClassName = MainWindowClassName.c_str();
	wndcGlowneOkno.lpfnWndProc = WindowProcedure;

	wndcGlowneOkno.hIcon = (HICON)LoadImage(NULL, "Grafika/Ikona.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wndcGlowneOkno.hIconSm = (HICON)LoadImage(NULL, "Grafika/Ikona.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wndcGlowneOkno.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndcGlowneOkno.hbrBackground = hbrPedzelTrawy;

	if (!RegisterClassEx(&wndcGlowneOkno)) {
		MessageBox(NULL, "rejestracja pola glownego nie powiodlo sie!", "Wiadomoœæ", MB_ICONERROR | MB_OK);
		return 1;
	}

	//--------------------------------------------------------------------------

	WNDCLASSEX wndcPolaPodGrafike;

	ZeroMemory(&wndcPolaPodGrafike, sizeof(WNDCLASSEX));
	wndcPolaPodGrafike.cbSize = sizeof(WNDCLASSEX);
	wndcPolaPodGrafike.hInstance = hThisInstance;
	wndcPolaPodGrafike.lpszClassName = GrafficWindowClassName.c_str();
	wndcPolaPodGrafike.lpfnWndProc = WindowProcedure;

	if (!RegisterClassEx(&wndcPolaPodGrafike)) {
		MessageBox(NULL, "rejestracja pol pod grafike nie powiodla sie!", "Wiadomoœæ", MB_ICONERROR | MB_OK);
		return 1;
	}

	//--------------------------------------------------------------------------

	WNDCLASSEX wndcPolaInformacyjne;

	ZeroMemory(&wndcPolaInformacyjne, sizeof(WNDCLASSEX));
	wndcPolaInformacyjne.cbSize = sizeof(WNDCLASSEX);
	wndcPolaInformacyjne.hInstance = hThisInstance;
	wndcPolaInformacyjne.lpszClassName = InformWindowClassName.c_str();
	wndcPolaInformacyjne.lpfnWndProc = WindowProcedure;
	wndcPolaInformacyjne.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	if (!RegisterClassEx(&wndcPolaInformacyjne)) {
		MessageBox(NULL, "rejestracja okna informacyjnego nie powiodla sie!", "Wiadomoœæ", MB_ICONERROR | MB_OK);
		return 1;
	}

	//--------------------------------------------------------------------------
	//----------------------------Creakcja okien--------------------------------    
	//--------------------------------------------------------------------------

	hwndGlowneOkno = CreateWindowEx(
		NULL,
		MainWindowClassName.c_str(),
		"SnakeWindow",
		WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
		50, 25, 14 * 50 + 205, 14 * 50 - 6,
		NULL,
		hMenu,
		hThisInstance,
		NULL
	);

	//--------------------------------------------------------------------------

	tablicaPoczatkowychOkien[0] = CreateWindowEx(
		0,
		"STATIC",
		"\n\tProsze wybrac stopien trudnosci:",
		WS_BORDER | WS_VISIBLE | WS_CHILD,
		150, 220, 600, 200,
		hwndGlowneOkno,
		NULL,
		hThisInstance,
		NULL
	);

	string ktoryPrzycisk;
	for (unsigned i = 1; i < 6; ++i) {
		switch (i) {
		case 1: ktoryPrzycisk = "LATWY";    break;
		case 2: ktoryPrzycisk = "NORMANY";  break;
		case 3: ktoryPrzycisk = "SREDNI";   break;
		case 4: ktoryPrzycisk = "TRUDNY";   break;
		case 5: ktoryPrzycisk = "OP";       break;
		};
		tablicaPoczatkowychOkien[i] = CreateWindowEx(
			0,
			"BUTTON",
			ktoryPrzycisk.c_str(),
			WS_BORDER | WS_VISIBLE | WS_CHILD,
			75 + 110 * i, 320, 90, 50,
			hwndGlowneOkno,
			(HMENU)i,
			hThisInstance,
			NULL
		);
	}
	tablicaPoczatkowychOkien[6] = CreateWindowEx(
		0,
		"BUTTON",
		"TO SAMO",
		WS_BORDER | WS_CHILD,
		75 + 110 * 4 - 55, 240, 90, 50,
		hwndGlowneOkno,
		(HMENU)6,
		hThisInstance,
		NULL
	);

	//------------------------------------------------------------------------------    

	srand(time(NULL));

	MSG msgKomunikat;
	msgKomunikat.message = WM_NULL;

	while (msgKomunikat.message != WM_QUIT) {
		if (PeekMessage(&msgKomunikat, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msgKomunikat);
			DispatchMessage(&msgKomunikat);
		}
		//else {       
		//} 
	}

	//--------------------------------------------------------------------------

	if (gra != nullptr) delete gra;

	DeleteObject(hbmpTrawa);
	DeleteObject(hbrPedzelTrawy);

	DeleteObject(hbmpScianaPoziomo);
	DeleteObject(hbmpScianaPionowo);
	DeleteObject(hbmpScianaGL);
	DeleteObject(hbmpScianaGP);
	DeleteObject(hbmpScianaDL);
	DeleteObject(hbmpScianaDP);

	DeleteObject(hbmpGlowaG);
	DeleteObject(hbmpGlowaD);
	DeleteObject(hbmpGlowaL);
	DeleteObject(hbmpGlowaP);

	DeleteObject(hbmpGlowaG_DEAD);
	DeleteObject(hbmpGlowaD_DEAD);
	DeleteObject(hbmpGlowaL_DEAD);
	DeleteObject(hbmpGlowaP_DEAD);

	DeleteObject(hbmpGlowaSkretGL_D_DEAD);
	DeleteObject(hbmpGlowaSkretGL_P_DEAD);
	DeleteObject(hbmpGlowaSkretGP_L_DEAD);
	DeleteObject(hbmpGlowaSkretGP_D_DEAD);
	DeleteObject(hbmpGlowaSkretDL_P_DEAD);
	DeleteObject(hbmpGlowaSkretDL_G_DEAD);
	DeleteObject(hbmpGlowaSkretDP_L_DEAD);
	DeleteObject(hbmpGlowaSkretDP_G_DEAD);

	DeleteObject(hbmpOgonG);
	DeleteObject(hbmpOgonD);
	DeleteObject(hbmpOgonL);
	DeleteObject(hbmpOgonP);

	DeleteObject(hbmpCialoPoziomo);
	DeleteObject(hbmpCialoPionowo);

	DeleteObject(hbmpSkretGL);
	DeleteObject(hbmpSkretGP);
	DeleteObject(hbmpSkretDL);
	DeleteObject(hbmpSkretDP);

	DeleteObject(hbmpOwoc);
	DeleteObject(hbmpEfekt);
	DeleteObject(hbmpBlad);

	DeleteObject(hbmpKlawiszW);
	DeleteObject(hbmpKlawiszS);
	DeleteObject(hbmpKlawiszA);
	DeleteObject(hbmpKlawiszD);
	DeleteObject(hbmpKlawiszSpacja);

	DeleteObject(hbmpKlawiszW_Zaznaczone);
	DeleteObject(hbmpKlawiszS_Zaznaczone);
	DeleteObject(hbmpKlawiszA_Zaznaczone);
	DeleteObject(hbmpKlawiszD_Zaznaczone);
	DeleteObject(hbmpKlawiszSpacja_Zaznaczone);

	//--------------------------------2 gracz-----------------------------------
	DeleteObject(hbmpKlawiszStrzalka_G);
	DeleteObject(hbmpKlawiszStrzalka_D);
	DeleteObject(hbmpKlawiszStrzalka_L);
	DeleteObject(hbmpKlawiszStrzalka_P);

	DeleteObject(hbmpKlawiszStrzalka_G_Zaznaczone);
	DeleteObject(hbmpKlawiszStrzalka_D_Zaznaczone);
	DeleteObject(hbmpKlawiszStrzalka_L_Zaznaczone);
	DeleteObject(hbmpKlawiszStrzalka_P_Zaznaczone);

	return static_cast<int>(msgKomunikat.wParam);
}

//------------------------------------------------------------------------------
void TworzenieOkien(short iluGraczy) {
	unsigned przesuniecie = (iluGraczy == 1) ? 0 : 250;

	for (unsigned i = 0; i < 13; ++i)
		for (unsigned j = 0; j < 13; ++j)
			tablicaPol[i][j] = CreateWindowEx(
				0,
				GrafficWindowClassName.c_str(),
				"oknoPola",
				WS_BORDER | WS_CHILD,
				i * 50 + przesuniecie, j * 50, 50, 50,
				hwndGlowneOkno,
				NULL,
				instancja,
				NULL
			);

	//----------------------------------------------------------------------

	tablicaKlawiszyMenu[0] = CreateWindowEx(
		0,
		GrafficWindowClassName.c_str(),
		"oknoMenu",
		WS_BORDER | WS_CHILD,
		13 * 50 + 25 + 70 + przesuniecie, 7 * 50, 60, 60,
		hwndGlowneOkno,
		NULL,
		instancja,
		NULL
	);


	for (unsigned i = 0; i < 3; ++i)
		tablicaKlawiszyMenu[i + 1] = CreateWindowEx(
			0,
			GrafficWindowClassName.c_str(),
			"oknoMenu",
			WS_BORDER | WS_CHILD,
			13 * 50 + 25 + 70 * i + przesuniecie, 8 * 50 + 20, 60, 60,
			hwndGlowneOkno,
			NULL,
			instancja,
			NULL
		);

	tablicaKlawiszyMenu[4] = CreateWindowEx(
		0,
		GrafficWindowClassName.c_str(),
		"spacja",
		WS_BORDER | WS_CHILD,
		13 * 50 + 25 + przesuniecie, 10 * 50 - 9, 200, 60,
		hwndGlowneOkno,
		NULL,
		instancja,
		NULL
	);


	//----------------------------------------------------------------------


	tablicaPolInformacyjnych[0] = CreateWindowEx(
		0,
		InformWindowClassName.c_str(),
		"oknoOwocow",
		WS_BORDER | WS_CHILD,
		13 * 50 + 25 + przesuniecie, 85, 200, 80,
		hwndGlowneOkno,
		NULL,
		instancja,
		NULL
	);

	tablicaPolInformacyjnych[1] = CreateWindowEx(
		0,
		InformWindowClassName.c_str(),
		"oknoEfektow",
		WS_BORDER | WS_CHILD,
		13 * 50 + 25 + przesuniecie, 205, 200, 80,
		hwndGlowneOkno,
		NULL,
		instancja,
		NULL
	);

	tablicaPolInformacyjnych[2] = CreateWindowEx(
		0,
		InformWindowClassName.c_str(),
		"oknoCzasuEfektow",
		WS_BORDER | WS_CHILD,
		13 * 50 + 25 + przesuniecie, 270, 200, 40,
		hwndGlowneOkno,
		NULL,
		instancja,
		NULL
	);

	//-------------------------------------------------------------------------

	if (iluGraczy == 1)
		MoveWindow(hwndGlowneOkno, 50, 25, 14 * 50 + 205, 14 * 50 - 6, TRUE);
	else {
		MoveWindow(tablicaPolInformacyjnych[1], 425, 650, 300, 60, FALSE);
		MoveWindow(tablicaPolInformacyjnych[2], 425, 680, 300, 35, FALSE);

		tablicaPolInformacyjnych_2 = CreateWindowEx(
			0,
			InformWindowClassName.c_str(),
			"oknoOwocow",
			WS_BORDER | WS_CHILD | WS_VISIBLE,
			25, 85, 200, 80,
			hwndGlowneOkno,
			NULL,
			instancja,
			NULL
		);

		tablicaKlawiszyMenu_2[0] = CreateWindowEx(
			0,
			GrafficWindowClassName.c_str(),
			"oknoMenu",
			WS_BORDER | WS_CHILD | WS_VISIBLE,
			25 + 70, 7 * 50, 60, 60,
			hwndGlowneOkno,
			NULL,
			instancja,
			NULL
		);


		for (unsigned i = 0; i < 3; ++i)
			tablicaKlawiszyMenu_2[i + 1] = CreateWindowEx(
				0,
				GrafficWindowClassName.c_str(),
				"oknoMenu",
				WS_BORDER | WS_CHILD | WS_VISIBLE,
				25 + 70 * i, 8 * 50 + 20, 60, 60,
				hwndGlowneOkno,
				NULL,
				instancja,
				NULL
			);

		tablicaKlawiszyMenu_2[4] = CreateWindowEx(
			0,
			GrafficWindowClassName.c_str(),
			"spacja",
			WS_BORDER | WS_CHILD | WS_VISIBLE,
			25, 10 * 50 - 9, 200, 60,
			hwndGlowneOkno,
			NULL,
			instancja,
			NULL
		);

		MoveWindow(hwndGlowneOkno, 0, 0, 14 * 50 + 455, 14 * 50 + 55, TRUE);
	}
}
