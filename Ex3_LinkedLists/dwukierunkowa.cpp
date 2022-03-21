#include "dwukierunkowa.hpp"
#include <limits>

#define NO_OPTIONS 12

/**
 ** pobranie od uzytkownika opcji
 * @return numer wybranej opcji
*/
int get_option()
{
    int x = 0;
    while(true)
    {
        try
        {
            std::cin >> x;
            if(x < 1 || x > NO_OPTIONS)
                throw std::out_of_range("Not an option");
            break;
        }
        catch(const std::exception& e)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Wprowadz liczbe miedzy [1;" << NO_OPTIONS << "]\n";
        }
    }
    return x;
}

//* menu wyświetlające sie użytkownikowi na początku programu 
int menu()
{
    std::cin.exceptions(std::ios::failbit | std::ios::badbit);
    std::cout << std::endl << "\033[1;33m=================================================================";
    std::cout << std::endl << "1. Wyswietl liste" << std::endl;
    std::cout << "2. Dodaj element na koniec listy" << std::endl;
    std::cout << "3. Dodaj element na poczatek listy" << std::endl;
    std::cout << "4. Dodaj element na wybrane miejsce w liscie" << std::endl;
    std::cout << "5. Usun ostatni element listy" << std::endl;
    std::cout << "6. Usun pierwszy element listy" << std::endl;
    std::cout << "7. Usun wybrany element listy" << std::endl;
    std::cout << "8. Usun element na wybranej pozycji" << std::endl;
    std::cout << "9. Sprawdz czy element znajduje sie na liscie" << std::endl;
    std::cout << "10. Posortuj liste" << std::endl;
    std::cout << "11. Wyczyść liste" << std::endl;
    std::cout << "12. Wyjdz z programu." << std::endl;
    std::cout << "=================================================================";
    std::cout << std::endl << "Dokonaj wyboru: " << std::endl;
    int n;
    n = get_option();
    std::cout << "=================================================================\033[0m" << std::endl;
    return n;
}

int main()
{
    int liczby[12] = {5,9,8,10,16,12,10,5,13,22,51,65};
    List_t<int> lista(liczby, 12);
    int element, position;
    bool run = true;

    while(run)
    {
        switch(menu())
        {
            case 1:
                std::cout << std::endl;
                lista.print();
                break;

            case 2:
                std::cout << "\nPodaj element jaki chcesz dodac: ";
                std::cin >> element;
                lista.push_back(element);
                std::cout << "\033[32mElement '" << element <<  "' zostal dodany\033[0m\n";
                lista.print();                
                break;

            case 3:
                std::cout << "\nPodaj element jaki chcesz dodac: ";
                std::cin >> element;
                lista.push_front(element);
                std::cout << "\033[32mElement '" << element <<  "' zostal dodany\033[0m\n";
                lista.print();                
                break;

            case 4:
            
                std::cout << "\nPodaj element jaki chcesz dodac: ";
                std::cin >> element;
                lista.print();
                std::cout << "\nPodaj miejsce na ktore chcesz dodac element z przedzialu [1:" << lista.get_size()+1 << "] : ";
                std::cin >> position;
                if(position >= 1 && position <= lista.get_size()+1){
                    lista.insert(element, position-1);
                    std::cout << "\033[32mElement '" << element << "' zostal dodany\033[0m\n\n";
                    lista.print();
                }
                else
                    std::cout << "\033[31mZostala wybrana pozycja spoza zakresu listy. Element nie zostal dodany.\033[0m\n";
                break;

            case 5:
                if(!lista.is_empty()) {
                    element = lista.back();
                    lista.pop_back();
                    std::cout << "\n\033[32mElement '" << element << "' zostal usuniety\033[0m\n\n";
                    lista.print();
                }
                else {
                    std::cout << std::endl;
                    lista.print();
                }
                break;

            case 6:
                if(!lista.is_empty()) {
                    element = lista.front();
                    lista.pop_front();
                    std::cout << "\n\033[32mElement '" << element << "' zostal usuniety\033[0m\n\n";
                    lista.print();
                }
                else {
                    std::cout << std::endl;
                    lista.print();
                }
                break;

            case 7:
                std::cout << std::endl;
                if(lista.is_empty()){
                    lista.print();
                    break;
                }
                lista.print();
                std::cout << "\nJaki element chcesz usunac? : ";
                std::cin >> element;
                if(lista.contains(element)) {
                    lista.erase(lista.find(element));
                    std::cout << "\n\033[1;32mElement '" << element << "' zostal usuniety\033[0m\n";
                    lista.print();
                }
                else
                    std::cout << "\n\033[1;31mElement nie znajduje sie na liscie, więc nie zostal usuniety.\033[0m\n";
                break;

            case 8:

                if(!lista.is_empty()){
                    std::cout << std::endl;
                    lista.print();
                    std::cout << "\nPodaj miejsce elementu ktory chcesz usunac z przedzialu [1:" << lista.get_size() << "] : ";
                    std::cin >> position;
                    if(position >= 1 && position <= lista.get_size()) {
                        element = lista.on_index(position-1);
                        lista.erase(position-1);
                        std::cout << "\033[32mElement o indeksie '" << position << "' i wartosci '" << element << "' zostal usniety\033[0m\n\n";
                        lista.print();
                    }
                    else{
                        std::cout << "\033[31mZostala wybrana pozycja spoza zakresu listy. Element nie zostal usuniety.\033[0m\n";
                    }
                }
                else
                    std::cout << "\n\033[1;31mLista jest pusta, wiec element nie zostal usuniety.\033[0m\n";
                break;

            case 9:
                if(lista.is_empty()) {
                    std::cout << std::endl;
                    lista.print();
                    break;
                }
                std::cout << "\nWpisz element ktory chcesz sprawdzic czy znajduje sie na liscie: ";
                std::cin >> element;
                if(lista.contains(element))
                    std::cout << "\n\033[1;32mElement '"<< element << "' znajduje sie na liscie\033[0m\n";
                else
                    std::cout << "\n\033[1;31mElement '"<< element << "' nie znajduje sie na liscie\033[0m\n";
                break;

            case 10:
                if(!lista.is_empty()){
                    std::cout << "\nPrzed sortowaniem:\n";   
                    lista.print();
                    lista.sort();
                    std::cout << "Po sortowaniu:\n";
                    lista.print();
                }
                else{
                    std::cout << std::endl;
                    lista.print();
                }
                break;

            case 11:
                std::cout << std::endl;
                lista.print();
                if(lista.is_empty())
                    break;
                std::cout << "\n\033[1;31mCzyszczenie listy...\033[0m\n\n";
                lista.clear();
                lista.print();
                break;
            case 12:
                run = false;
                break;

            default:
                break;
        }
    }
}