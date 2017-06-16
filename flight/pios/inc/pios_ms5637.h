/**
 ******************************************************************************
 * @addtogroup PIOS PIOS Core hardware abstraction layer
 * @{
 * @addtogroup PIOS_MS5637 MS5637 Functions
 * @brief Hardware functions to deal with the altitude pressure sensor
 * @{
 *
 * @file       pios_ms5637.h
 * @author     Librapilot, http://www.librepilot.org Copyright (C) 2017.
 *             The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 * @brief      MS5637 functions header.
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

#ifndef PIOS_MS5637_H
#define PIOS_MS5637_H
#include <pios_sensors.h>
/* BMP085 Addresses */
#define MS5637_I2C_ADDR   0x76
#define MS5637_RESET      0x1E
#define MS5637_CALIB_ADDR 0xA0 /* First sample is factory stuff */
#define MS5637_ADC_READ   0x00
#define MS5637_PRES_ADDR  0x40
#define MS5637_TEMP_ADDR  0x50
#define MS5637_ADC_MSB    0xF6

struct pios_ms5637_cfg {
    uint32_t oversampling;
};

enum pios_ms5637_osr {
    MS5637_OSR_256  = 0,
    MS5637_OSR_512  = 2,
    MS5637_OSR_1024 = 4,
    MS5637_OSR_2048 = 6,
    MS5637_OSR_4096 = 8,
};

/* Public Functions */
extern void PIOS_MS5637_Init(const struct pios_ms5637_cfg *cfg, int32_t i2c_device);

#endif /* PIOS_MS5637_H */

/**
 * @}
 * @}
 */
