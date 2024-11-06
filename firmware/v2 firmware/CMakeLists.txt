cmake_minimum_required(VERSION 3.13)

include(${CMAKE_CURRENT_LIST_DIR}/../pico-sdk/pico_sdk_init.cmake)

project(pio_adc_i2c)

pico_sdk_init()

add_executable(pio_adc_i2c)

pico_generate_pio_header(pio_adc_i2c ${CMAKE_CURRENT_LIST_DIR}/adc/adc.pio)

target_sources(pio_adc_i2c PRIVATE ${CMAKE_CURRENT_LIST_DIR}/main.c ${CMAKE_CURRENT_LIST_DIR}/adc/adc.h ${CMAKE_CURRENT_LIST_DIR}/adc/adc.c ${CMAKE_CURRENT_LIST_DIR}/i2c/i2c.h ${CMAKE_CURRENT_LIST_DIR}/i2c/i2c.c)

target_link_libraries(pio_adc_i2c PRIVATE pico_stdlib hardware_pio hardware_dma hardware_gpio hardware_clocks hardware_i2c)
pico_add_extra_outputs(pio_adc_i2c)

pico_enable_stdio_usb(pio_adc_i2c 1)
pico_enable_stdio_uart(pio_adc_i2c 0)