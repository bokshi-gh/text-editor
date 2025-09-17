cmake_minimum_required(VERSION 3.10)
project(Vimm
    VERSION 0.0.1
    DESCRIPTION "A minimal Vim like text editor written in c"
    LANGUAGES C CXX
)
set(CMAKE_C_STANDARD 11)
include_directories(include)
add_executable(vimm src/main.c src/terminal.c src/keypress.c src/editor/editor.c)
install(TARGETS vimm RUNTIME DESTINATION .)

