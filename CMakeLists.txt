cmake_minimum_required(VERSION 3.25)

project(gbcemu LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(CompilerWarnings)
include(Sanitizers)
include(StaticAnalyzers)

find_package(SDL2 CONFIG REQUIRED)

add_library(gbcemu_warnings INTERFACE)
set_project_warnings(gbcemu_warnings)

add_library(gbcemu_options INTERFACE)
enable_sanitizers(gbcemu_options)

add_executable(gbcemu
    src/main.cpp
    src/cpu/cpu.cpp
    src/memory/bus.cpp
    src/ppu/ppu.cpp
    src/cartridge/cartridge.cpp
)
target_include_directories(gbcemu PRIVATE src)
target_link_libraries(gbcemu
    PRIVATE
        gbcemu_warnings
        gbcemu_options
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        SDL2::SDL2
)

option(GBCEMU_ENABLE_TESTS "Build the test suite" ON)
if(GBCEMU_ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
