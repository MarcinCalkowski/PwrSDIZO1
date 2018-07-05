#include "stdafx.h"
#include "NumberGenerator.h"


NumberGenerator::NumberGenerator()
{
}

NumberGenerator::~NumberGenerator()
{
}

void NumberGenerator::GenerateNumbers()
{
	int range;
	int nrRandom;
	system("cls");
	std::cout << "Podaj ilosc liczb do wylosowania:\n";
	std::cin >> range;
	std::fstream plik_losowe;
	srand(time(NULL));
	plik_losowe.open("numbers.txt", std::ios::out);
	plik_losowe << range << std::endl;
	for (int i = 1; i <= range; i++)
	{
		nrRandom = rand();
		plik_losowe << nrRandom;
		if (i<range) { plik_losowe << "\n"; }
	};
	plik_losowe.close();
	std::cout << "Wylosowano liczby do pliku numbers.txt. \nNacisnij dowolny klawisz.\n";
	_getch();
}

void NumberGenerator::GenerateNumbersAuto(int range) {

	int nrRandom;
	std::fstream plik_losowe;
	srand(time(NULL));
	plik_losowe.open("testnumbers.txt", std::ios::out);
	plik_losowe << range << std::endl;
	for (int i = 1; i <= range; i++)
	{
		nrRandom = rand();
		plik_losowe << nrRandom;
		if (i<range) { plik_losowe << "\n"; }
	};
	plik_losowe.close();
}