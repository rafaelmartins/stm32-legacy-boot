/*
 * stm32-legacy-boot: A library to enable legacy boot via the BOOT0 pin on
 * STM32C0 microcontrollers.
 *
 * SPDX-FileCopyrightText: 2026 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file legacy-boot.h
 * @brief Public functions implemented by the @c stm32-legacy-boot library.
 *
 * Some recent STM32 series are designed to make most pins available as GPIO, and
 * because of that, the @c BOOT0 pin is configured as a regular GPIO by default.
 * This library reconfigures the microcontroller to enable entering the bootloader
 * via the @c BOOT0 pin, when that is suitable for the application. An unprogrammed
 * microcontroller will still boot into the bootloader, allowing a firmware that uses
 * this library to be flashed. Once running, it will configure the @c BOOT0 pin for
 * any subsequent updates.
 *
 * This version of the library only supports @c STM32C07x, which are the only
 * devices from the @c STM32C0 series with USB peripherals.
 */

#pragma once

#include <stdbool.h>

/**
 * @brief Enable legacy boot.
 *
 * Enables legacy boot, if needed, by setting the @c nBOOT_SEL option bit to @c 0.
 *
 * This function must be called during firmware initialization.
 *
 * @param[in] reset Reset the system after enabling legacy boot to reload registers.
 * @returns A boolean indicating whether any change was applied to the option bytes sector.
 *
 * If @c reset is @c true, the function won't return, as there will be an immediate reset.
 */
bool legacy_boot_enable(bool reset);
