//* Autor: Kacper Piątkowski

#include "funkcje.hpp"

/**
 ** Implementacja sortowania przez wybieranie (selection sort)
 * @param arr tablica ktora chcemy posortowac
 * @param size wielkosc tej tablicy
 * @return ilosc operacji wykonanych przy sortowaniu (porownania + zamiany)
*/
template <typename T>
int selection_sort(T *arr, int size)
{
    int no_operations = 0;
    int min_index = 0;
    T min_value = arr[0];

    for(int i = 0; i<size-1; i++){
        for(int j = i; j<size; j++){
            if(arr[j] <= min_value){    //* jesli aktualna minimalna wartosc jest wieksza, zmien ja na mniejsza i zachowaj index
                min_value = arr[j];
                min_index = j;
            }
            no_operations++;    //* zliczenie porownania
        }
        std::swap(arr[i], arr[min_index]);  //* zamieniam najmniejsza wartosc z elementem o kolejnym indeksie
        no_operations++;    //* zliczenie zamiany
        min_value = arr[i+1];
    }
    return no_operations;
}

int main(int argc, char* argv[])
{   
    srand(time(NULL));  //Ustawiamy seed dla naszego pseudolosowania

    if(PLOT) {
        print_line();
        std::cout << "SELECTION.DATA FILE WAS CREATED AND THE DATA IS CONSTANTLY ADDED\n";
        std::ofstream selection_file("selection.data"); // do tego pliku umieszczam srednia ilosc operacji po NO_TESTS probach dla tablicy wielkosci 'i'
        for(int i = 2; i<=MAX_LENGHT; i++) {
            int *plot_average = new int[NO_TESTS];  // tworze nową tablice w ktorej bede przechowywal ilosc operacji z danego testu
            for(int j = 0; j<NO_TESTS; j++) {
                int *array = new int[i];      // tworze nowa tablice o wielkosci 'i' i wypelniam ja zrandomizowanymi danymi
                fill_array(array, i);
                plot_average[j] = selection_sort(array, i); // wpisuje ilosc operacji wykonanych w tescie
                delete [] array;
            }
            selection_file << return_average(plot_average, NO_TESTS) << std::endl; // wypisuje do pliku srednią po 100 testach
            delete [] plot_average;
        }
        selection_file.close();
        std::cout << "THE DATA WAS PLACED SUCCESFULLY IN SELECTION.DATA FILE\n";
        print_line();

    }

    if(AVERAGE) {
        std::cout << "OPERATIONS_SELECTION.DATA WAS CREATED.\n";
        std::ofstream results("operations_selection.data", std::ios_base::app); // plik w ktorym przechowuje rezultaty po testach
        int array[ELEMENTS]; // tablica w ktorej beda znajdowac sie zrandomizowane liczby
        int operations[NO_TESTS];
        for(int i = 0; i<NO_TESTS; i++) {
            fill_array(array, ELEMENTS);
            operations[i] = selection_sort(array, ELEMENTS); // wpisuje ilosc operacji wykonanych w tescie
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
        selection_sort(tablica_int, SHOW_LENGHT);
        show(tablica_int);

        print_line();

        double tablica_double[SHOW_LENGHT];
        fill_array_double(tablica_double, SHOW_LENGHT);
        std::cout << "ARRAY AT BEGINNING (DOUBLE):" << std::endl;
        show(tablica_double);
        std::cout << "SORTED ARRAY:"<<std::endl;
        selection_sort(tablica_double, SHOW_LENGHT);
        show(tablica_double);

        print_line();

        std::string tablica_string[SHOW_LENGHT] = {"branch", "outrageous","gaudy" ,"garrulous" ,"heady" ,"murky" ,"roll" ,"hateful" ,"boring" ,"rhetorical"};
        std::cout << "ARRAY AT BEGINNING (STRING):" << std::endl;
        show(tablica_string);
        std::cout << "SORTED ARRAY:"<<std::endl;
        selection_sort(tablica_string, SHOW_LENGHT);
        show(tablica_string);

        print_line();
    }
}