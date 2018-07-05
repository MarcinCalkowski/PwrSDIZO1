#include "stdafx.h"
#include "BinaryHeap.h"
#include "NumberGenerator.h"


BinaryHeap::BinaryHeap()
{
	size = 0;
}


BinaryHeap::~BinaryHeap()
{
	if (size != 0)
	{
		delete[] heap;
		size = 0;
		//DeleteHeap();
	}
}


int BinaryHeap::SortUp(int index) { //sortowanie kopca w gore - wykorzystany indeks (parametr) i tablica (z klasy)

	if (index != 0)
	{
		int parent = ((index - 1) / 2);  //ustawienie rodzica jako polowe aktualnego indeksu
		if (heap[parent] < heap[index])  //porownanie rodzica i jego dziecka indeks
		{
			Swap(heap[parent], heap[index]);   //zamiana liczb miejsc gdy warunek jest spelniony
			SortUp(parent);  //ponowne wywolanie sortowania dla innego rodzica (wyliczonego wyzej)
		}
	}
	return 0;
}

int BinaryHeap::SortDown(int index) { //sortowanie kopca w dol - wykorzystany indeks (parametr), tablica i jej rozmiar (z klasy)

	if (index < size && index >= 0) //sprawdzanie czy indeks miesci sie w rozmiaze
	{
		int child1, child2;
		child1 = (2 * index) + 1;
		child2 = child1 + 1; //przywolane zmiennych pomocniczych oznaczajacych potomkow
		if ((child1 < size) && (heap[index] < heap[child1])) //warunek dla pierwszego potomka
		{
			Swap(heap[index], heap[child1]); //gdy warunek spelniony zamiana miejscami i przejscie nizej
			SortDown(child1);
		}
		if ((child2 < size) && (heap[index] < heap[child2])) //analogicznie jak wyzej, tylko dla drugiego potomka
		{
			Swap(heap[index], heap[child2]);
			SortDown(child2);
		}
	}
	return 0;
}

int BinaryHeap::AddElement(int element) { //dodawanie elementu

	if (size == 0) //dodanie jesli nic w kopcu nie ma
	{
		size++;
		heap = new int[size]; //utworzenie tablicy kopca
		*heap = element;
	}
	else if (size > 0) //dodanie gdy tablica ma co najmniej 1 element
	{
		//int sizeTemp = size + 1;
		int *heapTemp;
		heapTemp = new int[size + 1];
		for (int i = 0; i < size; i++) //kopiowanie poprzednich czesci tablicy do nowej tablicy pomocniczej
		{
			heapTemp[i] = heap[i];
		}
		//heap -= size;
		//heapTemp -= size;
		delete[] heap;
		heap = new int[size + 1];
		this->heap = heapTemp; //ustawienie wskaznika kopca na kopiec pomocniczy
		heap[size] = element; //dodanie elementu nowego

		SortUp(size); //uruchomienie sortowania w celu przywrucenia strukturze wlasciwosci kopca
		size++;
	}

	return 0;
}

int BinaryHeap::DeleteHeap() { //usuniece calego kopca

	delete[] heap;
	size = 0;
	return 0;
}

int BinaryHeap::DeleteElementMax() { // usuniecie elementu max z kopca

	if (size>0)
	{
		size--;
		Swap(heap[0], heap[size]); //zamiana pierwszego i ostatniego elementu
		int *heapTemp;
		heapTemp = new int[size];
		for (int i = 0; i<size; i++) //kopiowanie poprzednich czesci tablicy do nowej tablicy pomocniczej z pominieciem usunietego elementu
		{
			heapTemp[i] = heap[i];
		}
		delete[] heap;
		heap = new int[size];
		this->heap = heapTemp;

		SortDown(0); //przywrocenie wlasnosci kopca poprzez sortowanie od gory
	}
	else std::cout << "Kopiec jeset pusty\n";

	return 0;
}

int BinaryHeap::DeleteElementMin() { // usuniecie elementu MIN
	if (size>0)
	{
		size--; //zmniejszenie tablicy o 1
		int *heapTemp;
		heapTemp = new int[size]; // i stworzenie nowej tablicy z pominieciem ostatniego elementu (min)
		for (int i = 0; i<size; i++) //kopiowanie poprzednich czesci tablicy do nowej tablicy pomocniczej z pominieciem usunietego elementu
		{
			heapTemp[i] = heap[i];
		}
		delete[] heap;
		heap = new int[size];
		this->heap = heapTemp;
	}
	else std::cout << "Kopiec jeset pusty\n";

	return 0;
}

