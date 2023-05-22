#include <iostream>
#include "PasswordStorage.h"



using namespace std;

int main() {
    passCat.cat.emplace_back("Prywatne");
    passCat.cat.emplace_back("Gry");

    PasswordStorage passwordStorage;

    int choice = 0;
    while(choice != 8){
        cout << "________________\nPASSWORD MANAGER\n"
             << "________________\n";

        cout << "1. Wyszukaj haslo\n";
        cout << "2. Posortuj hasla\n";
        cout << "3. Dodaj haslo\n";
        cout << "4. Edytuj haslo\n";
        cout << "5. usun haslo\n";
        cout << "6. Dodaj kategorie\n";
        cout << "7. usun kategorie\n";
        cout << "8. Wyjscie z programu\n";

        cin >> choice;


        switch (choice) {
            case 1: {
                passwordStorage.findPasswords();
                break;
            }
            case 2: {
                cout << "sortowanie hasel\n";
                break;
            }
            case 3: {
                passwordStorage.addPassword();
                break;
            }
            case 4: {
                passwordStorage.editPassword();
                break;
            }
            case 5: {
                passwordStorage.deletePassword();
                break;
            }
            case 6: {
                passCat.addCategory();
                break;
            }
            case 7: {
                passwordStorage.deleteCategory();
                break;
            }
            case 8: {
                passwordStorage.savePasswords();
                cout << "Hasla zostaly zapisane.";
                break;
            }
            default: {
                cout << "Wybano zly numer\n";
            }
        }
    }
}
