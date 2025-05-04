# Create library.
add_library(project_name_lib STATIC project_name.cpp project_name.h)

# Create executable.
add_executable(project_name main.cpp)
target_link_libraries(project_name PRIVATE project_name_lib)