/* Autor: Kacper Piątkowski */

#ifndef FUNKCJE_HPP
#define FUNKCJE_HPP

#include <iostream>
#include <random>
#include <fstream>
#include <cmath>

#define PLOT true      //* drukowanie danych srednich dla tablic wielkosci [2:MAX_LENGHT]
#define AVERAGE true    //* drukowanie danych srednich oraz odchylenia standardowego dla wielkosci tablicy ELEMENTS
#define SHOW_SORTING true //* drukowanie sortowania danych do terminala
#define SHOW_LENGHT 10 //* dlugosc tablicy do pokazywania sortowania 
#define NO_TESTS 100    //* ilosc probek dla danej wielkosci tablicy
#define ELEMENTS 500    //* wielkosc tablicy do liczenia sredniej ilosci operacji/odchylenia standardowego
#define MAX_LENGHT 500 //* maksymalna wielkość tablicy 

/**
 ** Wypelnienie tablicy losowymi wartosciami calkowitymi (od 0 do RAND_MAX) 
 * @param arr tablica do ktorej wpisujemy liczby
 * @param size wielkosc tablicy
*/
void fill_array(int *arr, int size)
{
    for(int i = 0; i<size; i++)
        arr[i] = rand() % 10000;
}

/**
 ** Wypelnienie tablicy losowymi wartosciami zmiennoprzecinkowymi (od 0 do 100) 
 * @param arr tablica do ktorej wpisujemy liczby
 * @param size wielkosc tablicy
*/
void fill_array_double(double *arr, int size)
{
    for(int i = 0; i<size; i++)
        arr[i] = ((double) rand() / RAND_MAX) * 100;
}

/**
 * @return srednia ilosc operacji 
 * @param avg tablica z iloscia operacji w danym tescie
 * @param size wielkosc tablicy
*/
double return_average(int *avg, int size)
{
    int sum = 0;
    for(int i = 0; i<size; i++)
        sum+= avg[i];
    return (double)sum/size;
}

/**
 * @return odchylenie standardowe 
 * @param avg tablica z iloscia operacji w danym tescie
 * @param size wielkosc tablicy
 * @param average srednia wyliczona z funkcji return_average()
*/
double return_deviation(int *avg, int size, double average)
{
    long sum = 0;
    for(int i = 0; i<size; i++)
        sum += pow((avg[i] - average), 2);
    return sqrt(sum/size);
}

/**
 ** Wydrukowanie tablicy
 *  @param array tablica do wydruku  
*/
template<typename T>
void show(T const& array)
{
    for(auto x : array) {
        std::cout << x << " ";
    }
    putchar('\n');
}

//* Wypisuje linie skladajaca sie z '=' i '-' (separator miedzy poszczegolnymi etapami wypisywania)
inline void print_line() { std::cout << "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n"; }

#endif