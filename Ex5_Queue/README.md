# **Autor: Kacper Piątkowski** #

## Zawartosc i opis ##

#
Katalog zawiera:

* 2 pliki **hpp** - `kolejka_tablicowo.hpp` i `kolejka_wskaznikowo.hpp` w ktorej znajduje sie implementacja kolejki tablicowo i wskaznikowo
* 2 pliki **cpp** - `kolejka_tablicowo.cpp` i `kolejka_wskaznikowo.cpp` w ktorej znajduje sie prezentacja kolejek
#

## Funkcje w kolejkach ##

#
### **Pola klasy**
#

**Implementacja tablicowa:**
* `array` - dynamicznie alokowana tablica w ktorej przechowujemy kolejke
* `arraySize` - aktualna wielkosc tablicy
* `mSize` - przechowuje aktualną wielkość kolejki
* `head` - index pierwszego elementu w kolejce

#
**Implementacja wskaznikowa:**
* `mSize` - przechowuje aktualną wielkość kolejki
* `head` - przechowuje node znajdujacy sie na poczatku kolejki
* `last` - przechowuje node znajdujacy sie na koncu kolejki
#

### **Metody prywatne klasy**

#

* `void resize()` - funkcja wywolywana gdy aktualna tablica przechowująca kolejke nie będzie w stanie dodać kolejnego elementu (ze wzgledu na przekroczenie wielkosci tablicy)

#
### **Metody publiczne klasy**
#

* `void push(T data)` - dodaje element na tył kolejki
* `T pop()` - usuwa element z poczatku kolejki i zwraca jego wartość
* `const T& top()` - zwraca wartość elementu na poczatku kolejki 
* `const T& back()` - zwraca wartość elementu na końcu kolejki 
* `int size()` - zwraca wielkosc kolejki
* `void clear()` - usuwa wszystkie elementy kolejki
* `void print()` - wypisuje kolejke

#
## Jak uruchomic programy:

* Standardowa kompilacja:
        `g++ kolejka_tablicowo.cpp` albo `g++ kolejka_wskaznikowo.cpp`
* Wywołanie:
        `./a.out`

* Po wywołaniu w terminalu powinno wyświetlić się menu, któro służy użytkownikowi do operacji na kolejce
#