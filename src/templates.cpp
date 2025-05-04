#include "templates.h"

#include <fstream>
#include <iostream>
#include <array>
#include <cstdlib>

#include "strings.h"

namespace fs = std::filesystem;

std::string read_entire_file(const fs::path& path) {
    std::ifstream stream(path);
    stream.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    std::string str((std::istreambuf_iterator<char>(stream)),
                    std::istreambuf_iterator<char>());
    return str;
}

void write_entire_file(const fs::path& path,
                       const std::string& content) {
    std::ofstream stream(path);
    stream.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    stream.write(content.data(), static_cast<std::streamsize>(content.size()));
}

void load_templates_from(std::vector<std::unique_ptr<Template>>& templates,
                         const fs::path& path) {
    for (const auto& entry: fs::directory_iterator(path)) {
        if (!entry.is_directory()) {
            continue;
        }

        auto template_file_path = entry.path() / TEMPLATE_FILE_NAME;
        if (   !entry.is_directory()
            || !fs::exists(template_file_path)) {
            continue;
        }

        auto template_ptr = std::make_unique<Template>(entry.path());
        templates.push_back(std::move(template_ptr));
    }
}

static std::string apply_substitutions(std::string str,
                                       const std::string& project_name) {
    static const std::array<std::pair<Casing, const char*>, N_CASINGS> REPLACEMENTS = {
        std::pair { Casing::Default, "ActualProjectName" },
        std::pair { Casing::DashCase, "project-name" },
        std::pair { Casing::PascalCase, "ProjectName" },
        std::pair { Casing::CamelCase, "projectName" },
        std::pair { Casing::SnakeCase, "project_name" },
        std::pair { Casing::ScreamingSnakeCase, "PROJECT_NAME" },
    };

    for (const auto& [casing, base_name]: REPLACEMENTS) {
        str = str_replace(str, base_name, to_case(project_name, casing));
    }

    return str;
}

void Template::generate(const fs::path& where,
                        const std::string& project_name) const {
    for (const auto& entry: fs::recursive_directory_iterator(path())) {
        fs::path src_directory = entry.path().parent_path();
        fs::path dest_directory = where.relative_path() / fs::relative(src_directory, path());

        if (entry.is_regular_file()) {
            fs::path file_name = entry.path().filename();
            fs::path dest_file_name = apply_substitutions(file_name.string(), project_name);
            fs::create_directories(dest_directory);

            fs::path src_file_path = src_directory / file_name;
            if (fs::absolute(src_file_path) == fs::absolute(path() / TEMPLATE_FILE_NAME)) {
                // Don't copy the template file.
                continue;
            }

            fs::path dest_file_path = dest_directory / dest_file_name;

            std::string content = read_entire_file(src_file_path);
            content = apply_substitutions(content, project_name);
            write_entire_file(dest_file_path, content);
        }
        else {
            fs::create_directories(dest_directory);
        }
    }

    fs::current_path(where);
    for (const auto& cmd: m_info.commands) {
        std::string processed_cmd = apply_substitutions(cmd, project_name);
        std::system(processed_cmd.c_str());
    }
}

Template::Template(const fs::path& template_directory) {
    auto template_file_path = template_directory / TEMPLATE_FILE_NAME;
    std::string json_str = read_entire_file(template_file_path);
    m_info = nlohmann::json::parse(json_str);
    m_path = template_directory;
}

const std::string& Template::name() const {
    return m_info.name;
}

const std::string& Template::description() const {
    return m_info.description;
}

const fs::path& Template::path() const {
    return m_path;
}