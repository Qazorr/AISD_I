#include "BST.hpp"
#include <random>

#define NO_OPTIONS 9

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
    std::cout << std::endl << "1. Dodaj element do drzewa" << std::endl;
    std::cout << "2. Usun element z drzewa" << std::endl;
    std::cout << "3. Sprawdz czy element znajduje sie w drzewie." << std::endl;
    std::cout << "4. Wyswietl minimalna wartosc w drzewie" << std::endl;
    std::cout << "5. Wyswietl maksymalna wartosc w drzewie" << std::endl;
    std::cout << "6. Wypisz drzewo (inorder)" << std::endl;
    std::cout << "7. Wypisz drzewo (preorder)" << std::endl;
    std::cout << "8. Wypisz drzewo (postorder)" << std::endl;
    std::cout << "9. Wyjdz z programu" << std::endl;
    std::cout << "=================================================================";
    std::cout << std::endl << "Dokonaj wyboru: " << std::endl;
    int n;
    n = get_option();
    std::cout << "=================================================================\033[0m" << std::endl;
    return n;
}

int main()
{
    BST<int> tree;
    int element;
    std::string mess = "should be empty";
    Node<int>* temp;
    bool run = true;

    while(run)
    {
        try {
            switch(menu())
            {
                case 1:
                    std::cout << "\nPodaj element jaki chcesz dodac: ";
                    std::cin >> element;
                    if(!tree.find(element)) {
                        tree.insert(element);
                        std::cout << "\n\033[32mElement '" << element <<  "' zostal dodany\033[0m\n\n";
                    } else {
                        std::cout << "\n\033[31mElement '" << element <<  "' znajduje sie juz w drzewie\033[0m\n\n";
                    }
                    break;
                    
                case 2:
                    std::cout << "\nPodaj element jaki chcesz usunac: ";
                    std::cin >> element;
                    if(tree.find(element)) {
                        tree.remove(element);
                        std::cout << "\n\033[32mElement o wartosci '" << element <<  "' zostal usuniety\033[0m\n\n";
                    } else {
                        std::cout << "\033[31mElement nie znajduje sie w drzewie wiec nie zostal usuniety\033[0m" << std::endl;
                    }
                    break;

                case 3:
                    std::cout << "\nJaki element chcesz sprawdzic?: ";
                    std::cin >> element;
                    temp = tree.find(element);
                    mess = temp ? "\033[32mElement znajduje sie w drzewie\033[0m" : "\033[31mElement nie znajduje sie w drzewie\033[0m";
                    std::cout << mess << std::endl;
                    break;

                case 4:
                    std::cout << "Minimum w drzewie = " << tree.min();
                    break;
                case 5:
                    std::cout << "Maximum w drzewie = " << tree.max();
                    break;
                case 6:
                    std::cout << "INORDER: ";
                    tree.display_inorder();
                    break;

                case 7:
                    std::cout << "PREORDER: ";
                    tree.display_preorder();
                    break;

                case 8:
                    std::cout << "POSTORDER: ";
                    tree.display_postorder();
                    break;

                case 9:
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