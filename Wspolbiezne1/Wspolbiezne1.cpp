﻿// Wspolbiezne1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <omp.h>
#include <thread>
#include <mutex>
using namespace std;
mutex mtx;
void Func(char character, int iterations, int delay, WORD color)
{
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(hconsole, color);
	for (int i = 0; i < iterations; i++)
	{
		SetConsoleTextAttribute(hconsole, color);
		cout << character << " ";
		if (delay > 0) {
			Sleep(delay);
		}
	}
	SetConsoleTextAttribute(hconsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void FuncOMP(char character, int iterations, int delay, WORD color)
{
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(hconsole, color);
	for (int i = 0; i < iterations; i++)
	{
        #pragma omp critical
        {
            SetConsoleTextAttribute(hconsole, color);
            cout << character << " ";
        }
		if (delay > 0) {
			Sleep(delay);
		}
	}
	SetConsoleTextAttribute(hconsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void FuncMUT(char character, int iterations, int delay, WORD color)
{

	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(hconsole, color);
	for (int i = 0; i < iterations; i++)
	{
		{
			lock_guard<mutex> lock(mtx);
			SetConsoleTextAttribute(hconsole, color);
			cout << character << " ";
		}
		if (delay > 0) {
			Sleep(delay);
		}
	}
	SetConsoleTextAttribute(hconsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}


int main()
{
    setlocale(LC_CTYPE, "Polish");
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
        duration = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1000;
        wcout << "Czas trwania programu: " << duration << " milisekund\n" << endl;

        wcout << "Zadania realizowane ROWNOLEGLE - Liczba zadan 3" << endl;
        wcout << "KIERUNEK UPLYWU CZASU --->" << endl;
        QueryPerformanceCounter(&start);
        thread t1(Func, character1, iterations, delay, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        thread t2(Func, character2, iterations, delay, FOREGROUND_RED | FOREGROUND_INTENSITY);
        thread t3(Func, character3, iterations, delay, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        t1.join();
        t2.join();
        t3.join();
        QueryPerformanceCounter(&end);
        std::cout << std::endl;
        duration = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1000;
        wcout << "Czas trwania programu: " << duration << " milisekund\n" << endl;

        wcout << "Zadania realizowane ROWNOLEGLE - Liczba zadan 3" << endl;
        wcout << "KIERUNEK UPLYWU CZASU --->" << endl;
        QueryPerformanceCounter(&start);
        thread t4(FuncMUT, character1, iterations, delay, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        thread t5(FuncMUT, character2, iterations, delay, FOREGROUND_RED | FOREGROUND_INTENSITY);
        thread t6(FuncMUT, character3, iterations, delay, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        t4.join();
        t5.join();
        t6.join();
        QueryPerformanceCounter(&end);
        std::cout << std::endl;
        duration = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1000;
        wcout << "Czas trwania programu: " << duration << " milisekund\n" << endl;
        wcout << "Zadania realizowane ROWNOLEGLE OpenMP - Liczba zadan 3" << endl;
        wcout << "KIERUNEK UPLYWU CZASU --->" << endl;
        QueryPerformanceCounter(&start);

        #pragma omp parallel sections
        {
            #pragma omp single

                Func(character1, iterations, delay, FOREGROUND_BLUE | FOREGROUND_INTENSITY);

            #pragma omp section
            {
                Func(character2, iterations, delay, FOREGROUND_RED | FOREGROUND_INTENSITY);
            }
            #pragma omp section
            {
                Func(character3, iterations, delay, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }

        }


        QueryPerformanceCounter(&end);
        std::cout << std::endl;
        duration = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1000;
        wcout << "Czas trwania programu: " << duration << " milisekund\n" << endl;
        wcout << "Zadania realizowane ROWNOLEGLE OpenMP - Liczba zadan 3" << endl;
        wcout << "KIERUNEK UPLYWU CZASU --->" << endl;
        QueryPerformanceCounter(&start);
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                FuncOMP(character1, iterations, delay, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            }
            #pragma omp section
            {
                FuncOMP(character2, iterations, delay, FOREGROUND_RED | FOREGROUND_INTENSITY);
            }
            #pragma omp section
            {
                FuncOMP(character3, iterations, delay, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }

        }


        QueryPerformanceCounter(&end);
        std::cout << std::endl;
        duration = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1000;
        wcout << "Czas trwania programu: " << duration << " milisekund\n" << endl;




        do
        {
            wcout << "Czy chcesz powtorzyc program (t/n): ";
            cin >> c;
            if (c == 't' || c == 'n')
                break;
            
        } while (true);
        

    } while (c == 't');
    return 0;
}

