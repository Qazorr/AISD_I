# Autor: Kacper Piątkowski                        

## Zawartosc i opis

Katalog zawiera:
2 programy zawierajace implementacje 2 algorytmów sortowania:
* `sortowania bąbelkowego (bubble sort)`
* `sortowania przez wybieranie (selection sort)`

* Plik `funkcje.hpp` gdzie zostala zawarta implementacja funckji pomocniczych
    takich jak srednia arytmetyczna, odchylenie standardowe, losowanie liczb,
    oraz wypisywanie tablicy.

* Plik `Dokumentacja.pdf`, gdzie znajduje sie wyliczenie złożonosci dla
    danego sortu oraz porównanie jednego z drugim na wykresach.

## Dyrektywy w programie

W programach można uruchomić trzy tryby zmieniając wartosc dyrektywy
        z false na true:
* `PLOT` -> odpowiada za wydruk sredniej ilosci operacji po 100 probach
        gdzie numer linii + 1 to wielkosc tablicy
* `AVERAGE` -> odpowiada za wypisanie sredniej ilosci operacji po 100
        probach oraz odchylenia standardowego dla tablicy wielkosci
            ELEMENTS
* `SHOW_SORTING` -> odpowiada za wyswietlenie sortowania do terminala
        trzech tablic (intów, doubli oraz stringów)

Standardowo wszystkie ustawione są na true.

    
## Jak uruchomic programy:

* Standardowa kompilacja:
        `g++ bubble_sort.cpp lub g++ selection_sort.cpp`
* Wywołanie:
        `./a.out`

* Jesli `PLOT == true` (patrz wyżej) wartosci zostane zapisane do pliku
        sortname.data
* Jesli `AVERAGE == true` (patrz wyzej) wartosci dla danej wielkosci 
        `ELEMENTS` beda wpisane do pliku operations_sortname.data
