cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
# include_directories("/usr/include")

project(weight-measurer C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

pico_sdk_init()
add_executable(weight-measurer
    main.c
)
add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )

pico_enable_stdio_usb(weight-measurer 1)
pico_enable_stdio_uart(weight-measurer 0)

target_link_libraries(weight-measurer pico_stdlib hardware_adc)

pico_add_extra_outputs(weight-measurer)
