// SDIZO_Projekt 1
// Marcin Ca³kowski nr 2181901
// Ka¿dy typ struktury osadzony jest w osobnej klasie
// Ka¿da klasa ma w³asne menu pozwalaj¹ce na testowanie funkcji w danej strukturze
// Pomiar czasu rozpoczynany jest przed startem funkcji, i zatrzymywany jest zaraz po jej zwróceniu (w celu unikniêcia problemu z funkcjami rekurencyjnymi)

#include "stdafx.h"
#include "menu.h"


int main()
{
	menu menu;
	menu.ShowMenu(); //Wywo³anie menu g³ównego
	return 0;
	
}

