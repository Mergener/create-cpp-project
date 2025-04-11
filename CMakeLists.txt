cmake_minimum_required(VERSION 3.24)
project(create_cpp_project)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(TEMPLATES_PATH=\"${CMAKE_SOURCE_DIR}/templates\")

include_directories(${CMAKE_SOURCE_DIR}/ext)

add_executable(create_cpp_project src/main.cpp src/terminal.cpp src/templates.h src/templates.cpp src/strings.cpp)
set_target_properties(create_cpp_project PROPERTIES OUTPUT_NAME "create-cpp-project")
