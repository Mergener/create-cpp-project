#include "terminal.h"
#include "templates.h"

#include <iostream>
#include <filesystem>

int main() {
    namespace fs = std::filesystem;

    // Load file templates.
    std::vector<std::unique_ptr<Template>> templates;
    load_templates_from(templates, TEMPLATES_PATH);

    // Ask for project name and location.
    auto project_name = ask_for<std::string>("Select a project name:");
    std::string where = to_dash_case(project_name);
    if (!yes_or_no(std::string("Use ") + where + " as the project directory?")) {
        where = ask_for<std::string>("Select a project path:");
    }

    // Ask which template they want to use.
    std::vector<std::string> template_options;
    for (const auto& t: templates) {
        template_options.push_back(t->name());
    }
    int template_idx = ask_options("Select a template:", template_options);

    // Generate the project.
    templates[template_idx]->generate(where, project_name);

    return 0;
}
