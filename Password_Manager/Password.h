//
// Created by barte on 02.01.2023.
//

#ifndef MANAGER_HASEL_PASSWORD_H
#define MANAGER_HASEL_PASSWORD_H

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <random>
#include "PasswordCategory.h"


using namespace std;

/**
 *
 *  Klasa przechowująca informacje o hasłach
 *
 * */
class Password {
private:
    string name;
    string password;
    string category;
    string website;
    string login;

public:
    /**
    @brief konstruktor slużący do wczytywania objektów z pliku
    */
    Password(std::string name, std::string password, std::string category, std::string website, std::string login)
            : name(name), password(password), category(category), website(website), login(login) {}


    /**
    @brief konstruktor służący do stworzenia obiektu przez użytkownika
    */
    Password() {
        bool check;
        int choice;
        int choiceWay;

        // podawanie nazwy
        cout << "Podaj nazwe: ";
        cin >> name;

        // podawanie hasla
        cout << "1. Wygeneruj haslo automatycznie.\n"
             << "2. Sam napisze swoje haslo.";
        cin >> choiceWay;

        switch (choiceWay) {
            case 1: {
                password = generatePassword();
                break;
            }
            case 2: {
                cout << "podaj haslo: ";
                // sprawdzenie, czy haslo jest poprawne. w innym wypadku nalezy podac je jeszcze raz.
                do {
                    cin >> password;
                    check = checkPassword(password);
                } while (!check);
            }
        }

        // wybor kategorii
        cout << "do jakiej kategorii chesz przypisac swoje haslo?\n";
        passCat.printCategories();
        cin >> choice;

        // sprawdzenie, czy uzytkownik podal litere
        while (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "BLAD\nNie podano liczby. Sproboj ponownie: ";
            cin >> choice;
        }
        // sprawdzenie, czy uzytkownik podal wlasciwa liczbe
        while (choice < 1 && choice > passCat.cat.size()) {
            cout << "BLAD\nPodaj wlasciwa liczbe: ";
            cin >> choice;
        }
        // przypisanie kategorii
        category = passCat.cat[choice - 1];


        cout << "Czy chcesz podac informacje o stronie internetowej i/lub loginie?\n"
             << "1. Tak\n"
             << "2. Nie\n";

        cin >> choice;
        while (choice != 1 && choice != 2) {
            cout << "podano zly numer. Sproboj ponownie: ";
            cin >> choice;
        }

        switch (choice) {
            case 1: {
                cout << "co chcesz zrobic?\n"
                     << "1. Podaj nazwe strony internetowej.\n"
                     << "2. Podaj login.\n"
                     << "3. Podaj obie informacje\n";
                cin >> choice;

                switch (choice) {
                    case 1:
                        cout << "Podaj nazwe strony: ";
                        cin >> website;
                        break;
                    case 2:
                        cout << "Podaj login: ";
                        cin >> login;
                        break;
                    case 3:
                        cout << "Podaj nazwe strony: ";
                        cin >> website;
                        cout << "Podaj login: ";
                        cin >> login;
                        break;
                    default:
                        cout << "podano zly numer.\n";
                }
                break;
            }
            case 2: {
                cout << "Informacje o stronie i loginie nie zostaly dodane.";
                break;
            }
            default:
                cout << "Podano zla liczbe.";
                break;
        }

        cout << "Pomyslnie dodano informacje o nowym hasle.\n";
    }


    /** @brief Getters and setters
     *
     * */
    string getName() { return name; }

    string getPassword() { return password; }

    string getCategory() { return category; }

    string getWebsite() { return website; }

    string getLogin() { return login; }

    void setName() {
        string newName;
        cout << "Podaj nowa nazwe: ";
        cin >> newName;
        name = newName;
    }

    void setPassword(string s) {
        password = s;
    }

    void setPassword() {
        string newPassword;
        cout << "Podaj nowe haslo: ";
        cin >> newPassword;
        password = newPassword;
    }

    void setCategory() {
        int choice;
        cout << "do jakiej kategorii chesz przypisac swoje haslo?\n";
        passCat.printCategories();
        cin >> choice;
        category = passCat.cat[choice - 1];
    }

    void setWebsite() {
        string newWebsite;
        cout << "Podaj nowa nazwe strony: ";
        cin >> newWebsite;
        website = newWebsite;
    }

    void setLogin() {
        string newLogin;
        cout << "Podaj nowy login: ";
        cin >> newLogin;
        login = newLogin;
    }
    /** @brief funkcja służąca do edycji informacji o haśle */

