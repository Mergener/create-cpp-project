# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# Create library.
add_library(project_name_lib STATIC project_name.cpp project_name.h)
target_link_libraries(project_name_lib PUBLIC SDL3::SDL3)
target_include_directories(project_name_lib PUBLIC ${EXT_DIRECTORY}/sdl/include)

# Create executable.
add_executable(project_name main.cpp)
target_link_libraries(project_name PRIVATE project_name_lib)

add_custom_command(TARGET project_name_lib POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3-shared>
        $<TARGET_FILE_DIR:project_name_lib>
)

add_custom_command(TARGET project_name POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3-shared>
        $<TARGET_FILE_DIR:project_name>
)