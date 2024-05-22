cmake_minimum_required(VERSION 3.13)

include(${CMAKE_CURRENT_LIST_DIR}/../pico-sdk/pico_sdk_init.cmake)

project(phat)

pico_sdk_init()

add_executable(phat)

pico_generate_pio_header(phat ${CMAKE_CURRENT_LIST_DIR}/adc/adc.pio)

target_sources(phat PRIVATE ${CMAKE_CURRENT_LIST_DIR}/main.c ${CMAKE_CURRENT_LIST_DIR}/adc/adc.h ${CMAKE_CURRENT_LIST_DIR}/adc/adc.c)

target_link_libraries(phat PRIVATE pico_stdlib hardware_pio hardware_dma hardware_clocks)
pico_add_extra_outputs(phat)

pico_enable_stdio_usb(phat 1)
pico_enable_stdio_uart(phat 0)
