/**
 ******************************************************************************
 * @file       board_hw_defs.c
 * @author     Libreilot, http://www.openpilot.org Copyright (C) 2017.
 *             The OpenPilot Team, http://www.openpilot.org Copyright (C) 2014.
 * @addtogroup LibrePilotSystem LibrePilot System
 * @{
 * @addtogroup LibrePilotCore LibrePilot Core
 * @{
 * @brief Defines board specific static initializers for hardware for the GPS board.
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

#define BOARD_REVISION_GPSDIA 1
/*
 * GPS Diamond GPS + MAG + BARO board.
 * pins allocation:
 * port         |  Pins
 * -------------|-------------
 * SENSOR I2C   | PB6 I2C1_SCL
 *              | PB7 I2C1_SCK
 *              | PA0 INT1
 *              | PA1 INT2
 * ---------------------------
 * Led          | PA5
 * ---------------------------
 * Main Port    | PA9  TX
 *              | PA10 RX
 *----------------------------
 * GPS UART     | PA2 TX
 *              | PA3 RX
 *----------------------------
 */

/**
 * LED Configuration
 **/

#if defined(PIOS_INCLUDE_LED)

#include <pios_led_priv.h>

static const struct pios_gpio pios_leds_gpsp[] = {
    // PA5
    [PIOS_LED_HEARTBEAT] = {
        .pin                =             {
            .gpio = GPIOA,
            .init =             {
                .GPIO_Pin   = GPIO_Pin_5,
                .GPIO_Mode  = GPIO_Mode_OUT,
                .GPIO_OType = GPIO_OType_PP,
                .GPIO_Speed = GPIO_Speed_Level_1,
            },
        },
        .active_low         = false
    },
};

static const struct pios_gpio_cfg pios_led_cfg_gpsp = {
    .gpios     = pios_leds_gpsp,
    .num_gpios = NELEMENTS(pios_leds_gpsp),
};

const struct pios_gpio_cfg *PIOS_BOARD_HW_DEFS_GetLedCfg(__attribute__((unused)) uint32_t board_revision)
{
    return &pios_led_cfg_gpsp;
}

#endif /* PIOS_INCLUDE_LED */


/**
 * UART Configuration
 **/

#if defined(PIOS_INCLUDE_USART)

#include "pios_usart_priv.h"

static const struct pios_usart_cfg pios_usart_generic_main_cfg = {
    .regs  = USART1,
    .remap = GPIO_AF_1,
    .rx    = {
        .gpio = GPIOA,
        .init = {
            .GPIO_Pin   = GPIO_Pin_10,
            .GPIO_Speed = GPIO_Speed_2MHz,
            .GPIO_OType = GPIO_OType_OD,
            .GPIO_Mode  = GPIO_Mode_AF,
        },
    },
    .tx                 = {
        .gpio = GPIOA,
        .init = {
            .GPIO_Pin   = GPIO_Pin_9,
            .GPIO_Speed = GPIO_Speed_2MHz,
            .GPIO_OType = GPIO_OType_PP,
            .GPIO_Mode  = GPIO_Mode_AF,
        },
    },
};

static const struct pios_usart_cfg pios_usart_gps_cfg = {
    .regs  = USART2,
    .remap = GPIO_AF_1,
    .rx    = {
        .gpio = GPIOA,
        .init = {
            .GPIO_Pin   = GPIO_Pin_3,
            .GPIO_Speed = GPIO_Speed_2MHz,
            .GPIO_OType = GPIO_OType_OD,
            .GPIO_Mode  = GPIO_Mode_AF,
        },
    },
    .tx                 = {
        .gpio = GPIOA,
        .init = {
            .GPIO_Pin   = GPIO_Pin_2,
            .GPIO_Speed = GPIO_Speed_2MHz,
            .GPIO_OType = GPIO_OType_PP,
            .GPIO_Mode  = GPIO_Mode_AF,
        },
    },
};

#endif /* PIOS_INCLUDE_USART */


/**
 * COM Configuration
 **/

#if defined(PIOS_INCLUDE_COM)

#include "pios_com_priv.h"

#endif /* PIOS_INCLUDE_COM */


/**
 * RTC Configuration
 **/

#if defined(PIOS_INCLUDE_RTC)
/*
 * Realtime Clock (RTC)
 */
#include <pios_rtc_priv.h>

void PIOS_RTC_IRQ_Handler(void);
void RTC_IRQHandler() __attribute__((alias("PIOS_RTC_IRQ_Handler")));
static const struct pios_rtc_cfg pios_rtc_main_cfg = {
    .clksrc    = RCC_RTCCLKSource_LSI,
    .prescaler = 100,
    .irq                             = {
        .init                        = {
            .NVIC_IRQChannel    = RTC_IRQn,
            .NVIC_IRQChannelPriority = PIOS_IRQ_PRIO_MID,
            .NVIC_IRQChannelCmd = ENABLE,
        },
    },
};

