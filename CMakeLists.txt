# SPDX-FileCopyrightText: 2026 Rafael G. Martins <rafael@rafaelmartins.eng.br>
# SPDX-License-Identifier: BSD-3-Clause

if(NOT TARGET stm32-legacy-boot)
    add_library(stm32-legacy-boot INTERFACE)

    target_sources(stm32-legacy-boot INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/src/legacy-boot.c
        ${CMAKE_CURRENT_LIST_DIR}/include/legacy-boot.h
    )

    target_include_directories(stm32-legacy-boot INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/include
    )
endif()