int BinaryHeap::DeleteElement(int element) { // usuniecie wybranego elementu

	int index = FindElement(element); //znalezienie indeksu szukanego elementu

	if (index < 0 || index >= size) {
		//std::cout << "nie ma takiej liczby w kopcu!";
		return -1;
	}
	else if (index == size - 1) {
		DeleteElementMin();
		return 0;
	}
	else if (index == 0) {
		DeleteElementMax();
		return 0;
	}
	else {
			size--;
			Swap(heap[index], heap[size]); //zamiana pierwszego i ostatniego elementu
			int *heapTemp;
			heapTemp = new int[size];
			for (int i = 0; i<size; i++) //kopiowanie poprzednich czesci tablicy do nowej tablicy pomocniczej z pominieciem usunietego elementu
			{
				heapTemp[i] = heap[i];
			}
			delete[] heap;
			heap = new int[size];
			this->heap = heapTemp;

			SortDown(index); //przywrocenie wlasnosci kopca poprzez sortowanie od gory
	}

		return 0;
}

int BinaryHeap::DeleteElementIndex(int index) { // usuniecie wybranego elementu

	if (index < 0 || index >= size) {
		//std::cout << "nie ma takiej liczby w kopcu!";
		return -1;
	}
	else if (index == size - 1) {
		DeleteElementMin();
		return 0;
	}
	else if (index == 0) {
		DeleteElementMax();
		return 0;
	}
	else {
		size--;
		Swap(heap[index], heap[size]); //zamiana pierwszego i ostatniego elementu
		int *heapTemp;
		heapTemp = new int[size];
		for (int i = 0; i<size; i++) //kopiowanie poprzednich czesci tablicy do nowej tablicy pomocniczej z pominieciem usunietego elementu
		{
			heapTemp[i] = heap[i];
		}
		delete[] heap;
		heap = new int[size];
		this->heap = heapTemp;

		SortDown(index); //przywrocenie wlasnosci kopca poprzez sortowanie od gory
	}

	return 0;
}

int BinaryHeap::LoadFromFile(std::string filename) { //wczytanie kopca z pliku
	if (size != 0) // usuniecie listy w przydpadku niepustej listy	
		DeleteHeap();

	int pom = 0;
	std::fstream numbersFile;
	numbersFile.open(filename, std::ios::in);
	if (numbersFile.good() == false) //sprawdzenie czy dobrze wczytano plik z liczbami
	{
		std::cout << "Nie mozna wczytac pliku!";
		return -1;
	}

	int newSize = 0;
	numbersFile >> newSize;

	int index = 0;

	while (!numbersFile.eof()) //wczytywanie kolejnych liczb;
	{
		int pom;
		numbersFile >> pom;
		this->AddElement(pom);
		index++;
		if (index == newSize)
			break;
	}
	size = newSize;
	//std::cout << "Wczytano liczby z pliku do kopca.\n";

	return 0;
}

int BinaryHeap::CompareElements(int index, int element){ //funkcja pomocnicza (rekurencyjna) do znajdywania plików w kopcu

	if (index < size && index >= 0) //sprawdzanie czy indeks miesci sie w rozmiaze
	{
		int child1, child2, temp;
		child1 = (2 * index) + 1;
		child2 = child1 + 1; //przywolane zmiennych pomocniczych oznaczajacych potomkow
		temp = -1;

		if ((child1 < size) && (heap[child1] == element)) //jesli liczba == elementem w danym potomku zwracamy jego index
			temp = child1;
		
		else if ((child1 < size) && (heap[child1] > element)) //warunek dla pierwszego potomka
			temp = CompareElements(child1, element);
				
		if (temp >= 0)
			return temp;

		if ((child2 < size) && (heap[child2] == element))
			temp = child2;
		
		else if ((child2 < size) && (heap[child2] > element)) //warunek dla pierwszego potomka
			temp = CompareElements(child2, element);

		return temp;	
	}
	else return -1;
}

int BinaryHeap::FindElement(int element) { //pierwsza czesc funkcji odpowiedzialnej za znalezienie elementu w kopcu - zwraca index
	
	if (element > heap[0])
		return -1;
	else if (element == heap[0])
		return 0;
	else {
		int pom = CompareElements(0, element);
		return pom; 
	}
}


void BinaryHeap::gotoxy(int x, int y) //funckja pomocnicza w wyswietlaniu drzewa ustawiajaca kursor w odopowiednim miejscu.
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c); //funkcja ustawiajaca kursor w odpowiednim miejscu, dziala z pomoca biblioteki "windows.h"
}

