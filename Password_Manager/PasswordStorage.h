//
// Created by barte on 10.01.2023.
//

#ifndef MANAGER_HASEL_PASSWORDSTORAGE_H
#define MANAGER_HASEL_PASSWORDSTORAGE_H


#include "Password.h"
#include <memory>
#include <fstream>
#include <iostream>
#include <ctime>


using namespace std;

/**
 *
 *  @brief Klasa przechowująca obiekty klasy Password w wektorze
 *
 * */
class PasswordStorage {

public:
    vector<Password> passwords;

    /** @brief konstruktor, który wczytuje z pliku hasła do wektora. Wymagane jest hasło. Po wpisaniu błędnego hasła zostaje zapisana informacja w pliku LOG.txt */
    PasswordStorage() {
        cout << "Podaj haslo.";
        string pass = "abcXYZ";
        string tryPass;
        bool isPassed = false;

        while (!isPassed) {
            cin >> tryPass;
            if (tryPass == pass) {
                passwords = readPasswordsFromFile();
                isPassed = true;
            } else {
                string path = "C://Users//barte//CLionProjects//Manager_hasel//LOG.txt";
                fstream outfile(path);
                outfile << "Nieudana proba logowania: " << currentDateTime() << "\n";

                cout << "Podano bledne haslo. Sproboj ponownie: ";
            }
        }
    }




    /** @brief funkcja dodajaca haslo za pomoca konstruktora klasy Password */
    void addPassword() {
        passwords.push_back(*new Password());
    }

    /** @brief funkcja usuwajaca kategorie po indeksie wektora. W przypadku usuniecia kategorii, zostana usuniete takze wszystkie hasla do niej przypisane */
    void deleteCategory() {
        int choice;
        int choice2;
        cout << "wybierz kategorie do usuniecia:\n";
        passCat.printCategories();
        cin >> choice;

        cout << "Czy jestes pewien, ze chcesz usunac kategorie?\n"
                "Usuniesz takze wszystkie hasla, ktore do niej naleza.\n"
                "1. Tak\n"
                "2. Nie\n";
        cin >> choice2;

        switch (choice2) {
            case 1: {
                for (int i = 0; i < passwords.size(); ++i) {
                    if (passwords[i].getCategory() == passCat.cat[i])
                        passwords.erase(passwords.begin() + i);
                }
                passCat.cat.erase(passCat.cat.begin() + choice);
                break;
            }
            case 2: {
                cout << "kategoria nie zostala usunieta.\n";
                break;
            }
        }
    }

    /** @brief funkcja edytująca informacje o haśle */
    void editPassword() {
        int choice;
        cout << "wybierz haslo do edycji: \n";
        for (int i = 0; i < passwords.size(); ++i) {
            cout << 1 + i << ".\n";
            passwords[i].print();
            cout << "\n";
        }
        cin >> choice;
        passwords[choice - 1].editPasswordInfo();
        cout << "Pomyslnie edytowano dane.\n";
    }

    /** @brief Funkcja usuwajaca hasło po indeksie wektora */
    void deletePassword() {
        int choice;
        int choiceDel;

        cout << "wybierz haslo do usuniecia: \n";

        // wyswietlenie wszystkich obiektow typu Password, ktore znajduja sie w wektorze passwords
        for (int i = 0; i < passwords.size(); ++i) {
            cout << 1 + i << ".\n";
            passwords[i].print();
            cout << "\n";
        }

        cin >> choice;

        cout << "Czy jestes pewny, ze chcesz usunac to haslo?\n"
             << "1. Tak"
             << "2. Nie\n";
        cin >> choiceDel;

        switch (choiceDel) {
            case 1: {
                passwords.erase(passwords.begin() + choice);
                cout << "Pomyslnie usunieto\n";
                break;
            }
            case 2:
                cout << "haslo nie zostalo usuniete.\n";
                break;
            default:
                cout << "wybrano zly numer.";
                break;
        }
    }

    void sortStorage() {}

