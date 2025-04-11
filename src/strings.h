#ifndef STRINGS_H
#define STRINGS_H

#include <string>

std::string str_replace(std::string str,
                        const std::string& from,
                        const std::string& to);

enum class Casing {
    Default,
    DashCase,
    PascalCase,
    CamelCase,
    SnakeCase,
    ScreamingSnakeCase,
};
static constexpr size_t N_CASINGS = 6;

std::string to_case(const std::string& s,
                    Casing casing);

/** dash-case-string */
std::string to_dash_case(const std::string& s);

/** PascalCaseString */
std::string to_pascal_case(const std::string& s);

/** camelCaseString */
std::string to_camel_case(const std::string& s);

/** snake_case_string */
std::string to_snake_case(const std::string& s);

/** SCREAMING_SNAKE_CASE_STRING */
std::string to_screaming_snake_case(const std::string& s);

#endif // STRINGS_H
