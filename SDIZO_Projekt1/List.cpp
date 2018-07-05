#include "stdafx.h"
#include "List.h"
#include "NumberGenerator.h"

List::List()
{
	size = 0;
	first = NULL;
	last = NULL;
}


List::~List()
{
	DeleteList();
}

int List::LoadFromFile(std::string filename) { //Wczytanie listy z pliku

	if (size > 0)
	{
		DeleteList();
		size = 0;
	}

	std::fstream numbersFile;
	numbersFile.open(filename, std::ios::in);
	if (!numbersFile.good()) //sprawdzenie czy dobrze wczytano plik z liczbami
	{
		std::cout << "Nie mozna wczytac pliku!\n";
		return 0;
	}

	int newSize = 0;
	numbersFile >> newSize;

	int index = 0;

	while (!numbersFile.eof()) //wczytywanie kolejnych liczb;
	{
		int pom;
		numbersFile >> pom;
		this->AddElementLast(pom);
		index++;
		if (index == newSize)
			break;
	}
	size = newSize;
	numbersFile.close();
	//std::cout << "Wczytano!\n";

	return 0;
}

int List::AddElementZero(int v) { //dodanie elementu do pustej listy

	if (size != 0)
		;
	else {
		ListElem *elem = new ListElem;
		first = elem;
		last = elem;
		elem->next = NULL;
		elem->prev = NULL;
		elem->var = v;
		size = 1;
	}
	return 0;
}

int List::AddElementFirst(int v) { //dodanie elementu na poczatek listy

	if (size == 0) {
		AddElementZero(v);
	}
	else {
		ListElem *elem = new ListElem;
		elem->next = first;
		elem->prev = NULL;
		elem->var = v;
		first = elem;
		size++;
	}

	return 0;
}

int List::AddElementLast(int v) { //dodanie elementu na koniec listy

	if (size == 0) {
		AddElementZero(v);
	}
	else {
		ListElem *elem = new ListElem;
		elem->next = NULL;
		elem->prev = last;
		elem->var = v;
		last->next = elem;
		last = elem;
		size++;
	}

	return 0;
}

int List::AddElement(int v, int position) { //dodanie elementu na wybrana pozycje listy

	if (size < 1)
		AddElementZero(v);
	else if (position == 0)
		AddElementFirst(v);
	else if (position == size)
		AddElementLast(v);
	else
	{
		if (position > size)
		{
			std::cout << "\nZa malo pozycji w tablicy!\n";
			return 0;
		}
		else
		{
			ListElem *elem = new ListElem;
			ListElem *pom = first;
			for (int i = 0; i < position-1; i++)
			{
				pom = pom->next;
			}
			elem->var = v;
			
			elem->prev = pom;
			elem->next = pom->next;

			pom->next->prev = elem;
			pom->next = elem;
			
			size++;
		}
	}
	//std::cout << "Dodano liczbe!\n\n";
	return 0;
}

int List::DeleteList() { //usuniecie listy

	first = NULL;
	last = NULL;
	size = 0;
	return 0;
}

int List::DeleteElementFirst() { //usuniecie pierwszego elementu listy

	if (size > 1)
	{
		first->next->prev = NULL;
		first = first->next;
		size--;
	}
	else 
		DeleteList();

	return 0;
}

int List::DeleteElementLast() { //usuniecie ostatniego elementu listy

	if (size > 1)
	{
		last->prev->next = NULL;
		last = last->prev;
		size--;
	}
	else
		DeleteList();

	return 0;
}

int List::DeleteElement(int position) { //usuniecie elementu na wybranej pozycji listy
	if (position >= size)
	{
		std::cout << "\nBrak takiej pozycji w liscie!\n";
		return 0;
	}
	else if (size < 2)
		DeleteList();
	else if (position == 0)
		DeleteElementFirst();
	else if (position == size - 1)
		DeleteElementLast();
	else
	{
		ListElem *pom = first;
		for (int i = 0; i < position - 1; i++)
		{
			pom = pom->next;
		}
		
		pom->next->next->prev = pom;
		pom->next = pom->next->next;

		size--;
	}
	//std::cout << "Usunieto liczbe!\n\n";
	return 0;
}

int List::FindElementFound(int v) {
	
	if (first == NULL) {
		return 0;
	}
	ListElem *pom;
	pom = this->first;
	for (int i = 0; i < size; i++)
	{
		if (pom->var == v) {
			DeleteElement(i);
			return 1;
		}
			
		if (pom->next != NULL)
			pom = pom->next;
		else return 0;
	}
	return 0;
}

