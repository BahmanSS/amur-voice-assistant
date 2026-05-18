cmake_minimum_required(VERSION 3.28)
project(app_project LANGUAGES C ASM)

add_executable(app 
    app/main.c
    app/dfplayer_driver.c
    app/rgb_led_type_driver.c
    app/dht11_driver.c
    app/bsp/pinmux.c
    app/bsp/timer_config.c
    app/bsp/usart.c
    app/DFRobot_DF2301Q_driver.c
    app/bsp/riscv-irq.c
    app/bsp/startup.c
)

add_subdirectory(hardware)

target_link_libraries(app
    PRIVATE
        mik32_hal
)

add_custom_command(TARGET app
    POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND ${TOOLCHAIN_PREFIX}objcopy ARGS -O ihex app.elf app.hex
)