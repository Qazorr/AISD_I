# Autor: Kacper Piątkowski #

## Zawartosc i opis ##

Katalog zawiera:

* 2 pliki hpp - `jednokierunkowa.hpp` i `dwukierunkowa.hpp` w ktorej znajduje sie implementacja list jedno i dwukierunkowych.
* 2 pliki cpp - `jednokierunkowa.cpp` i `dwukierunkowa.cpp` w ktorej znajduje sie prezentacja listy jedno i dwukierunkowej.

#

## Funkcje w listach ##

#### Pola klasy
* `size` - przechowuje aktualną wielkość listy
* `head` - wskaźnik na pierwszy element w liście
* `tail` - wskaźnik na ostatni element w liście

#

#### Metody prywatne klasy
* `void push_first(T data)` - używane jeśli dodajemy pierwszy element do pustej listy
* `void pop_single()` - używane jeśli usuwamy element w liście jednoelementowej

#

#### Metody publiczne klasy
* `int get_size()` - zwraca wielkosc listy
* `bool is_empty()` - zwraca **true** jesli lista jest pusta, w przeciwnym wypadku **false**
* `const T& front()` - zwraca refrencje do wartosci pierwszego elementu
* `const T& back()` - zwraca refrencje do wartosci ostatniego elementu
* `void push_front(T data)` - dodaj element na poczatek listy
* `void push_back(T data)` - dodaj element na koniec listy
* `void insert(T data, int pos)` - dodaj element na określoną pozycje
* `void insert(T data, Iterator it)` - dodaj element za element wskazywany przez iterator
* `void pop_front()` - usun element z poczatku listy
* `void pop_back()` - usun element z konca listy
* `void erase(Iterator it)` - usun element o podanym iteratorze (np erase(find(2)))
* `void erase(int pos)` - usun element na danej pozycji
* `bool contains(const T& data)` - zwraca **true** jesli element znajduje się na liście, w przeciwnym wypadku zwraca **false** 
* `Iterator find(T data)` - zwraca iterator do elementu o wartosci **data**
* `void sort()` - sortuje liste
* `void print()` - wypisuje liste
* `Iterator begin()` - zwraca Iterator poczatku listy
* `Iterator end()` - zwraca Iterator konca listy

#

## Jak uruchomic programy:

* Standardowa kompilacja:
        `g++ jednokierunkowa.cpp` albo `g++ dwukierunkowa.cpp`
* Wywołanie:
        `./a.out`
* Po uruchomieniu powinno pojawic sie menu dzieki któremu bedziemy modyfikowac oraz sprawdzać naszą liste
* Lista defaultowo posiada **12** elementów (jest ona inicjalizowana przez tablice 12 elementów [intów])

#