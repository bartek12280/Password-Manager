//
// Created by barte on 12.01.2023.
//

#ifndef MANAGER_HASEL_PASSWORDCATEGORY_H
#define MANAGER_HASEL_PASSWORDCATEGORY_H

#include <iostream>
#include <vector>

/**
 *
 * @brief Klasa przechowująca informacje na temat kategorii haseł.
 *
 * */
class PasswordCategories {
public:
    std::vector<std::string> cat;

    /** @brief dodaje kategorie */
    void addCategory() {
        std::string categoryName;
        std::cout << "Podaj nazwe kategorii: ";
        std::cin >> categoryName;
        cat.push_back(categoryName);

    }
    /** @brief Wyświetla wszystkie kategorie. */
    void printCategories() {
        for (int i = 0; i < cat.size(); ++i) {
            std::cout << i+1 << "." << cat[i] << "\n";
        }
    }
};
/**
 *  @param Obiekt globalny przechowujący kategorie
 */
extern PasswordCategories passCat;


#endif //MANAGER_HASEL_PASSWORDCATEGORY_H
