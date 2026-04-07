/*
 * stm32-legacy-boot: A firmware utility to enable legacy boot via the BOOT0
 * pin on STM32C0 microcontrollers.
 *
 * SPDX-FileCopyrightText: 2026 Rafael G. Martins <rafael@rafaelmartins.eng.br>
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stm32c0xx.h>
#include <legacy-boot.h>


int
main(void)
{
    legacy_boot_enable(true);

    RCC->APBENR2 |= RCC_APBENR2_SYSCFGEN;
    SYSCFG->CFGR1 = SYSCFG_CFGR1_MEM_MODE_0;

    __IO uint32_t bootloader_stack_pointer = *(uint32_t*) 0x1FFF0000UL;
    __IO uint32_t bootloader_address = *(uint32_t*) 0x1FFF0004UL;

    // avoid using __setMSP() and jump to bootloader in C because gcc tends to
    // generate code that stores the bootloader address in the stack pointer
    // instead of a normal register when building with -O3. gcc can't identify
    // that we changed the stack pointer and loads an invalid address when
    // trying to jump to bootloader.
    __ASM volatile (
        "MSR msp, %0\r\n"
        "BLX %1\r\n"
        :: "r" (bootloader_stack_pointer), "r" (bootloader_address)
    );

    while (1)
        __NOP();

    return 0;
}
