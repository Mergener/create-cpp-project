#include "strings.h"

#include <vector>
#include <sstream>
#include <algorithm>

static std::vector<std::string> split_tokens(const std::string& s) {
    std::vector<std::string> words;
    std::string word;

    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];

        if (i == 0 && std::isdigit(c)) {
            continue;
        }

        if (   !std::isalnum(c)
            && !std::isspace(c)
            && c != '-'
            && c != '_') {
            continue;
        }

        if (c == '-' || c == '_' || std::isspace(c)) {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        }
        else if (std::isupper(c)) {
            if (!word.empty() && !(std::isupper(word.back()) && std::isupper(c))) {
                words.push_back(word);
                word.clear();
            }
            word += static_cast<char>(std::tolower(c));
        }
        else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    return words;
}

std::string capitalize(const std::string& word) {
    if (word.empty()) return "";
    std::string result = word;
    result[0] = std::toupper(result[0]);
    return result;
}

std::string str_replace(std::string str,
                        const std::string& from,
                        const std::string& to) {
    if (from.empty()) {
        return str;
    }
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

std::string to_dash_case(const std::string& s) {
    std::vector<std::string> words = split_tokens(s);
    std::ostringstream oss;
    for (size_t i = 0; i < words.size(); ++i) {
        if (i > 0) oss << "-";
        oss << words[i];
    }
    return oss.str();
}

std::string to_pascal_case(const std::string& s) {
    std::vector<std::string> words = split_tokens(s);
    std::ostringstream oss;
    for (const auto& word : words) {
        oss << capitalize(word);
    }
    return oss.str();
}

std::string to_camel_case(const std::string& s) {
    std::vector<std::string> words = split_tokens(s);
    std::ostringstream oss;
    for (size_t i = 0; i < words.size(); ++i) {
        if (i == 0)
            oss << words[i];
        else
            oss << capitalize(words[i]);
    }
    return oss.str();
}

std::string to_snake_case(const std::string& s) {
    std::vector<std::string> words = split_tokens(s);
    std::ostringstream oss;
    for (size_t i = 0; i < words.size(); ++i) {
        if (i > 0) oss << "_";
        oss << words[i];
    }
    return oss.str();
}

std::string to_screaming_snake_case(const std::string& s) {
    std::vector<std::string> words = split_tokens(s);
    std::ostringstream oss;
    for (size_t i = 0; i < words.size(); ++i) {
        if (i > 0) oss << "_";
        std::string upper_word = words[i];
        std::transform(upper_word.begin(), upper_word.end(), upper_word.begin(), ::toupper);
        oss << upper_word;
    }
    return oss.str();
}

std::string to_case(const std::string& s,
                    Casing casing) {
    switch (casing) {
        case Casing::DashCase:           return to_dash_case(s);
        case Casing::PascalCase:         return to_pascal_case(s);
        case Casing::CamelCase:          return to_camel_case(s);
        case Casing::SnakeCase:          return to_snake_case(s);
        case Casing::ScreamingSnakeCase: return to_screaming_snake_case(s);
        default:                         return s;
    }
}