void BinaryHeap::ShowHeap() { //wyswietlenie kopca

	if (size < 1) std::cout << "\nKopiec jest pusty!\n\n";
	else
	{
		system("cls"); //potrzebny dla dobrego wyswietlania kopca jak drzewo
		if (size > 0) { gotoxy(40, 1); std::cout << heap[0]; } //wyswietlenie konkretnego indeksu tablicy w odpowiednim miejscu
		if (size > 1) { gotoxy(20, 3); std::cout << heap[1]; }
		if (size > 2) { gotoxy(60, 3); std::cout << heap[2]; }
		if (size > 3) { gotoxy(10, 6); std::cout << heap[3]; }
		if (size > 4) { gotoxy(30, 6); std::cout << heap[4]; }
		if (size > 5) { gotoxy(50, 6); std::cout << heap[5]; }
		if (size > 6) { gotoxy(70, 6); std::cout << heap[6]; }
		if (size > 7) { gotoxy(5, 9); std::cout << heap[7]; }
		if (size > 8) { gotoxy(15, 9); std::cout << heap[8]; }
		if (size > 9) { gotoxy(25, 9); std::cout << heap[9]; }
		if (size > 10) { gotoxy(35, 9); std::cout << heap[10]; }
		if (size > 11) { gotoxy(45, 9); std::cout << heap[11]; }
		if (size > 12) { gotoxy(55, 9); std::cout << heap[12]; }
		if (size > 13) { gotoxy(65, 9); std::cout << heap[13]; }
		if (size > 14) { gotoxy(75, 9); std::cout << heap[14]; }
		std::cout << std::endl << std::endl;
	}
}

void BinaryHeap::Swap(int & p1, int & p2) { //zamiana dwoch liczb - potrzebna przy sortowaniu kopca

	int temp = p1;
	p1 = p2;
	p2 = temp;
}


int BinaryHeap::Menu() //Menu dla kopca binarnego typu MAX
{
	char select = 'y';

	while (select != '0')
	{
		if (size < 1)
		{
			std::cout << "\Kopiec nie zostal utworzony\n";
		}
		else
		{
			std::cout << "\nRozmiar kopca: " << size << std::endl;
		}
		std::cout << "Wybierz nastepujace opcje:\n\n1. Wczytaj z pliku\n2. Dodaj element do kopca\n3. Usun element z kopca\n4. Szukaj liczby\n9. Wyswietl elementy kopca\n0. Powrot do menu glownego (Wyjscie kasuje kopiec)" << std::endl;

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
			int pom;

			std::chrono::time_point<std::chrono::system_clock> start, end; //pomiar czasu
			start = std::chrono::system_clock::now();

			pom = LoadFromFile(filename);

			end = std::chrono::system_clock::now(); //koniec pomiaru
			std::chrono::duration<double> elapsed_seconds = end - start;

			if (pom = 0)
				std::cout << "Wczytano plik!\n";
			std::cout << "\nCzas wykonywania: " << elapsed_seconds.count() << " [s]\n";

		} break;

		case '2': {
			int var;
			std::cout << "\nPodaj liczbe: ";
			std::cin >> var;

			std::chrono::time_point<std::chrono::system_clock> start, end; //pomiar czasu
			start = std::chrono::system_clock::now();

			AddElement(var);

			end = std::chrono::system_clock::now(); //koniec pomiaru
			std::chrono::duration<double> elapsed_seconds = end - start;
			std::cout << "Dodano liczbe!\n";
			std::cout << "\nCzas wykonywania: " << elapsed_seconds.count() << " [s]\n";

		} break;

		case '3': {
			int var, pom;
			std::cout << "\nPodaj wartosc liczby do usuniecia: ";
			std::cin >> var;

			std::chrono::time_point<std::chrono::system_clock> start, end; //pomiar czasu
			start = std::chrono::system_clock::now();

			pom = DeleteElement(var);

			end = std::chrono::system_clock::now(); //koniec pomiaru
			std::chrono::duration<double> elapsed_seconds = end - start;

			if (pom == 0) {
				std::cout << "Liczba usunieta!\n";
			}
			else std::cout << "Liczby nie ma w kopcu\n";
			std::cout << "\nCzas wykonywania: " << elapsed_seconds.count() << " [s]\n";

		} break;

		case '4': {
			int var, pom;
			std::cout << "\nPodaj szukana liczbe: ";
			std::cin >> var;

			std::chrono::time_point<std::chrono::system_clock> start, end; //pomiar czasu
			start = std::chrono::system_clock::now();

			pom = FindElement(var);

			end = std::chrono::system_clock::now(); //koniec pomiaru
			std::chrono::duration<double> elapsed_seconds = end - start;

			if (pom >= 0)
				std::cout << "Podana liczba jest w kopcu\n";
			else std::cout << "Podanej liczby nie ma w kopcu\n";
			/*std::cout << "Indeks szukanej liczby: " << FindElement(var) << "\n\n"; //Wyswietla indeks liczby znalezionej*/


			std::cout << "\nCzas wykonywania: " << elapsed_seconds.count() << " [s]\n";

		} break;

		case '9': {
			ShowHeap();
		} break;

		case 'T': {

			char select2 = 'x';
			srand(time(NULL));
			while (select2 != '0')
			{
				std::cout << "\n-----------------------------\n---- Menu testow kopca ----\n-----------------------------\n\n";
				std::cout << "1. Dodawanie\n2. Usuwanie\n3. Wyszukiwanie losowo\n0. Powrot\n\n";
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

						AddElement(nrRandom); // funkcja testowana <--------

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

				case '3': {

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
