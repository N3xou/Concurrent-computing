#include <iostream>
#include <Windows.h>
#include <omp.h>
#include <thread>
#include <mutex>
#include <vector>
#include <fstream>
#include <filesystem>
using namespace std;

mutex mtx;

void Func(char character, int iterations, int delay, WORD color)
{
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
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

    ofstream outfile("output.txt");
    setlocale(LC_CTYPE, "Polish");
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    SetConsoleOutputCP(65001);

    for (int i = 0; i < 120; i++) { cout << "*"; }
    cout << "Autor programu: Damian Nussbaum" << endl;
    for (int i = 0; i < 120; i++) { cout << "*"; }
    char c;
    double duration;
    int iterations, delay;
    char character1, character2, character3;
    vector<double> times(5);

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
        times[0] = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1000;

        std::cout << std::endl;
        wcout << "Czas trwania programu: " << times[0] << " milisekund\n" << endl;
        outfile << times[0] << endl;

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
        times[1] = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1000;
        wcout << "Czas trwania programu: " << times[1] << " milisekund\n" << endl;
        outfile << times[1] << endl;

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
        times[2] = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1000;
        wcout << "Czas trwania programu: " << times[2] << " milisekund\n" << endl;
        outfile << times[2] << endl;

        wcout << "Zadania realizowane ROWNOLEGLE OpenMP - Liczba zadan 3" << endl;
        wcout << "KIERUNEK UPLYWU CZASU --->" << endl;
        QueryPerformanceCounter(&start);

#pragma omp parallel sections
        {
#pragma omp section
            {
                Func(character1, iterations, delay, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            }
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
        times[3] = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1000;
        wcout << "Czas trwania programu: " << times[3] << " milisekund\n" << endl;
        outfile << times[3] << endl;

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
        times[4] = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1000;
        wcout << "Czas trwania programu: " << times[4] << " milisekund\n" << endl;
        outfile << times[4] << endl;

        do
        {
            wcout << "Czy chcesz powtorzyc program (t/n): ";
            cin >> c;
            if (c == 't' || c == 'n')
                break;
        } while (true);

    } while (c == 't');

    outfile.close();
    cout << "Output file closed." << endl;
    return 0;
}
