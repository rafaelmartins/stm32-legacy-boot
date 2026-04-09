# SPDX-FileCopyrightText: 2026 Rafael G. Martins <rafael@rafaelmartins.eng.br>
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.25)

include(FetchContent)

FetchContent_Declare(cmake_cmsis_stm32
    GIT_REPOSITORY https://github.com/rafaelmartins/cmake-cmsis-stm32.git
    GIT_TAG c199670047e5adb373d8a033ece58c34f173ad4b
)
FetchContent_Declare(cmake_stm32_firmware_release
    GIT_REPOSITORY https://github.com/rafaelmartins/cmake-stm32-firmware-release.git
    GIT_TAG 983970487fad111d48e7b7dca9e0e840e055705a
)
FetchContent_MakeAvailable(
    cmake_cmsis_stm32
    cmake_stm32_firmware_release
)

add_subdirectory(.. legacy-boot)

project(stm32-legacy-boot-firmware
    VERSION "${PACKAGE_VERSION_CANONICAL}"
    HOMEPAGE_URL "https://rafaelmartins.com/p/stm32-legacy-boot/"
    LANGUAGES C ASM
)

add_executable(stm32-legacy-boot-firmware
    main.c
)

target_link_libraries(stm32-legacy-boot-firmware PRIVATE
    stm32-legacy-boot
)

target_compile_options(stm32-legacy-boot-firmware PRIVATE
    -Wall
    -Wextra
    -Werror
)

set_property(TARGET stm32-legacy-boot-firmware
    PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE
)

cmsis_stm32_target(stm32-legacy-boot-firmware
    DEVICE STM32C071xx
    VERSION 20251118033700
    LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32C071K8TX_FLASH.ld
    ADDITIONAL_OUTPUTS BIN MAP IHEX DFU S19
    SHOW_SIZE ON
    STLINK ON
    INSTALL ON
)

cpack_configure()
