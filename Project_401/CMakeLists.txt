cmake_minimum_required(VERSION 3.10)

project(Project401)

# Include the src directory
add_subdirectory(src)

# Add the executable with the list of source files and header files
add_executable(Project401 src/hello_world.c)

target_link_libraries(Project401 PUBLIC think_of_better_name)
