cmake_minimum_required(VERSION 3.23)
project(ProjektTesty C)

set(CMAKE_C_STANDARD 99)

# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
file(COPY src/data/question_database.csv DESTINATION ${PROJECT_BINARY_DIR})
include_directories(ProjektTesty ${GTK_INCLUDE_DIRS})
link_directories(ProjektTesty ${GTK_LIBRARY_DIRS})
add_executable(ProjektTesty src/presentation/main.c src/presentation/question/question_view.c src/presentation/question/question_view.h src/presentation/entrypoint/entrypoint_view.c src/presentation/entrypoint/entrypoint_view.h src/presentation/score/score_view.c src/presentation/score/score_view.h src/data/question_datasource.c src/data/question_datasource.h src/data/model/question.c src/data/model/question.h src/domain/usecase/get_question_usecase.c src/domain/usecase/get_question_usecase.h src/presentation/app/app.c src/presentation/app/app.h src/presentation/common/window.c src/presentation/common/window.h src/presentation/common/ui_common.h src/presentation/common/buttons.c src/presentation/common/buttons.h)
add_definitions(${GTK_CFLAGS_OTHER})

# Link the target to the GTK+ libraries
target_link_libraries(ProjektTesty ${GTK_LIBRARIES})
