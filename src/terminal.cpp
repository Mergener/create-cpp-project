#include "terminal.h"

#include <algorithm>
#include <iostream>
#include <utility>

bool yes_or_no(const std::string& prompt) {
    std::string response;
    while (true) {
        std::cout << prompt << " (y/n): ";
        std::getline(std::cin, response);

        response.erase(std::remove_if(response.begin(), response.end(), ::isspace), response.end());

        std::transform(response.begin(), response.end(), response.begin(), ::tolower);

        if (response == "y" || response == "yes") {
            return true;
        }
        if (response == "n" || response == "no") {
            return false;
        }

        std::cout << "Please enter 'y' or 'n'.\n";
    }
}

int ask_options(const std::string& prompt, const std::vector<std::string>& opts) {
    while (true) {
        std::cout << prompt << "\n";
        for (size_t i = 0; i < opts.size(); ++i) {
            std::cout << "  [" << i + 1 << "] " << opts[i] << "\n";
        }
        std::cout << "Enter number or option name: ";

        std::string input;
        std::getline(std::cin, input);

        input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());

        try {
            size_t index = std::stoul(input);
            if (index >= 1 && index <= opts.size()) {
                return static_cast<int>(index - 1);
            }
        } catch (...) {
            // Ignore, might be a string match.
        }

        auto match = std::find_if(opts.begin(), opts.end(), [&](const std::string& opt) {
            return std::equal(
                opt.begin(), opt.end(),
                input.begin(), input.end(),
                [](char a, char b) {
                    return std::tolower(a) == std::tolower(b);
                });
        });

        if (match != opts.end()) {
            return static_cast<int>(match - opts.begin());
        }

        std::cout << "Invalid option. Please try again.\n";
    }
}

