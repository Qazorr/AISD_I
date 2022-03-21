//* Autor: Kacper Piątkowski

#include "funkcje.hpp"

/**
 ** Implementacja sortowania bąbelkowego (bubble sort)
 * @param arr tablica ktora chcemy posortowac
 * @param size wielkosc tej tablicy
 * @return ilosc operacji wykonanych przy sortowaniu (porownania + zamiany)
*/
template<typename T>
int bubble_sort(T *arr, int size)
{
    int no_operations = 0;  //* licznik operacji
    for(int i = 0; i<size-1; i++) {
        for(int j = 0; j<size-i-1; j++){    //* odejmujemy 'i' poniewaz wiemy ze liczba ktora "wyplynela" na koniec jest najwieksza
            if(arr[j] > arr[j+1]){  //* jesli poprzednik jest wiekszy od nastepnika zamien miejscami i zwieksz liczbe operacji
                std::swap(arr[j], arr[j+1]);
                no_operations++;
            }
            no_operations++;    //* zwiekszam ilosc operacji poniewaz w kazdej iteracji porownuje dwa elementy (arr[j] i arr[j+1])
        }
    }
    return no_operations;
}

int main(int argc, char* argv[])
{   
    srand(time(NULL)); //Ustawiamy seed dla naszego pseudolosowania

    if(PLOT) {
        print_line();
        std::cout << "BUBBLE.DATA FILE WAS CREATED AND THE DATA IS CONSTANTLY ADDED\n";
        std::ofstream bubble_file("bubble.data");   // do tego pliku umieszczam srednia ilosc operacji po NO_TESTS probach dla tablicy wielkosci 'i'
        for(int i = 2; i<=MAX_LENGHT; i++) {
            int *operations = new int[NO_TESTS];  // tworze nową tablice w ktorej bede przechowywal ilosc operacji z danego testu
            for(int j = 0; j < NO_TESTS; j++) {
                int *array = new int[i];     // tworze nowa tablice o wielkosci 'i' i wypelniam ja zrandomizowanymi danymi
                fill_array(array, i);
                operations[j] = bubble_sort(array, i);    // wpisuje ilosc operacji wykonanych w tescie
                delete [] array;
            }
            bubble_file << return_average(operations, NO_TESTS) << std::endl;  // wypisuje do pliku srednią po 100 testach
            delete [] operations;
        }
        bubble_file.close();
        std::cout << "THE DATA WAS PLACED SUCCESFULLY IN BUBBLE.DATA FILE\n";
        print_line();
    }

    if(AVERAGE) {
        std::cout << "OPERATIONS_BUBBLE.DATA WAS CREATED.\n";
        std::ofstream results("operations_bubble.data", std::ios_base::app); // plik w ktorym przechowuje rezultaty po testach
        int array[ELEMENTS];    // tablica w ktorej beda znajdowac sie zrandomizowane liczby
        int operations[NO_TESTS];
        for(int i = 0; i<NO_TESTS; i++) {
            fill_array(array, ELEMENTS);    
            operations[i] = bubble_sort(array, ELEMENTS);  // wpisuje ilosc operacji wykonanych w tescie
        }
        double average = return_average(operations, NO_TESTS); // wyliczam srednia ilosc operacji po 100 testach i wypisuje srednia oraz odchylenie
        results << "Array consisting " << ELEMENTS << " elements:" << std::endl;
        results << "\tAverage after 100 tests = " << average << std::endl;
        results << "\tStandard deviation after 100 tests = " << return_deviation(operations, NO_TESTS, average) << std::endl;
        results.close();
        std::cout << "DATA WAS SUCCESFULLY ADDED\n";
        print_line();
    }

    // Tworze tablice, wypełniam ją, po czym pokazuję ją w stanie początkowym, sortuje i ponownie wypisuje. 
    if(SHOW_SORTING) {
        int tablica_int[SHOW_LENGHT];
        fill_array(tablica_int, SHOW_LENGHT);
        std::cout << "ARRAY AT BEGINNING (INT):" << std::endl;
        show(tablica_int);
        std::cout << "SORTED ARRAY:"<<std::endl;
        bubble_sort(tablica_int, SHOW_LENGHT);
        show(tablica_int);

        print_line();

        double tablica_double[SHOW_LENGHT];
        fill_array_double(tablica_double, SHOW_LENGHT);
        std::cout << "ARRAY AT BEGINNING (DOUBLE):" << std::endl;
        show(tablica_double);
        std::cout << "SORTED ARRAY:"<<std::endl;
        bubble_sort(tablica_double, SHOW_LENGHT);
        show(tablica_double);

        print_line();

        std::string tablica_string[SHOW_LENGHT] = {"branch", "outrageous","gaudy" ,"garrulous" ,"heady" ,"murky" ,"roll" ,"hateful" ,"boring" ,"rhetorical"};
        std::cout << "ARRAY AT BEGINNING (STRING):" << std::endl;
        show(tablica_string);
        std::cout << "SORTED ARRAY:"<<std::endl;
        bubble_sort(tablica_string, SHOW_LENGHT);
        show(tablica_string);

        print_line();

    }
}