#include "stdafx.h"
#include "Board.h"
#include "NumberGenerator.h"

Board::Board()
{
	size = 0;
}


Board::~Board()
{
	if (size != 0)
	{
		delete this->board;
		size = 0;
	}
}

int Board::LoadFromFile(std::string filename) //wczytanie tablicy z pliku
{
	if (size > 0)
	{
		delete[] this->board;
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
	this->board = new int[newSize]; //stworzenie nowej tablicy dynamicznej

	int index = 0;

	while (!numbersFile.eof()) //wczytywanie kolejnych liczb;
	{
		numbersFile >> this->board[index];
		index++;
		if (index == newSize)
			break;
	}
	numbersFile.close();

	return newSize;
}

int Board::AddElementZero(int var)
{
	if (size != 0)
	{
		size = 0;
		delete[] this->board;
	}
	this->board = new int[1];
	board[0] = var;
	size = 1;
	return 0;
}

int Board::AddElementFirst(int var) //dodanie elementu na poczatek tablicy
{
	if (size < 1)
		AddElementZero(var);
	else
	{
		size++;
		int *help;
		help = new int[size];
		help[0] = var;
		for (int i = 1; i < size; i++)
		{
			help[i] = this->board[i - 1];
		}

		delete[] this->board;
		this->board = new int[size];

		this->board = help;
	}

	return 0;
}

int Board::AddElementLast(int var) //dodanie elementu na koniec tablicy
{
	if (size < 1)
		AddElementZero(var);
	else
	{
		size++;
		int *help;
		help = new int[size];
		for (int i = 0; i < size - 1; i++)
		{
			help[i] = this->board[i];
		}
		help[size - 1] = var;
		delete this->board;
		this->board = new int[size];

		this->board = help;

	}

	return 0;
}


int Board::AddElement(int var, int position) //dodanie elementu o danej wartosci na danej pozycji
{
	if (size < 1)
		AddElementZero(var);
	else if (position == 0)
		AddElementFirst(var);
	else if (position == size)
		AddElementLast(var);
	else
	{
		if (position > size)
		{
			std::cout << "\nZa malo pozycji w tablicy!\n";
			return 0;
		}
		else
		{
			size++;
			int *help;
			help = new int[size];

			for (int i = 0; i < position; i++)
				help[i] = this->board[i];

			help[position] = var;

			for (int i = position + 1; i < size; i++)
				help[i] = this->board[i - 1];

			delete this->board;
			this->board = new int[size];
			this->board = help;
		}
	}
	return 0;
}

int Board::DeleteBoard() //usuniêcie tablicy (stosowane zawsze przy usuwaniu ostatniego elementu)
{
	if (size != 0)
	{
		delete[] this->board;
		size = 0;
		return 1;
	}

	return 0;
}

int Board::DeleteElementFirst() //usuniecie elementu na poczatku tablicy
{
	if (size < 2)
		DeleteBoard();
	else
	{
		int *help;
		help = new int[size - 1];
		for (int i = 0; i < size - 1; i++)
		{
			help[i] = this->board[i + 1];
		}
		delete this->board;
		this->board = new int[size - 1];
		this->board = help;
		size--;
	}
	return 0;
}

int Board::DeleteElementLast() //usuniecie elementu na koncu tablicy
{
	if (size < 2)
		DeleteBoard();
	else
	{
		int *help;
		help = new int[size - 1];
		for (int i = 0; i < size - 1; i++)
		{
			help[i] = this->board[i];
		}
		delete this->board;
		this->board = new int[size - 1];
		this->board = help;
		size--;
	}
	return 0;
}

int Board::DeleteElement(int position) //usuwanie elementu z danej pozycji
{
	if (position > size)
	{
		std::cout << "\nBrak takiej pozycji w tablicy!\n";
		return 0;
	}
	else if (size < 2)
		DeleteBoard();
	else if (position == 0)
		DeleteElementFirst();
	else if (position == size - 1)
		DeleteElementLast();
	else
	{
		int *help;
		help = new int[size - 1];

		for (int i = 0; i < position; i++)
			help[i] = this->board[i];

		for (int i = position; i < size - 1; i++)
			help[i] = this->board[i + 1];

		delete this->board;
		this->board = new int[size - 1];
		this->board = help;
		size--;
	}
	return 0;
}

int Board::DeleteElementFound(int var) {

	for (int i = 0; i < size; i++)
	{
		if (board[i] == var) {
			DeleteElement(i);
			return 1;
		}
		
	}
	return 0;

}

int Board::FindElement(int var) {

	for (int i = 0; i < size; i++)
	{
		if (board[i] == var)
			return 1;
	}
	return 0;
}

int Board::ShowBoard(int n) //wyswietlenie aktualnej zawartosci tablicy
{
	std::cout << "\nElementy tablicy:\n";
	for (int i = 0; i < n; i++)
	{
		std::cout << *this->board << std::endl;
		this->board++;
	}
	this->board -= n;

	return 0;
}

int Board::Menu() //Menu odpowiedzialne za wybranie opcji zwiazanych z tablica
{
	char select = 'y';
	while (select != '0')
	{
		if (size < 1)
		{
			std::cout << "\nTablica nie zostala utworzona\n";
		}
		else
		{
			std::cout << "\nRozmiar tablicy: " << size << std::endl;
		}

		std::cout << "Wybierz opcje:\n\n1. Wczytaj plik\n2. Dodaj element do tablicy\n3. Usun element z tablicy\n4. Sprawdz czy element jest w tablicy\n9. Wyswietl elementy tablicy\n0. Powrot do menu glownego (Wyjscie kasuje tablice)\n";

		select = _getch();
		switch (select)
		{
		case '1':
		{
			std::string filename;
			std::cout << "\nPodaj nazwe wczytywanego pliku:";
			std::cin >> filename;
			if (filename.substr(filename.find_last_of(".") + 1) != "txt") //dodanie do nazwy pliku rozszerzenia .txt gdy go nie ma
			{
				filename += ".txt";
			}

			std::chrono::time_point<std::chrono::system_clock> start, end; //u¿ycie funkcji z biblioteki chrono do pomiaru czasu
			start = std::chrono::system_clock::now();

			size = LoadFromFile(filename); //wywolanie funkcji wczytuj¹cej dane z pliku

			end = std::chrono::system_clock::now(); //zakoñczenie liczenia czasu
			std::chrono::duration<double> elapsed_seconds = end - start; //wynik czasu w double

			if (size != 0)
				std::cout << "\nWczytano plik!\n\n";

			std::cout << "\nCzas wykonywania: " << elapsed_seconds.count() << " [s]\n";
		} break;

		case '2':
		{
			int var, position;
			std::cout << "\nPodaj indeks pozycji (od 0 do " << size << "): ";
			std::cin >> position;
			std::cout << "\nPodaj liczbe: ";
			std::cin >> var;

			std::chrono::time_point<std::chrono::system_clock> start, end; //u¿ycie funkcji z biblioteki chrono do pomiaru czasu
			start = std::chrono::system_clock::now();

			AddElement(var, position);

			end = std::chrono::system_clock::now(); //zakoñczenie liczenia czasu
			std::chrono::duration<double> elapsed_seconds = end - start; //wynik czasu w double

			std::cout << "Dodano liczbe!\n\n";
			std::cout << "\nCzas wykonywania: " << elapsed_seconds.count() << " [s]\n";
			/*

			------------------ Testowe menu sprawdzaj¹ce ka¿dy typ dodawania osobno ------------------

			char select2 = 'x';
			while (select2 != '0')
			{
			std::cout << "\nDodawanie elemntu:\n1. Na poczatku tablicy\n2. Na koncu tablicy\n3. W wybranym miejscu tablicy\n9. Wyswietl tablice\n0. Powrot";
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
			std::cout << "\nPodaj indeks pozycji (od 0 do "<<size<<"): ";
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
			} while (n>size || n <= 0);
			}
			std::cout << std::endl;
			ShowBoard(n);
			std::cout << std::endl;

			} break;
			}

			};
			select2 = 'x';
			*/
		} break;


		case '3':
		{
			int value;
			std::cout << "\nPodaj wartosc ktora chcesz usunac:\n";
			std::cin >> value;

			std::chrono::time_point<std::chrono::system_clock> start, end; //u¿ycie funkcji z biblioteki chrono do pomiaru czasu
			start = std::chrono::system_clock::now();

			int pom = DeleteElementFound(value);

			end = std::chrono::system_clock::now(); //zakoñczenie liczenia czasu
			std::chrono::duration<double> elapsed_seconds = end - start; //wynik czasu w double

			if (pom == 1)
				std::cout << "Usunieto!\n";
			else std::cout << "Liczby tej nie ma w liscie\n";
			std::cout << "\nCzas wykonywania: " << elapsed_seconds.count() << " [s]\n";
			/* -- Usuwanie liczby o danym indeksie --

			int position, pomsize;
			if (size == 0)
			pomsize = 0;
			else
			pomsize = size - 1;
			std::cout << "\nPodaj indeks pozycji (od 0 do " << pomsize << "): ";
			std::cin >> position;
			DeleteElement(position);
			std::cout << "Usunieto liczbe!\n\n";
			*/
			/*
			------------------ Testowe menu sprawdzaj¹ce ka¿dy typ usuwania osobno ------------------

			char select2 = 'x';
			while (select2 != '0')
			{
			std::cout << "\nUsuwanie elemntu:\n1. Na poczatku tablicy\n2. Na koncu tablicy\n3. W wybranym miejscu tablicy\n9. Wyswietl tablice\n0. Powrot";
			select2 = _getch();

			switch (select2)
			{
			case '1': {
			int var;
			DeleteElementFirst();
			std::cout << "Usunieto liczbe!\n\n";

			} break;

			case '2': {
			int var;
			DeleteElementLast();
			std::cout << "Usunieto liczbe!\n\n";
			} break;

			case '3': {

			int position, pomsize;
			if (size == 0)
			pomsize = 0;
			else
			pomsize = size - 1;
			std::cout << "\nPodaj indeks pozycji (od 0 do " << pomsize << "): ";
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
			} while (n>size || n <= 0);
			}
			std::cout << std::endl;
			ShowBoard(n);
			std::cout << std::endl;

			} break;
			}

			};
			select2 = 'x';
			*/
		} break;

		case ('4') :
		{
			int var = 0;
			std::cout << "\nPodaj szukana liczbe:\n";
			std::cin >> var;

			std::chrono::time_point<std::chrono::system_clock> start, end; //u¿ycie funkcji z biblioteki chrono do pomiaru czasu
			start = std::chrono::system_clock::now();

			int pom = FindElement(var);

			end = std::chrono::system_clock::now(); //zakoñczenie liczenia czasu
			std::chrono::duration<double> elapsed_seconds = end - start; //wynik czasu w double

			if (pom == 1)
				std::cout << "Liczba ta znajduje sie w liscie\n";
			else std::cout << "Liczby tej nie ma w liscie\n";
			std::cout << "\nCzas wykonywania: " << elapsed_seconds.count() << " [s]\n";

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
			ShowBoard(n);
			std::cout << std::endl;

		} break;

		case 'T': {

			char select2 = 'x';
			srand(time(NULL));
			while (select2 != '0')
			{
				std::cout << "\n-----------------------------\n---- Menu testow tablicy ----\n-----------------------------\n\n";
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
						size = LoadFromFile("testnumbers.txt");
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
						size = LoadFromFile("testnumbers.txt");

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
						size = LoadFromFile("testnumbers.txt");

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
						size = LoadFromFile("testnumbers.txt");

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
						size = LoadFromFile("testnumbers.txt");

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
						size = LoadFromFile("testnumbers.txt");

						int possition = (rand() % (this->size - 2)) + 1;
						//std::cout << "poz: " << possition << "\n";

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
						size = LoadFromFile("testnumbers.txt");

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