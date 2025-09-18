cmake_minimum_required(VERSION 3.12)

project(klangstrom-emulator)

if (NOT DEFINED KLST_ENV)
    message(FATAL_ERROR "KLST_ENV is not defined")
endif ()

file(GLOB EMU_SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(klangstrom-emulator ${EMU_SOURCE_FILES})

target_include_directories(klangstrom-emulator PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_compile_definitions(klangstrom-emulator PRIVATE KLST_ENV=${KLST_ENV})
