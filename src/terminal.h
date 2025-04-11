#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

/**
 * Asks a Y/N question.
 */
bool yes_or_no(const std::string& prompt);

template <typename T>
T ask_for();

int ask_options(const std::string& prompt, const std::vector<std::string>& options);

//
// Template implementations
//

template <typename T>
T ask_for(const std::string& prompt) {
    T value;
    while (true) {
        std::cout << prompt << ' ';

        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Invalid input. Please try again.\n";
    }
}

#endif //TERMINAL_H
