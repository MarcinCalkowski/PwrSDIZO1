// SDIZO_Projekt 1
// Marcin Ca�kowski nr 2181901
// Ka�dy typ struktury osadzony jest w osobnej klasie
// Ka�da klasa ma w�asne menu pozwalaj�ce na testowanie funkcji w danej strukturze
// Pomiar czasu rozpoczynany jest przed startem funkcji, i zatrzymywany jest zaraz po jej zwr�ceniu (w celu unikni�cia problemu z funkcjami rekurencyjnymi)

#include "stdafx.h"
#include "menu.h"


int main()
{
	menu menu;
	menu.ShowMenu(); //Wywo�anie menu g��wnego
	return 0;
	
}

