cmake_minimum_required(VERSION 3.23)
project(ProjektTesty C)

set(CMAKE_C_STANDARD 99)

# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(ProjektTesty ${GTK_INCLUDE_DIRS})
link_directories(ProjektTesty ${GTK_LIBRARY_DIRS})
add_executable(ProjektTesty src/main.c)
add_definitions(${GTK_CFLAGS_OTHER})

# Link the target to the GTK+ libraries
target_link_libraries(ProjektTesty ${GTK_LIBRARIES})