int List::ShowList(int n) { //pokazanie listy

	if (first == NULL) {
		std::cout << "\nLista jest pusta";
		return 0;
	}

	ListElem *pom;
	pom = this->first;
	std::cout << "\nElementy listy:\n";
	for (int i = 0; i < n; i++)
	{
		std::cout << pom->var << std::endl;
		if (pom->next != NULL)
			pom = pom->next;
		else return 0;
	}

	return 0;
}

int List::FindElement(int v) {  //sprawdzenie czy jest element

	if (first == NULL) {
		std::cout << "\nLista jest pusta";
		return 0;
	}
	int was = 0;
	ListElem *pom;
	pom = this->first;
	for (int i = 0; i < size; i++)
	{
		if (pom->var == v)
			was = 1;
		if (pom->next != NULL)
			pom = pom->next;
		else return was;
	}
	return was;
}


int List::Menu() //Menu klasy Listy
{
	char select = 'y';

	while (select != '0')
	{
		if (size < 1)
		{
			std::cout << "\nLista nie zostala utworzona\n";
		}
		else
		{
			std::cout << "\nRozmiar listy: " << size << std::endl;
		}
		std::cout << "Wybierz nastepujace opcje:\n\n1. Wczytaj z pliku\n2. Dodaj element do listy\n3. Usun element z listy\n4. Szukaj liczby\n9. Wyswietl elementy listy\n0. Powrot do menu glownego (Wyjscie kasuje liste)" << std::endl;

		select = _getch();
		switch (select)
		{
		case '1': {
			std::string filename;
			std::cout << "\nPodaj nazwe wczytywanego pliku:";
			std::cin >> filename;
			if (filename.substr(filename.find_last_of(".") + 1) != "txt") //dodanie do nazwy pliku rozszerzenia .txt gdy go nie ma
			{
				filename += ".txt";
			}

			std::chrono::time_point<std::chrono::system_clock> start, end; //pomiar czasu
			start = std::chrono::system_clock::now();

			LoadFromFile(filename);

			end = std::chrono::system_clock::now(); //zakoñczenie liczenia czasu
			std::chrono::duration<double> elapsed_seconds = end - start;

			if (size != 0)
				std::cout << "\nWczytano plik!\n\n";
			std::cout << "\nCzas wykonywania: " << elapsed_seconds.count() << " [s]\n";

		} break;

		case '2': {

			int var, position;
			std::cout << "\nPodaj indeks pozycji (od 0 do " << size << "): ";
			std::cin >> position;
			std::cout << "\nPodaj liczbe: ";
			std::cin >> var;

			std::chrono::time_point<std::chrono::system_clock> start, end; //pomiar czasu
			start = std::chrono::system_clock::now();


			AddElement(var, position);

			end = std::chrono::system_clock::now(); //koniec pomiaru
			std::chrono::duration<double> elapsed_seconds = end - start;
			std::cout << "\nCzas wykonywania: " << elapsed_seconds.count() << " [s]\n";
			/*
			------------------ Testowe menu sprawdzaj¹ce ka¿dy typ dodawania osobno ------------------

			char select2 = 'x';
			while (select2 != '0')
			{
			std::cout << "\nDodawanie elemntu:\n1. Na poczatku listy\n2. Na koncu listy\n3. W wybranym miejscu listy\n9. Wyswietl tablice\n0. Powrot";
			select2 = _getch();

			switch (select2)
			{
			case '1': {
			int var;
			std::cout << "\nPodaj liczbe: ";
			std::cin >> var;
			AddElementFirst(var);
			std::cout << "Dodano liczbe!\n\n";

			} break;

			case '2': {
			int var;
			std::cout << "\nPodaj liczbe: ";
			std::cin >> var;
			AddElementLast(var);
			std::cout << "Dodano liczbe!\n\n";
			} break;

			case '3': {
			int var, position;
			std::cout << "\nPodaj indeks pozycji (od 0 do " << size << "): ";
			std::cin >> position;
			std::cout << "\nPodaj liczbe: ";
			std::cin >> var;
			AddElement(var, position);
			std::cout << "Dodano liczbe!\n\n";
			} break;

			case ('9') :
			{
			int n;
			if (size >= 0 && size < 15)
			n = size;
			else
			{
			std::cout << "\nPodaj ile liczb wyswietlic:";
			do
			{
			std::cin >> n;
			if (n > size || n <= 0)
			{
			std::cout << "Nie ma tylu liczb w tablicy, wprowadz jeszcze raz ilosc.\n";
			n = 0;
			}
			} while (n > size || n <= 0);
			}
			std::cout << std::endl;
			ShowList(n);
			std::cout << std::endl;

			} break;
			}

			};
			select2 = 'x';
			*/
		} break;

		case '3': {

			int var = 0;
			std::cout << "\nPodaj wartosc liczby ktora chcesz usunac:\n";
			std::cin >> var;

			std::chrono::time_point<std::chrono::system_clock> start, end; //pomiar czasu
			start = std::chrono::system_clock::now();

			int pom = FindElementFound(var);

			end = std::chrono::system_clock::now(); //koniec pomiaru
			std::chrono::duration<double> elapsed_seconds = end - start;

			if (pom == 1)
				std::cout << "Usunieto!\n";
			else std::cout << "Liczby tej nie ma w liscie\n";
			std::cout << "\nCzas wykonywania: " << elapsed_seconds.count() << " [s]\n";
			/*
			----- Usiniecie liczbby  z danej pozycji

			int position;
			std::cout << "\nPodaj indeks pozycji (od 0 do " << size - 1 << "): ";
			std::cin >> position;
			DeleteElement(position);
			*/
			/*

			------------------ Testowe menu sprawdzaj¹ce ka¿dy typ usuwania osobno ------------------

			char select2 = 'x';
			while (select2 != '0')
			{
			std::cout << "\nUsuwanie elemntu:\n1. Na poczatku listy\n2. Na koncu listy\n3. W wybranym miejscu listy\n9. Wyswietl tablice\n0. Powrot";
			select2 = _getch();

			switch (select2)
			{
			case '1': {
			DeleteElementFirst();
			std::cout << "Usunieto liczbe!\n\n";

			} break;

			case '2': {
			DeleteElementLast();
			std::cout << "Usunieto liczbe!\n\n";
			} break;

			case '3': {
			int position;
			std::cout << "\nPodaj indeks pozycji (od 0 do " << size - 1 << "): ";
			std::cin >> position;
			DeleteElement(position);
			std::cout << "Usunieto liczbe!\n\n";
			} break;

			case ('9') :
			{
			int n;
			if (size >= 0 && size < 15)
			n = size;
			else
			{
			std::cout << "\nPodaj ile liczb wyswietlic:";
			do
			{
			std::cin >> n;
			if (n > size || n <= 0)
			{
			std::cout << "Nie ma tylu liczb w tablicy, wprowadz jeszcze raz ilosc.\n";
			n = 0;
			}
			} while (n > size || n <= 0);
			}
			std::cout << std::endl;
			ShowList(n);
			std::cout << std::endl;

			} break;
			}

			};
			select2 = 'x';
			*/
		} break;

		case '4': {
			int var = 0;
			std::cout << "\nPodaj szukana liczbe:\n";
			std::cin >> var;

			std::chrono::time_point<std::chrono::system_clock> start, end; //pomiar czasu
			start = std::chrono::system_clock::now();

			int pom = FindElement(var);

			end = std::chrono::system_clock::now(); //koniec pomiaru
			std::chrono::duration<double> elapsed_seconds = end - start;

			if (pom == 1)
				std::cout << "Liczba ta znajduje sie w liscie\n";
			else std::cout << "Liczby tej nie ma w liscie\n";

			std::cout << "\nCzas wykonywania: " << elapsed_seconds.count() << " [s]\n";

		} break;

		case '9': {
			int n;
			if (size >= 0 && size < 15)
				n = size;
			else
			{
				std::cout << "\nPodaj ile liczb wyswietlic:";
				do
				{
					std::cin >> n;
					if (n > size || n <= 0)
					{
						std::cout << "Nie ma tylu liczb w tablicy, wprowadz jeszcze raz ilosc.\n";
						n = 0;
					}
				} while (n > size || n <= 0);
			}
			std::cout << std::endl;
			ShowList(n);
			std::cout << std::endl;

		} break;


		case 'T': {

			char select2 = 'x';
			srand(time(NULL));
			while (select2 != '0')
			{
				std::cout << "\n-----------------------------\n---- Menu testow listy ----\n-----------------------------\n\n";
				std::cout << "1. Dodawanie na poczatku\n2. Dodawanie na koncu\n3. Dodawanie losowo\n4. Usuwanie na poczatku\n5. Usuwanie na koncu\n6. Usuwanie losowo\n7. Wyszukiwanie losowo\n0. Powrot\n\n";
				select2 = _getch();
				switch (select2) {

				case '1': {

					int powtorzenia, wielkosc;
					std::cout << "1. Podal liczbe powtowrzen: \n";
					std::cin >> powtorzenia;
					std::cout << "Podal wielkosc testowanej struktury: \n";
					std::cin >> wielkosc;
					NumberGenerator num;
					std::chrono::duration<double> time_total;
					for (int i = 0; i < powtorzenia; i++) {
						num.GenerateNumbersAuto(wielkosc);
						LoadFromFile("testnumbers.txt");

						int nrRandom = rand();

						std::chrono::time_point<std::chrono::system_clock> start, end; //pomiar czasu
						start = std::chrono::system_clock::now();

						AddElementFirst(nrRandom); // funkcja testowana <--------

						end = std::chrono::system_clock::now(); //koniec pomiaru
						std::chrono::duration<double> elapsed_seconds = end - start;

						elapsed_seconds /= powtorzenia;
						time_total += elapsed_seconds;
						if (i % 10 == 0)
							std::cout << i << " powtorzen\n";
					}
					std::fstream wynik;
					wynik.open("wynik.txt", std::ios::out);
					wynik << time_total.count() << std::endl;
					wynik.close();
					std::cout << "\nSredni czas wykonywania: " << time_total.count() << " [s]\n";


				} break;

				case '2': {

					int powtorzenia, wielkosc;
					std::cout << "2. Podal liczbe powtowrzen: \n";
					std::cin >> powtorzenia;
					std::cout << "Podal wielkosc testowanej struktury: \n";
					std::cin >> wielkosc;
					NumberGenerator num;
					std::chrono::duration<double> time_total;
					for (int i = 0; i < powtorzenia; i++) {
						num.GenerateNumbersAuto(wielkosc);
						LoadFromFile("testnumbers.txt");

						int nrRandom = rand();

						std::chrono::time_point<std::chrono::system_clock> start, end; //pomiar czasu
						start = std::chrono::system_clock::now();

						AddElementLast(nrRandom); // funkcja testowana <--------

						end = std::chrono::system_clock::now(); //koniec pomiaru
						std::chrono::duration<double> elapsed_seconds = end - start;

						elapsed_seconds /= powtorzenia;
						time_total += elapsed_seconds;
						if (i % 10 == 0)
							std::cout << i << " powtorzen\n";
					}
					std::fstream wynik;
					wynik.open("wynik.txt", std::ios::out);
					wynik << time_total.count() << std::endl;
					wynik.close();
					std::cout << "\nSredni czas wykonywania: " << time_total.count() << " [s]\n";

				} break;

				case '3': {

					int powtorzenia, wielkosc;
					std::cout << "3. Podal liczbe powtowrzen: \n";
					std::cin >> powtorzenia;
					std::cout << "Podal wielkosc testowanej struktury: \n";
					std::cin >> wielkosc;
					NumberGenerator num;
					std::chrono::duration<double> time_total;
					for (int i = 0; i < powtorzenia; i++) {
						num.GenerateNumbersAuto(wielkosc);
						LoadFromFile("testnumbers.txt");

						int nrRandom = rand();
						int possition = (rand() % wielkosc - 2) + 1;

						std::chrono::time_point<std::chrono::system_clock> start, end; //pomiar czasu
						start = std::chrono::system_clock::now();

						AddElement(nrRandom, possition); // funkcja testowana <--------

						end = std::chrono::system_clock::now(); //koniec pomiaru
						std::chrono::duration<double> elapsed_seconds = end - start;

						elapsed_seconds /= powtorzenia;
						time_total += elapsed_seconds;
						if (i % 10 == 0)
							std::cout << i << " powtorzen\n";
					}
					std::fstream wynik;
					wynik.open("wynik.txt", std::ios::out);
					wynik << time_total.count() << std::endl;
					wynik.close();
					std::cout << "\nSredni czas wykonywania: " << time_total.count() << " [s]\n";

				} break;

				case '4': {

					int powtorzenia, wielkosc;
					std::cout << "4. Podal liczbe powtowrzen: \n";
					std::cin >> powtorzenia;
					std::cout << "Podal wielkosc testowanej struktury: \n";
					std::cin >> wielkosc;
					NumberGenerator num;
					std::chrono::duration<double> time_total;
					for (int i = 0; i < powtorzenia; i++) {
						num.GenerateNumbersAuto(wielkosc);
						LoadFromFile("testnumbers.txt");

						std::chrono::time_point<std::chrono::system_clock> start, end; //pomiar czasu
						start = std::chrono::system_clock::now();

						DeleteElementFirst(); // funkcja testowana <--------

						end = std::chrono::system_clock::now(); //koniec pomiaru
						std::chrono::duration<double> elapsed_seconds = end - start;

						elapsed_seconds /= powtorzenia;
						time_total += elapsed_seconds;
						if (i % 10 == 0)
							std::cout << i << " powtorzen\n";
					}
					std::fstream wynik;
					wynik.open("wynik.txt", std::ios::out);
					wynik << time_total.count() << std::endl;
					wynik.close();
					std::cout << "\nSredni czas wykonywania: " << time_total.count() << " [s]\n";

				} break;

				case '5': {

					int powtorzenia, wielkosc;
					std::cout << "5. Podal liczbe powtowrzen: \n";
					std::cin >> powtorzenia;
					std::cout << "Podal wielkosc testowanej struktury: \n";
					std::cin >> wielkosc;
					NumberGenerator num;
					std::chrono::duration<double> time_total;
					for (int i = 0; i < powtorzenia; i++) {
						num.GenerateNumbersAuto(wielkosc);
						LoadFromFile("testnumbers.txt");

						std::chrono::time_point<std::chrono::system_clock> start, end; //pomiar czasu
						start = std::chrono::system_clock::now();

						DeleteElementLast(); // funkcja testowana <--------

						end = std::chrono::system_clock::now(); //koniec pomiaru
						std::chrono::duration<double> elapsed_seconds = end - start;

						elapsed_seconds /= powtorzenia;
						time_total += elapsed_seconds;
						if (i % 10 == 0)
							std::cout << i << " powtorzen\n";
					}
					std::fstream wynik;
					wynik.open("wynik.txt", std::ios::out);
					wynik << time_total.count() << std::endl;
					wynik.close();
					std::cout << "\nSredni czas wykonywania: " << time_total.count() << " [s]\n";

				} break;

				case '6': {

					int powtorzenia, wielkosc;
					std::cout << "6. Podal liczbe powtowrzen: \n";
					std::cin >> powtorzenia;
					std::cout << "Podal wielkosc testowanej struktury: \n";
					std::cin >> wielkosc;
					NumberGenerator num;
					std::chrono::duration<double> time_total;
					for (int i = 0; i < powtorzenia; i++) {
						num.GenerateNumbersAuto(wielkosc);
						LoadFromFile("testnumbers.txt");

						int possition = (rand() % wielkosc - 2) + 1;

						std::chrono::time_point<std::chrono::system_clock> start, end; //pomiar czasu
						start = std::chrono::system_clock::now();

						DeleteElement(possition); // funkcja testowana <--------

						end = std::chrono::system_clock::now(); //koniec pomiaru
						std::chrono::duration<double> elapsed_seconds = end - start;

						elapsed_seconds /= powtorzenia;
						time_total += elapsed_seconds;
						if (i % 10 == 0)
							std::cout << i << " powtorzen\n";
					}
					std::fstream wynik;
					wynik.open("wynik.txt", std::ios::out);
					wynik << time_total.count() << std::endl;
					wynik.close();
					std::cout << "\nSredni czas wykonywania: " << time_total.count() << " [s]\n";

				} break;

				case '7': {

					int powtorzenia, wielkosc;
					std::cout << "7. Podal liczbe powtowrzen: \n";
					std::cin >> powtorzenia;
					std::cout << "Podal wielkosc testowanej struktury: \n";
					std::cin >> wielkosc;
					NumberGenerator num;
					std::chrono::duration<double> time_total;
					for (int i = 0; i < powtorzenia; i++) {
						num.GenerateNumbersAuto(wielkosc);
						LoadFromFile("testnumbers.txt");

						int randomNumber = rand();

						std::chrono::time_point<std::chrono::system_clock> start, end; //pomiar czasu
						start = std::chrono::system_clock::now();

						FindElement(randomNumber); // funkcja testowana <--------

						end = std::chrono::system_clock::now(); //koniec pomiaru
						std::chrono::duration<double> elapsed_seconds = end - start;

						elapsed_seconds /= powtorzenia;
						time_total += elapsed_seconds;
						if (i % 10 == 0)
							std::cout << i << " powtorzen\n";
					}
					std::fstream wynik;
					wynik.open("wynik.txt", std::ios::out);
					wynik << time_total.count() << std::endl;
					wynik.close();
					std::cout << "\nSredni czas wykonywania: " << time_total.count() << " [s]\n";

				} break;

				}
			}
		}break;

		}
	}

	return 0;
}