/*
 * stm32-legacy-boot: A library to enable legacy boot via the BOOT0 pin on
 * STM32C0 microcontrollers.
 *
 * SPDX-FileCopyrightText: 2026 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdbool.h>

#if defined(STM32C0) || defined(STM32C0xx)
#include <stm32c0xx.h>
#else
#error "Unsupported STM32 series"
#endif


bool
legacy_boot_enable(bool reset)
{
    RCC->AHBENR |= RCC_AHBENR_FLASHEN;

    if (reset && (RCC->CSR2 & RCC_CSR2_OBLRSTF) == RCC_CSR2_OBLRSTF)
        return false;

    if ((FLASH->OPTR & FLASH_OPTR_nBOOT_SEL) != FLASH_OPTR_nBOOT_SEL)
        return false;

    if ((FLASH->CR & FLASH_CR_LOCK) == FLASH_CR_LOCK) {
        FLASH->KEYR = 0x45670123;
        FLASH->KEYR = 0xcdef89ab;
    }

    if ((FLASH->CR & FLASH_CR_OPTLOCK) == FLASH_CR_OPTLOCK) {
        FLASH->OPTKEYR = 0x08192a3b;
        FLASH->OPTKEYR = 0x4c5d6e7f;
    }

    FLASH->OPTR &= ~FLASH_OPTR_nBOOT_SEL;

    while ((FLASH->SR & FLASH_SR_BSY1) == FLASH_SR_BSY1);
    FLASH->CR |= FLASH_CR_OPTSTRT;
    while ((FLASH->SR & FLASH_SR_BSY1) == FLASH_SR_BSY1);

    if (reset)
        FLASH->CR |= FLASH_CR_OBL_LAUNCH;

    FLASH->CR |= FLASH_CR_LOCK;
    return true;
}