void PIOS_RTC_IRQ_Handler(void)
{
    PIOS_RTC_irq_handler();
}

#endif /* if defined(PIOS_INCLUDE_RTC) */


/**
 * I2C interface.
 **/

#if defined(PIOS_INCLUDE_I2C)

#include <pios_i2c_priv.h>

/*
 * I2C Adapters
 */
void PIOS_I2C_sensors_irq_handler(void);
void I2C1_IRQHandler() __attribute__((alias("PIOS_I2C_sensors_irq_handler")));

static const struct pios_i2c_adapter_cfg pios_i2c_sensors_cfg = {
    .remapSDA = GPIO_AF_1,
    .remapSCL = GPIO_AF_1,
    .regs     = I2C1,
    .init     = {
        .I2C_Mode                    = I2C_Mode_I2C,
        .I2C_AnalogFilter  = I2C_AnalogFilter_Enable,
        .I2C_DigitalFilter = 0x00,
        .I2C_OwnAddress1   = 0x00,
        .I2C_Ack    = I2C_Ack_Enable,
        .I2C_AcknowledgedAddress     = I2C_AcknowledgedAddress_7bit,
        .I2C_Timing = (uint32_t)0x00210507,
    },
    .transfer_timeout_ms             = 50,
    .scl                             = {
        .gpio = GPIOB,
        .init = {
            .GPIO_Pin   = GPIO_Pin_6,
            .GPIO_Speed = GPIO_Speed_2MHz,
            .GPIO_OType = GPIO_OType_OD,
            .GPIO_PuPd  = GPIO_PuPd_NOPULL,
            .GPIO_Mode  = GPIO_Mode_AF,
        },
        .pin_source                  = GPIO_PinSource6,
    },
    .sda                             = {
        .gpio = GPIOB,
        .init = {
            .GPIO_Pin   = GPIO_Pin_7,
            .GPIO_Speed = GPIO_Speed_2MHz,
            .GPIO_OType = GPIO_OType_OD,
            .GPIO_PuPd  = GPIO_PuPd_NOPULL,
            .GPIO_Mode  = GPIO_Mode_AF,
        },
        .pin_source                  = GPIO_PinSource7,
    },
    .event                           = {
        .flags = 0,
        .init  = {
            .NVIC_IRQChannel    = I2C1_IRQn,
            .NVIC_IRQChannelPriority = PIOS_IRQ_PRIO_HIGH,
            .NVIC_IRQChannelCmd = ENABLE,
        },
    },
    .error                           = {
        .flags = 0,
        .init  = {
            .NVIC_IRQChannel    = I2C1_IRQn,
            .NVIC_IRQChannelPriority = PIOS_IRQ_PRIO_HIGH,
            .NVIC_IRQChannelCmd = ENABLE,
        },
    },
};

uint32_t pios_i2c_sensors_id;
void PIOS_I2C_sensors_irq_handler(void)
{
    /* Call into the generic code to handle the IRQ for this specific device */
    PIOS_I2C_IRQ_Handler(pios_i2c_sensors_id);
}

/**
 * Configuration for the MS5637 chip
 */
#if defined(PIOS_INCLUDE_MS5637)
#include "pios_ms5637.h"
static const struct pios_ms5637_cfg pios_ms5637_cfg = {
    .oversampling = MS5637_OSR_4096,
};
const struct pios_ms5637_cfg *PIOS_BOARD_HW_DEFS_GetMS5637Cfg(__attribute__((unused)) uint32_t board_revision)
{
    return &pios_ms5637_cfg;
}
#endif /* PIOS_INCLUDE_MS5637 */

/**
 * Configuration for the MS5611 chip
 */
#if defined(PIOS_INCLUDE_MS5611)
#include "pios_ms5611.h"
static const struct pios_ms5611_cfg pios_ms5611_cfg = {
    .oversampling = MS5611_OSR_4096,
};
const struct pios_ms5611_cfg *PIOS_BOARD_HW_DEFS_GetMS5611Cfg(__attribute__((unused)) uint32_t board_revision)
{
    return &pios_ms5611_cfg;
}
#endif /* PIOS_INCLUDE_MS5611 */

#endif /* PIOS_INCLUDE_I2C */


/**
 * COM message interface.
 **/

#if defined(PIOS_INCLUDE_COM_MSG)

#include <pios_com_msg_priv.h>

#endif /* PIOS_INCLUDE_COM_MSG */
