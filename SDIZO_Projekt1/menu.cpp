#include "stdafx.h"
#include "menu.h"
#include "NumberGenerator.h"
#include "List.h"
#include "Board.h"
#include "BinaryHeap.h"


menu::menu()
{
}

menu::~menu()
{
}


int menu::ShowMenu() //Menu g³ówne programu
{
	char select = 'x';
	while (select != '0')
	{
		std::cout << "SDIZO Projek 1 - Marcin Calkowski nr. 218191\nWybierz opcje:\n\n1. Tablica\n2. Lista\n3. Kopiec binarny\n4. Losuj plik testowy\n0. Wyjscie\n";
		select = _getch();

		switch (select)
		{
			case '1':
			{
				std::cout << "\n-----------------------------\n---------  Tablica  ---------\n-----------------------------\n\n";
				Board tablica;	//stworzenie klasy testwoania tablicy
				tablica.Menu();
			} break;

			case '2':
			{
				std::cout << "\n-----------------------------\n---------   Lista   ---------\n-----------------------------\n\n";
				List lista;		//stworzenie klasy testwoania listy
				lista.Menu();
			} break;


			case '3':
			{
				std::cout << "\n-----------------------------\n------ Kopiec  binarny ------\n-----------------------------\n\n";
				BinaryHeap kopiec;	//stworzenie klasy testwoania kopca binarnego
				kopiec.Menu();
			} break;

			case '4':
			{
				std::cout << "Losowanie pliku\n";
				NumberGenerator gen;	//generowanie losowej puli liczb
				gen.GenerateNumbers();
			} break;

		}
		std::cout << std::endl;
	}
	
	return 0;
}