    void editPasswordInfo() {
        int choice;
        cout << "Co chcesz zmienic?\n"
             << "1. Nazwa\n"
             << "2. kategoria\n"
             << "3. strona\n"
             << "4. login\n"
             << "5. haslo\n";
        cin >> choice;

        switch (choice) {
            case 1:
                setName();
                break;
            case 2:
                setCategory();
                break;
            case 3:
                setWebsite();
                break;
            case 4:
                setLogin();
                break;
            case 5:
                setPassword();
            default:
                cout << "Wybrano zly numer";
                break;
        }
    }

    /** @brief funkcja sprawdzająca, czy liczba jest liczbą pierwszą */
    bool isPrimeNum(int a) {
        if (a % 2 == 0)
            return (a == 2);
        for (int i = 3; i <= sqrt(a); i += 2) {
            if (a % i == 0) {
                return false;
            }
        }
        return true;
    }

    /**  @brief Funkcja szyfrująca hasło. */
    string encrypt(string a) {
        for (int i = 0; i < a.size(); ++i) {
            if (isPrimeNum(i))
                a[i] += 6;
            else
                a[i] -= 6;
        }
        return a;
    }

    /** @brief Funkcja deszyfrująca hasło */
    string decrypt(string a) {
        for (int i = 0; i < a.size(); ++i) {
            if (isPrimeNum(i))
                a[i] -= 6;
            else
                a[i] += 6;
        }
        return a;
    }

    /** @brief Funkcja sprawdzająca, czy hasło spełnia wymagania.(małe i wielkie litery, cyfry, znaki specjalne, conajmniejn 8 znaków)
     *  @param password przyjmuje haslo, ktore zostalo stworzone przez uzytkownika
     * */
    bool checkPassword(string password) {

        bool isLong = true;
        bool hasLower = false;
        bool hasUpper = false;
        bool hasDigit = false;
        bool hasSpecial = false;

        // check length
        if (password.length() < 8)
            isLong = false;

        for (char i: password) {
            // check upper case
            if (isupper(i))
                hasUpper = true;
            // check lower case
            if (islower(i))
                hasLower = true;
            // check digit
            if (isdigit(i))
                hasDigit = true;
            // check special case
            if (!isalnum(i))
                hasSpecial = true;
        }

        if (isLong && hasSpecial && hasLower && hasUpper && hasDigit) {
            cout << "Twoje haslo jest mocne\n";
            return true;
        } else if (!hasUpper) {
            cout << "Brak wielkich liter.\n";
            return false;
        } else if (!hasSpecial) {
            cout << "Brak znakow specjalnych.\n";
            return false;
        } else if (!hasLower) {
            cout << "Brak malych liter.\n";
            return false;
        } else if (!hasDigit) {
            cout << "Brak cyfr.\n";
            return false;
        } else if (!isLong) {
            cout << "Twoje haslo jest za krotkie. Powinno skladac sie z conajmniej 8 znakow\n";
            return false;
        }
    }

    /** @brief funkcja wyświetlająca informacje o haśle */
    void print() {
        cout << "nazwa: " << name
             << "\nkategoria: " << category
             << "\nstrona: " << website
             << "\nlogin: " << login
             << "\nhaslo: " << password;
    }

    /** @brief funkcja generujaca haslo. Przyjmuje od uzytkownika informacje o dlugosci hasla, o zawarciu wielkich liter i znakow specjalnych. */
    string generatePassword() {
        int lenght;
        int choice;
        bool upper = false;
        bool special = false;

        cout << "Podaj dlugosc hasla(ilosc znakow): ";
        cin >> lenght;

        cout << "Czy haslo ma zawierac wielkie litery?\n"
             << "1. Tak\n"
             << "2. Nie\n";
        cin >> choice;
        if (choice == 1)
            upper = true;

        cout << "Czy haslo ma zawierac specjalne znaki?\n"
             << "1. Tak\n"
             << "2. Nie\n";
        cin >> choice;
        if (choice == 1)
            special = true;

        string characters = "abcdefghijklmnopqrstuvwxyz";
        if (upper) characters += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        if (special) characters += "!@#$%^&*()_+-=[]{}\\|;:'\"<>,.?/";

        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<> distribution(0, characters.size() - 1);

        string password;
        for (int i = 0; i < lenght; ++i) {
            password += characters[distribution(generator)];
        }
        return password;
    }
};


#endif //MANAGER_HASEL_PASSWORD_H
