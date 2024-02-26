set(target think_of_better_name)

set(SOURCES other_file.c)
set(HEADERS other_file.h)

add_library(${target} ${SOURCES} ${HEADERS})
# Specify include directories if needed
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
