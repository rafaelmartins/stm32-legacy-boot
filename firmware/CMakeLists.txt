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

include(cmake/git-version-gen.cmake)

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

configure_file(
    cmake/cpack/files/README.txt.in
    cmake/cpack/files/README.txt
    @ONLY
)

install(FILES
    cmake/cpack/files/LICENSE.txt
    "${CMAKE_BINARY_DIR}/cmake/cpack/files/README.txt"
    DESTINATION .
)

set(CPACK_VERBATIM_VARIABLES YES)

set(CPACK_GENERATOR TXZ ZIP)
set(CPACK_PACKAGE_VENDOR "Rafael G. Martins")
set(CPACK_PACKAGE_VERSION "${PACKAGE_VERSION_GIT}")
set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${PACKAGE_VERSION_GIT}")
set(CPACK_PACKAGE_CHECKSUM SHA512)

set(CPACK_SOURCE_GENERATOR TXZ ZIP)
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-source-${PACKAGE_VERSION_GIT}")
set(CPACK_SOURCE_IGNORE_FILES
    \\.git
    \\.gitignore
    \\.github/
    "build.*/"
    "/.*-backups/"
    "/gerber/"
    "-cache$"
    "-cache.lib$"
    "\\.(000|bak|bck|kicad_pcb-bak|lck|tmp|dsn|ses|kicad_sch-bak|kicad_prl)$"
    ".*~$"
)

include(CPack)
