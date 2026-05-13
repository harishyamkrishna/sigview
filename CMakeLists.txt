cmake_minimum_required(VERSION 3.20)
project(sigview LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------- Dependencies -------------------------------------------------------
include(FetchContent)

FetchContent_Declare(
    ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
    GIT_TAG        v5.0.0
)
FetchContent_MakeAvailable(ftxui)

# ---------- Library ------------------------------------------------------------
add_library(libsigview STATIC
    src/Histogram.cpp
    src/DatParser.cpp
    src/App.cpp
)

target_include_directories(libsigview PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(libsigview PUBLIC
    ftxui::screen
    ftxui::dom
    ftxui::component
)

# ---------- Executable ---------------------------------------------------------
add_executable(sigview
    src/main.cpp
)

target_link_libraries(sigview PRIVATE
    libsigview
)

# ---------- Compiler warnings --------------------------------------------------
target_compile_options(sigview PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
)
