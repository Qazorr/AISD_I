#include "stos_wskaznikowo.hpp"
#include <limits>

#define NO_OPTIONS 6

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
    std::cout << std::endl << "1. Wyswietl stos" << std::endl;
    std::cout << "2. Dodaj element na stos" << std::endl;
    std::cout << "3. Usun element z góry stosu" << std::endl;
    std::cout << "4. Wypisz wartosc elementu z góry stosu" << std::endl;
    std::cout << "5. Wyczysc stos" << std::endl;
    std::cout << "6. Wyjdz z programu." << std::endl;
    std::cout << "=================================================================";
    std::cout << std::endl << "Dokonaj wyboru: " << std::endl;
    int n;
    n = get_option();
    std::cout << "=================================================================\033[0m" << std::endl;
    return n;
}

int main()
{
    Stack<int> stack;
    int element;
    bool run = true;
    while(run)
    {
        try {
            switch(menu())
            {
                case 1:
                    std::cout << std::endl;
                    stack.print();
                    break;
                    
                case 2:
                    std::cout << "\nPodaj element jaki chcesz dodac: ";
                    std::cin >> element;
                    stack.push(element);
                    std::cout << "\n\033[32mElement '" << element <<  "' zostal dodany\033[0m\n\n";
                    stack.print();
                    break;

                case 3:
                    element = stack.pop();
                    std::cout << "\n\033[32mElement o wartosci '" << element <<  "' zostal usuniety\033[0m\n\n";
                    stack.print();
                    break;

                case 4:
                    element = stack.top();
                    std::cout << "\n\033[32mElement na gorze stosu ma wartosc\033[0m \033[1;5;31m" << element << "\033[0m\n";
                    break;

                case 5:
                    std::cout << std::endl;
                    stack.print();
                    std::cout << "\n\033[32mCzyszczenie...\033[0m\n\n";
                    stack.clear();
                    stack.print();
                    break;

                case 6:
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