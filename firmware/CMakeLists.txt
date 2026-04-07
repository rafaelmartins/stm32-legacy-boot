# SPDX-FileCopyrightText: 2026 Rafael G. Martins <rafael@rafaelmartins.eng.br>
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.25)

include(FetchContent)

FetchContent_Declare(cmake_cmsis_stm32
    GIT_REPOSITORY https://github.com/rafaelmartins/cmake-cmsis-stm32.git
    GIT_TAG c199670047e5adb373d8a033ece58c34f173ad4b
)
FetchContent_MakeAvailable(
    cmake_cmsis_stm32
)

add_subdirectory(.. legacy-boot)

project(legacy-boot-firmware C ASM)

add_executable(legacy-boot-firmware
    main.c
)

target_link_libraries(legacy-boot-firmware PRIVATE
    stm32-legacy-boot
)

target_compile_options(legacy-boot-firmware PRIVATE
    -Wall
    -Wextra
    -Werror
)

set_property(TARGET legacy-boot-firmware
    PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE
)

cmsis_stm32_target(legacy-boot-firmware
    DEVICE STM32C071xx
    VERSION 20251118033700
    LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32C071K8TX_FLASH.ld
    ADDITIONAL_OUTPUTS BIN MAP IHEX DFU S19
    SHOW_SIZE ON
    STLINK ON
    INSTALL ON
)
