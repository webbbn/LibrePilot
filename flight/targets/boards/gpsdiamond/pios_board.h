/**
 ******************************************************************************
 *
 * @file       pios_board.h
 * @author     The LibrePilot Team, http://www.openpilot.org Copyright (C) 2017.
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @brief      Defines board hardware for the GPS Diamond platform.
 * @see        The GNU Public License (GPL) Version 3
 *
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef PIOS_BOARD_H
#define PIOS_BOARD_H
// ------------------------
// Timers and Channels Used
// ------------------------
/*
   Timer | Channel 1 | Channel 2 | Channel 3 | Channel 4
   ------+-----------+-----------+-----------+----------
   ------+-----------+-----------+-----------+----------
 */

// ------------------------
// DMA Channels Used
// ------------------------
/* Channel 1  -                                 */
/* Channel 2  -                                 */
/* Channel 3  -                                 */
/* Channel 4  -                                 */
/* Channel 5  -                                 */
/* Channel 6  -                                 */
/* Channel 7  -                                 */
/* Channel 8  -                                 */
/* Channel 9  -                                 */
/* Channel 10 -                                 */
/* Channel 11 -                                 */
/* Channel 12 -                                 */

// ------------------------
// BOOTLOADER_SETTINGS
// ------------------------
#define BOARD_READABLE        true
#define BOARD_WRITABLE        true
#define MAX_DEL_RETRYS        3

// ------------------------
// WATCHDOG_SETTINGS
// ------------------------
#define PIOS_WATCHDOG_TIMEOUT 400
#define PIOS_WDG_REGISTER     RTC_BKP_DR4
#define PIOS_WDG_SYSTEM       0x0001
#define PIOS_WDG_GPS          0x0002
#define PIOS_WDG_MAG          0x0004

// ------------------------
// TELEMETRY
// ------------------------
// #define TELEM_QUEUE_SIZE         20

// ------------------------
// PIOS_LED
// ------------------------
#define PIOS_LED_HEARTBEAT    0

// -------------------------
// System Settings
// -------------------------
#define PIOS_MASTER_CLOCK     48000000
#define PIOS_PERIPHERAL_CLOCK (PIOS_MASTER_CLOCK / 2)

// -------------------------
// Interrupt Priorities
// -------------------------
#define PIOS_IRQ_PRIO_LOW     12              // lower than RTOS
#define PIOS_IRQ_PRIO_MID     8               // higher than RTOS
#define PIOS_IRQ_PRIO_HIGH    5               // for SPI, ADC, I2C etc...
#define PIOS_IRQ_PRIO_HIGHEST 4 // for USART etc...

// ------------------------
// PIOS_I2C
// See also pios_board.c
// ------------------------
#define PIOS_I2C_MAX_DEVS 1
extern uint32_t pios_i2c_gps_id;
#define PIOS_I2C_GPS      (pios_i2c_gps_id)

// -------------------------
// SPI
//
// See also pios_board.c
// -------------------------
#define PIOS_SPI_MAX_DEVS   0

// -------------------------
// PIOS_USART
// -------------------------
#define PIOS_USART_MAX_DEVS 2

// -------------------------
// PIOS_COM
//
// See also pios_board.c
// -------------------------
#define PIOS_COM_MAX_DEVS 2
extern uint32_t pios_com_main_id;
extern uint32_t pios_com_gps_id;
#define PIOS_COM_MAIN     (pios_com_main_id)
#define PIOS_COM_GPS      (pios_com_gps_id)

#if defined(PIOS_INCLUDE_DEBUG_CONSOLE)
#define PIOS_COM_DEBUG    (pios_com_main_id)
#endif /* PIOS_INCLUDE_DEBUG_CONSOLE */

// --------------------------
// Timer controller settings
// --------------------------
#define PIOS_TIM_MAX_DEVS 3

// -------------------------
// GPIO
// -------------------------
#define PIOS_GPIO_PORTS   {}
#define PIOS_GPIO_PINS    {}
#define PIOS_GPIO_CLKS    {}
#define PIOS_GPIO_NUM     0

#define PIOS_USB_ENABLED  0

#endif /* PIOS_BOARD_H */
