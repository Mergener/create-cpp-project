#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <vector>
#include <string>
#include <filesystem>
#include <memory>
#include <nlohmann/json.h>
#include <array>

#include "strings.h"

static constexpr const char* TEMPLATE_FILE_NAME = "cpp-template.json";

struct TemplateInfo {
    std::string name;
    std::string description;
    std::vector<std::string> commands;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TemplateInfo, name, description, commands);

class Template {
public:
    [[nodiscard]] const std::string& name() const;
    [[nodiscard]] const std::string& description() const;
    [[nodiscard]] const std::filesystem::path& path() const;

    void generate(const std::filesystem::path& where,
                  const std::string& project_name) const;

    explicit Template(const std::filesystem::path& template_directory);

private:
    std::filesystem::path m_path;
    TemplateInfo m_info;
};

void load_templates_from(std::vector<std::unique_ptr<Template>>& templates,
                         const std::filesystem::path& path);

#endif // TEMPLATES_H
