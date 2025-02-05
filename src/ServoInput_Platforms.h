/*
 *  Project     Servo Input Library
 *  @author     David Madison
 *  @link       github.com/dmadison/ServoInput
 *  @license    LGPLv3 - Copyright (c) 2020 David Madison
 *
 *  This file is part of the Arduino Servo Input Library.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// This file borrows the formating and naming conventions from Paul Stoffregen's
// Encoder library. Thanks Paul!
// https://github.com/PaulStoffregen/Encoder/blob/master/utility/direct_pin_read.h

#ifndef ServoInput_Platforms_h
#define ServoInput_Platforms_h

#include <Arduino.h>

#if defined(__AVR__)

#define IO_REG_TYPE                     uint8_t
#define PIN_TO_BASEREG(pin)             (portInputRegister(digitalPinToPort(pin)))
#define PIN_TO_BITMASK(pin)             (digitalPinToBitMask(pin))
#define DIRECT_PIN_READ(base, mask)     (((*(base)) & (mask)) ? 1 : 0)

#elif defined(ESP8266) || defined(ESP32)

#define IO_REG_TYPE                     uint32_t
#define PIN_TO_BASEREG(pin)             (portInputRegister(digitalPinToPort(pin)))
#define PIN_TO_BITMASK(pin)             (digitalPinToBitMask(pin))
#define DIRECT_PIN_READ(base, mask)     (((*(base)) & (mask)) ? 1 : 0)
#define SERVOINPUT_ISR_FLAG             ICACHE_RAM_ATTR

#elif defined(__SAMD21G18A__)  // Arduino MKR boards, Arm Cortex-M0 SAMD21

#define IO_REG_TYPE                     uint32_t
#define PIN_TO_BASEREG(pin)             (portInputRegister(digitalPinToPort(pin)))
#define PIN_TO_BITMASK(pin)             (digitalPinToBitMask(pin))
#define DIRECT_PIN_READ(base, mask)     (((*(base)) & (mask)) ? 1 : 0)

#elif defined(TEENSYDUINO)

#if defined(__arm__) && defined(KINETISK)  // 32 bit Teensy 3.x
#define IO_REG_TYPE                     uint8_t
#elif defined(__arm__) && defined(KINETISL)  // 32 bit Teensy-LC
#define IO_REG_TYPE                     uint8_t
#elif defined(__arm__) && \
  (defined(__IMXRT1052__) || defined(__IMXRT1062__))  // 32 bit Teensy 4.x
#define IO_REG_TYPE                     uint32_t
#endif

#define PIN_TO_BASEREG(pin)             (portInputRegister(digitalPinToPort(pin)))
#define PIN_TO_BITMASK(pin)             (digitalPinToBitMask(pin))
#define DIRECT_PIN_READ(base, mask)     (((*(base)) & (mask)) ? 1 : 0)

#else
#error "The ServoInput library does not support this board (platform). Please create a feature request here: https://github.com/dmadison/ServoInput/"
#endif

#ifndef SERVOINPUT_ISR_FLAG
#define SERVOINPUT_ISR_FLAG
#endif


#endif
