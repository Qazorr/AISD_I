# **Autor: Kacper Piątkowski** #

## Zawartosc i opis ##

#
Katalog zawiera:

* 2 pliki **hpp** - `stos_tablicowo.hpp` i `stos_wskaznikowo.hpp` w ktorej znajduje sie implementacja stosu tablicowo i wskaznikowo
* 2 pliki **cpp** - `stos_tablicowo.cpp` i `stos_wskaznikowo.cpp` w ktorej znajduje sie prezentacja stosów
#

## Funkcje w stosach ##

#
### **Pola klasy**
#

**Implementacja tablicowa:**
* `array` - dynamicznie alokowana tablica w ktorej przechowujemy stos
* `arrSize` - aktualna wielkosc tablicy
* `mSize` - przechowuje aktualną wielkość stosu

#
**Implementacja wskaznikowa:**
* `mSize` - przechowuje aktualną wielkość stosu
* `head` - przechowuje node znajdujacy sie na górze stosu
#

### **Metody prywatne klasy**

#

* `void resize()` - funkcja wywolywana gdy aktualna tablica przechowująca stos nie będzie w stanie dodać kolejnego elementu (ze wzgledu na przekroczenie wielkosci tablicy)

#
### **Metody publiczne klasy**
#

* `void push(T data)` - dodaje element na góre stosu
* `T pop()` - usuwa element z góry stosu i zwraca jego wartośc
* `const T& top()` - zwraca wartość elementu na górze stosu 
* `int size()` - zwraca wielkosc stosu
* `void clear()` - usuwa wszystkie elementy stosu
* `void print()` - wypisuje stos

#
## Jak uruchomic programy:

* Standardowa kompilacja:
        `g++ stos_tablicowo.cpp` albo `g++ stos_wskaznikowo.cpp`
* Wywołanie:
        `./a.out`

* Po wywołaniu w terminalu powinno wyświetlić się menu, któro służy użytkownikowi do operacji na stosie
#