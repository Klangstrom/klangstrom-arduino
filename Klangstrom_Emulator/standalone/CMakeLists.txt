cmake_minimum_required(VERSION 3.15)

project(klangstrom-emulator-standalone)

set(UMFELD_ARDUINO_PATH "/Users/dennisppaul/Documents/dev/umfeld/git/umfeld-arduino/umfeld")
set(KLST_EMU_UMFELD_PATH "${UMFELD_ARDUINO_PATH}/cores/sdl/umfeld")
set(KLST_EMU_VARIANT_PATH "${UMFELD_ARDUINO_PATH}/variants/KLST_EMU")
set(KLST_ENV 0x46)

message(STATUS "----------------------------------------")
message(STATUS "Klangstrom Emulator Standalone")
message(STATUS "----------------------------------------")
message(STATUS "UMFELD_ARDUINO_PATH  : ${UMFELD_ARDUINO_PATH}")
message(STATUS "KLST_EMU_UMFELD_PATH : ${KLST_EMU_UMFELD_PATH}")
message(STATUS "KLST_EMU_VARIANT_PATH: ${KLST_EMU_VARIANT_PATH}")
message(STATUS "KLST_ENV             : ${KLST_ENV}")
message(STATUS "----------------------------------------")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCE_FILES
        "src/*.c"
        "src/*.cpp"
)
file(GLOB KLST_EMU_VARIANT_SOURCES
        "${KLST_EMU_VARIANT_PATH}/*.c"
        "${KLST_EMU_VARIANT_PATH}/*.cpp"
)
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${KLST_EMU_VARIANT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "${KLST_EMU_VARIANT_PATH}")
target_include_directories(${PROJECT_NAME} PRIVATE "${KLST_EMU_UMFELD_PATH}/..")
target_include_directories(${PROJECT_NAME} PRIVATE "src/.")

# set definitions

target_compile_definitions(${PROJECT_NAME} PUBLIC
        UMFELD_SET_DEFAULT_CALLBACK=0
        BOARD_NAME_KLST_EMU
        KLST_ENV=${KLST_ENV}
        VARIANT_H="variant_KLST_Emulator.h"
        KLST_EMU_AUDIO_BLOCK=2048
)

# add umfeld

add_subdirectory("${KLST_EMU_UMFELD_PATH}" ${CMAKE_BINARY_DIR}/umfeld-lib-${PROJECT_NAME})
add_umfeld_libs()
target_link_libraries(${PROJECT_NAME} PRIVATE umfeld-lib-interface umfeld-lib)
target_compile_definitions(umfeld-lib PRIVATE
        UMFELD_SET_DEFAULT_CALLBACK=0
)

# add Klangstrom_Emulator

add_subdirectory(".." ${CMAKE_BINARY_DIR}/klangstrom-emulator-lib-${PROJECT_NAME})
target_compile_definitions(klangstrom-emulator PRIVATE
        KLST_ENV=${KLST_ENV}
        VARIANT_H="variant_KLST_Emulator.h"
        KLST_EMU_AUDIO_BLOCK=2048
)
target_include_directories(klangstrom-emulator PRIVATE "${KLST_EMU_UMFELD_PATH}/..")
target_include_directories(klangstrom-emulator PRIVATE "${KLST_EMU_VARIANT_PATH}")
target_link_libraries(klangstrom-emulator PRIVATE umfeld-lib-interface umfeld-lib)
target_link_libraries(${PROJECT_NAME} PRIVATE klangstrom-emulator)
