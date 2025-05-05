## About

I've created this project to facilitate the creation of some C++ projects
that I usually want to build.

It allows me to simply run

```
create-cpp-project
```

and select one of my templates to start building something.

## Installation

At the project top level, run

```
cmake -S . -B build
cd build
```

And build the project with the generated build system.
You'll want to add this project to your `PATH` or add an alias
to allow running `create-cpp-project` from anywhere on your machine.

## Usage

### Creating a C++ project from template

Once you've added create-cpp-project to your `PATH`, simply
run `create-cpp-project` from the parent directory you want to create
your project and follow the steps it displays to select project settings
and your desired template.

### Creating a template

Templates are located in the `templates` folder. To create a new template,
create a new folder and add a `cpp-template.json` file to it. The file has the following
structure:

```json
{
  "name": "Your template name",
  "description": "Explain a bit about your template here.",
  "priority": 500,
  "commands": [
    "setup-command-1 arg1 arg2",
    "setup-command-2 arg1 arg2 arg3"
  ]
}
```

All fields but `name` are optional. The `commands` field is an array of sequentially executed 
commands that are run as soon as the template is instantiated at the directory it is being instantiated.
The `priority` field specifies the template priority. Templates with higher priority are ordered higher
when displaying available templates.

After the JSON is created, simply add any files you want to add to your template and they will
be copied whenever you run `create-cpp-project` and selects your new template. Besides copying the files,
`create-cpp-project` will also perform the following substitutions on the instantiated files, both in their
names and their contents:

`ActualProjectName` -> Replaced with the Actual Project Name exactly matching the one defined on project creation

`project-name` -> Replaced with the specified project name in dash-case

`ProjectName` -> Replaced with the specified project name in PascalCase

`projectName` -> Replaced with the specified project name in camelCase

`project_name` -> Replaced with the specified project name in snake_case

`PROJECT_NAME` -> Replaced with the specified project name in SCREAMING_SNAKE_CASE