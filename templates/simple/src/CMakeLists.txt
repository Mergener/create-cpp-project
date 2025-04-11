# Set source files here.
set(SOURCES lib.cpp)

# Create library.
add_library(project_name_lib STATIC ${SOURCES})

# Create executable.
add_executable(project_name main.cpp ${SOURCES})
target_link_libraries(project_name PRIVATE project_name_lib)