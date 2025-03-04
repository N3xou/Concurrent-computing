// Wspolbiezne1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
using namespace std;

void Func(char character, int iterations, int delay, WORD color)
{
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hconsole, color);
	for (int i = 0; i < iterations; i++)
	{
		cout << character << " ";
		if (delay > 0) {
			Sleep(delay);
		}
	}
	SetConsoleTextAttribute(hconsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}


int main()
{
	setlocale(LC_ALL, "pl_PL");
	LARGE_INTEGER frequency;
	LARGE_INTEGER start;
	LARGE_INTEGER end;
	
	SetConsoleOutputCP(65001);	

	for (int i = 0; i < 120; i++){cout << "*";}
	cout << "Autor programu: Damian Nussbaum" << endl;
	for (int i = 0; i < 120; i++) { cout << "*";}
	char c;
	double duration;
	int iterations, delay;
	char character1, character2, character3;
	do {
		wcout << "-> Podaj liczbe iteracji: ";
		cin >> iterations;
		wcout << "-> Podaj opoznienie: ";
		cin >> delay;
		wcout << "Podaj pierwszy znak: ";
		cin >> character1;
		wcout << "Podaj drugi znak: ";
		cin >> character2;
		wcout << "Podaj trzeci: ";
		cin >> character3;
		wcout << "Zadania realizowane SEKWENCYJNIE - Liczba zadan 3" << endl;
		wcout << "KIERUNEK UPLYWU CZASU --->" << endl;
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&start);
		Func(character1, iterations, delay, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	
		Func(character2, iterations, delay, FOREGROUND_RED | FOREGROUND_INTENSITY);

		Func(character3, iterations, delay, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		QueryPerformanceCounter(&end);
		std::cout << std::endl;
		duration = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;
		wcout << "Czas trwania programu: " << duration << " sekund" << endl;
		do
		{
			wcout << "Czy chcesz powtorzyc program (t/n): ";
			cin >> c;
			if (c == 't' || c == 'n')
				break;
			
		} while (true);
	} while (c == 't');
};