    /** @brief funkcja wyszukująca hasła, zależnie od parametru. */
    void findPasswords() {
        int choice;
        string text;
        vector<Password> foundPasswords;
        cout << "Po jakim parametrze chcesz wyszukac haslo?\n"
             << "1. Nazwa\n"
             << "2. kategoria\n"
             << "3. strona\n"
             << "4. login\n";
        cin >> choice;

        switch (choice) {
            // Wyszukiwanie po nazwie
            case 1: {
                cout << "Podaj nazwe, ktorej szukasz.";
                cin >> text;
                for (int i = 0; i < passwords.size(); ++i) {
                    if (text == passwords[i].getName())
                        foundPasswords.push_back(passwords[i]);
                }
                if (foundPasswords.size() == 0) {
                    cout << "nie znaleziono zadnego hasla.";
                } else {
                    cout << "znalezione hasła: \n";
                    for (int i = 0; i < foundPasswords.size(); ++i) {
                        foundPasswords[i].print();
                        cout << "\n";
                    }
                }
                break;
            }
            // Wyszukiwanie po kategorii
            case 2:{
                cout << "Podaj kategorie, ktorej szukasz.";
                cin >> text;
                for (int i = 0; i < passwords.size(); ++i) {
                    if (text == passwords[i].getCategory())
                        foundPasswords.push_back(passwords[i]);
                }
                if (foundPasswords.size() == 0) {
                    cout << "nie znaleziono zadnego hasla.";
                } else {
                    cout << "znalezione hasła: \n";
                    for (int i = 0; i < foundPasswords.size(); ++i) {
                        foundPasswords[i].print();
                        cout << "\n";
                    }
                }
                break;
            }
            // Wyszukiwanie po nazwie strony
            case 3:{
                cout << "Podaj nazwe strony, ktorej szukasz.";
                cin >> text;
                for (int i = 0; i < passwords.size(); ++i) {
                    if (text == passwords[i].getWebsite())
                        foundPasswords.push_back(passwords[i]);
                }
                if (foundPasswords.size() == 0) {
                    cout << "nie znaleziono zadnego hasla.";
                } else {
                    cout << "znalezione hasla: \n";
                    for (int i = 0; i < foundPasswords.size(); ++i) {
                        foundPasswords[i].print();
                        cout << "\n";
                    }
                }
                break;
            }
            // Wyszukiwanie po loginie
            case 4:{
                cout << "Podaj login, ktorego szukasz.";
                cin >> text;
                for (int i = 0; i < passwords.size(); ++i) {
                    if (text == passwords[i].getLogin())
                        foundPasswords.push_back(passwords[i]);
                }
                if (foundPasswords.size() == 0) {
                    cout << "nie znaleziono zadnego hasla.";
                } else {
                    cout << "znalezione hasła: \n";
                    for (int i = 0; i < foundPasswords.size(); ++i) {
                        foundPasswords[i].print();
                        cout << "\n";
                    }
                }
                break;
            }
            // Informacja o podaniu zlej liczby
            default:{
                cout << "Podano zly numer";
                break;
            }
        }
    }

    /** @brief Funkcja zapisujaca haslo do pliku txt */
    void savePasswords(){
        string path = "C://Users//barte//CLionProjects//Manager_hasel//pswrds.txt";
        ofstream outfile(path);
        for (auto & password : passwords) {
            outfile << password.getName() << "," << password.getCategory() << "," << password.encrypt(password.getPassword())
                    << "," << password.getLogin() << "," << password.getWebsite() << "\n";
        }
    }

    /** @brief Funkcja wczytująca obiekty klasy Password do wektora */
    std::vector<Password> readPasswordsFromFile() {
        std::vector<Password> passwords;
        std::ifstream file("C://Users//barte//CLionProjects//Manager_hasel//pswrds.txt");
        if(!file){
            std::cout<<"File not opened\n";
            return passwords;
        }
        std::string line;
        while (std::getline(file, line)) {
            // parse the line and create a Password object
            size_t pos = line.find(",");
            std::string name = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(",");
            std::string category = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(",");
            std::string password = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(",");
            std::string login = line.substr(0, pos);
            line.erase(0, pos + 1);

            std::string website = line;

            Password p(name, password, category, website, login);
            p.setPassword(p.decrypt(p.getPassword()));
            passwords.push_back(p);
        }
        file.close();
        return passwords;
    }

    /** @brief funkcja zwracająca aktualną datę i godzinę */
    string currentDateTime() {
        time_t now = time(nullptr);
        tm *ltm = localtime(&now);

        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);

        return buffer ;
    }
};

#endif //MANAGER_HASEL_PASSWORDSTORAGE_H
