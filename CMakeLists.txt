cmake_minimum_required(VERSION 4.1.2)
project(Vim--
    VERSION 1.0
    DESCRIPTION ""
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_executable(vim-- src/main.c src/terminal.c src/editor.c)

install(TARGETS vim-- RUNTIME DESTINATION bin)
install(FILES LICENSE README.md DESTINATION docs)
