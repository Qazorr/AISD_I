#include "HashMap.hpp"
#include <random>

#define NO_OPTIONS 7
#define SIZE 10

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
    std::cout << std::endl << "1. Dodaj element do HashMapy" << std::endl;
    std::cout << "2. Usun element z HashMapy" << std::endl;
    std::cout << "3. Sprawdz czy klucz znajduje sie w HashMapie" << std::endl;
    std::cout << "4. Wypisz wartosc z HashMapy podajac klucz" << std::endl;
    std::cout << "5. Wypisz HashMape" << std::endl;
    std::cout << "6. Wypisz wielkosc HashMapy" << std::endl;
    std::cout << "7. Wyjdz z programu" << std::endl;
    std::cout << "=================================================================";
    std::cout << std::endl << "Dokonaj wyboru: " << std::endl;
    int n;
    n = get_option();
    std::cout << "=================================================================\033[0m" << std::endl;
    return n;
}

int main(int argc, char const *argv[])
{
    HashMap<SIZE, int> map;
    using entry = Entry<std::string, int>;
    entry tmp;
    std::string key{}, mess{};
    int value{};
    bool run = true;

    while(run)
    {
        try {
            switch(menu())
            {
                case 1:
                    std::cout << "\nPodaj klucz: ";
                    std::cin >> key;
                    std::cout << "Podaj wartosc: ";
                    std::cin >> value;
                    tmp = entry(key, value);
                    if(!map.find(key)) {
                        map.insert(tmp);
                        std::cout << "\n\033[32mElement '" << tmp << "' zostal dodany\033[0m\n\n";
                    } else {
                        std::cout << "\n\033[31mElement '" << tmp <<  "' zostal zmodyfikowany\033[0m\n\n";
                    }
                    break;
                    
                case 2:
                    std::cout << "\nPodaj klucz: ";
                    std::cin >> key;
                    if(map.find(key)) {
                        map.remove(key);
                        std::cout << "\n\033[32mElement o kluczu '" << key <<  "' zostal usuniety\033[0m\n\n";
                    } else {
                        std::cout << "\033[31mElement nie znajduje sie w HashMapie wiec nie zostal usuniety\033[0m" << std::endl;
                    }
                    break;

                case 3:
                    std::cout << "\nJaki klucz chcesz sprawdzic?: ";
                    std::cin >> key;
                    mess = (map.find(key) ? "\033[32mKlucz znajduje sie w HashMapie\033[0m" : "\033[31mKlucz nie znajduje sie w HashMapie\033[0m");
                    std::cout << mess << std::endl;
                    break;

                case 4:
                    std::cout << "\nJaki klucz chcesz sprawdzic?: ";
                    std::cin >> key;
                    std::cout << map[key] << std::endl;
                    break;

                case 5:
                    map.display();
                    break;

                case 6:
                    std::cout << map.size() << std::endl;
                    break;

                case 7:
                    run = false;
                    break;

                default:
                    break;
            }
        } catch(std::exception& e) {
            std::cout << std::endl << e.what() << std::endl;
        }
    }
}