/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _VARIANT_STONEFLY_M4_
#define _VARIANT_STONEFLY_M4_

// The definitions here needs a SAMD core >=1.6.10
#define ARDUINO_SAMD_VARIANT_COMPLIANCE 10610

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** Frequency of the board main oscillator */
#define VARIANT_MAINOSC (32768ul)

/** Master clock frequency */
#define VARIANT_MCK (F_CPU)

#define VARIANT_GCLK0_FREQ (F_CPU)
#define VARIANT_GCLK1_FREQ (48000000UL)
#define VARIANT_GCLK2_FREQ (100000000UL)

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "WVariant.h"

#ifdef __cplusplus
#include "SERCOM.h"
#include "Uart.h"
#endif // __cplusplus

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

// Number of pins defined in PinDescription array
#define PINS_COUNT (80u)
#define NUM_DIGITAL_PINS (45u)
#define NUM_ANALOG_INPUTS (19u)
#define NUM_ANALOG_OUTPUTS (2u)
#define analogInputToDigitalPin(p) ((p < 10) ? 66 + (p) : (p < 12) ? 64 + (p)-10 \
                                                      : (p == 12)  ? 58          \
                                                      : (p == 13)  ? 19          \
                                                      : (p < 17)   ? 23 + (p)-17 \
                                                                   : -1)

#define digitalPinToPort(P) (&(PORT->Group[g_APinDescription[P].ulPort]))
#define digitalPinToBitMask(P) (1 << g_APinDescription[P].ulPin)
//#define analogInPinToBit(P)        ( )
#define portOutputRegister(port) (&(port->OUT.reg))
#define portInputRegister(port) (&(port->IN.reg))
#define portModeRegister(port) (&(port->DIR.reg))
#define digitalPinHasPWM(P) (g_APinDescription[P].ulPWMChannel != NOT_ON_PWM || g_APinDescription[P].ulTCChannel != NOT_ON_TIMER)

/*
 * digitalPinToTimer(..) is AVR-specific and is not defined for SAMD
 * architecture. If you need to check if a pin supports PWM you must
 * use digitalPinHasPWM(..).
 *
 * https://github.com/arduino/Arduino/issues/1833
 */
// #define digitalPinToTimer(P)

// LEDs
#define PIN_LED_8 (8)    // PC26 User Green
#define PIN_LED_9 (9)    // PC27 User Red
#define PIN_LED_13 (13)  // PC28 User Purple
#define PIN_LED_RXL (45) // PC23
#define PIN_LED_TXL (46) // PC24
#define PIN_LED PIN_LED_13
#define PIN_LED2 PIN_LED_8
#define PIN_LED3 PIN_LED_9
#define PIN_LED4 PIN_LED_RXL
#define PIN_LED5 PIN_LED_TXL
#define LED_BUILTIN PIN_LED_13
#define PIN_LED_PURPLE PIN_LED_13
#define PIN_LED_GREEN PIN_LED_8
#define PIN_LED_RED PIN_LED_9

/*
 * Analog pins
 */
#define PIN_A0 (66)
#define PIN_A1 (PIN_A0 + 1)
#define PIN_A2 (PIN_A0 + 2)
#define PIN_A3 (PIN_A0 + 3)
#define PIN_A4 (PIN_A0 + 4)
#define PIN_A5 (PIN_A0 + 5)
#define PIN_A6 (PIN_A0 + 6)
#define PIN_A7 (PIN_A0 + 7)
#define PIN_A8 (PIN_A0 + 8)
#define PIN_A9 (PIN_A0 + 9)

#define PIN_A10 (64)
#define PIN_A11 (PIN_A10 + 1)

#define PIN_A12 (58)
#define PIN_A13 (19)

#define PIN_A14 (23)
#define PIN_A15 (PIN_A14 + 6)
#define PIN_A16 (PIN_A14 + 7)

#define PIN_DAC0 PIN_A9
#define PIN_DAC1 PIN_A7

    static const uint8_t A0 = PIN_A0;
    static const uint8_t A1 = PIN_A1;
    static const uint8_t A2 = PIN_A2;
    static const uint8_t A3 = PIN_A3;
    static const uint8_t A4 = PIN_A4;
    static const uint8_t A5 = PIN_A5;
    static const uint8_t A6 = PIN_A6;
    static const uint8_t A7 = PIN_A7;

    static const uint8_t A8 = PIN_A8;
    static const uint8_t A9 = PIN_A9;
    static const uint8_t A10 = PIN_A10;
    static const uint8_t A11 = PIN_A11;
    static const uint8_t A12 = PIN_A12;
    static const uint8_t A13 = PIN_A13;
    static const uint8_t A14 = PIN_A14;
    static const uint8_t A15 = PIN_A15;
    static const uint8_t A16 = PIN_A16;

    static const uint8_t DAC0 = PIN_DAC0;
    static const uint8_t DAC1 = PIN_DAC1;

/**
 * Serial interfaces
 *
 * USART – Synchronous and Asynchronous Receiver and Transmitter
 *
 * UART Objects are created in variant.cpp using one of two constructors
 *
 * `Uart(SERCOM *_s, uint8_t _pinRX, uint8_t _pinTX, SercomRXPad _padRX, SercomUartTXPad _padTX);`
 * `Uart(SERCOM *_s, uint8_t _pinRX, uint8_t _pinTX, SercomRXPad _padRX, SercomUartTXPad _padTX, uint8_t _pinRTS, uint8_t _pinCTS);`
 *
 * Rx Pad (`_padRX`) can be any pad (0-3) [CTLA.RXPO]
 *
 * - use one of `SERCOM_RX_PAD_0`, `SERCOM_RX_PAD_1`, `SERCOM_RX_PAD_2`, `SERCOM_RX_PAD_3`
 *
 *
 * TX Pad (`_padTX`) Options on a SAMD21:
 *
 * - `UART_TX_PAD_0` (0x0) - Tx on pad 0, XKC (when available) on pad 1
 * - `UART_TX_PAD_2` (0x1) - Tx on pad 2, XKC (when available) on pad 3
 * - `UART_TX_RTS_CTS_PAD_0_2_3` (0x2) - Tx on Pad 0, RTS on pad 2, CTS on pad 3
 *
 *
 * TX Pad (`_padTX`) Options on a SAMD/E51:
 *
 * @note The defines/enum values are not aligned with the proper values!
 * @see https://github.com/adafruit/ArduinoCore-samd/issues/368
 *
 * - `UART_TX_PAD_0` (0x0) - Tx on pad 0, XKC (when available) on pad 1
 * - `UART_TX_PAD_2` (0x1) - NOT VALID!
 * - `UART_TX_RTS_CTS_PAD_0_2_3` (0x2) - Tx on Pad 0, RTS on pad 2, CTS on pad 3
 * - (0x3) - Tx on Pad 0, XKC (when available) on pad 1, TE on pad 2
 */

// Serial1 (Grove)
#define PIN_SERIAL1_RX (0) // PA17 SERCOM1/PAD[1]
#define PIN_SERIAL1_TX (1) // PA16 SERCOM1/PAD[0]
#define PAD_SERIAL1_TX (UART_TX_PAD_0)
#define PAD_SERIAL1_RX (SERCOM_RX_PAD_1)
#define SERCOM_SERIAL1 sercom1

// Serial2 (Feather Wing Right)
#define PIN_SERIAL2_RX (26) // PA13 SERCOM2/PAD[1]
#define PIN_SERIAL2_TX (27) // PA12 SERCOM2/PAD[0]
#define PAD_SERIAL2_TX (UART_TX_PAD_0)
#define PAD_SERIAL2_RX (SERCOM_RX_PAD_1)
#define SERCOM_SERIAL2 sercom2

// Serial3 (Feather Wing Left)
#define PIN_SERIAL3_RX (36) // PC17 SERCOM6/PAD[1]
#define PIN_SERIAL3_TX (37) // PC16 SERCOM6/PAD[0]
#define PAD_SERIAL3_TX (UART_TX_PAD_0)
#define PAD_SERIAL3_RX (SERCOM_RX_PAD_1)
#define SERCOM_SERIAL3 sercom6

// Serial4 (Bee)
#define SerialBee Serial4
#define PIN_SERIAL4_RX (14) // PB17 SERCOM5/PAD[1]
#define PIN_SERIAL4_TX (15) // PB16 SERCOM5/PAD[0]
#define PAD_SERIAL4_TX (UART_TX_PAD_0)
#define PAD_SERIAL4_RX (SERCOM_RX_PAD_1)
#define SERCOM_SERIAL4 sercom5

/**
 * SPI Interfaces
 *
 * SPI – Serial Peripheral Interface (Host operation)
 *
 * @note SPI interfaces are created in libraries/SPI.cpp of the Adafruit Core based on the defines below
 *
 * Data In (MISO in host operation) can be any pad (0-3) [CTLA.DIPO], but the real available values depend on what is selected as Data Out.
 *
 * - define `PAD_SPI#_RX` as one of:
 *   - `SERCOM_RX_PAD_0`
 *   - `SERCOM_RX_PAD_1`
 *   - `SERCOM_RX_PAD_2`
 *   - `SERCOM_RX_PAD_3`
 *
 *
 * TX Options on a SAMD21: [CTLA.DOPO]
 *
 * - define `PAD_SPI_TX` as one of:
 *   - `SPI_PAD_0_SCK_1` (0x0) - Data Out (MOSI) on pad 0, SCK is on pad 1, Hardware SS is on pad 2 (Only pad 3 left for MISO)
 *   - `SPI_PAD_2_SCK_3` (0x1) - Data Out (MOSI) on pad 2, SCK is on pad 3, Hardware SS is on pad 1 (Only pad 0 left for MISO)
 *   - `SPI_PAD_3_SCK_1` (0x2) - Data Out (MOSI) on Pad 3, SCK is on pad 1, Hardware SS is on pad 2 (Only pad 0 left for MISO)
 *   - `SPI_PAD_0_SCK_3` (0x3) - Data Out (MOSI) on Pad 0, SCK is on pad 3, Hardware SS is on pad 1 (Only pad 2 left for MISO)
 *
 *
 * TX Options on a SAMD/E51: [CTLA.DOPO]
 *
 * - define `PAD_SPI_TX` as one of: *
 *   - `SPI_PAD_0_SCK_1` (0x0) - Data Out (MOSI) on pad 0, SCK is on pad 1, Hardware SS is on pad 2 (Only pad 3 left for MISO)
 *   - `SPI_PAD_3_SCK_1` (0x2) - Data Out (MOSI) on Pad 3, SCK is on pad 1, Hardware SS is on pad 2 (Only pad 0 left for MISO)
 *   - `SPI_PAD_2_SCK_3` (0x1) and `SPI_PAD_0_SCK_3` (0x3) are NOT VALID on the SAMD/E 51!
 *
 * In the Adafruit core, hardware SS (slave select) is used by default.
 * This means that the SS pin must be the specified pad on the SERCOM restricting you to using only the single slave attachted to that SS pin.
 *
 * If you want to use multiple slaves on the same bus, you can disable hardware SPI select.
 * Doing this allows you to use any GPIO pin(s) as the SS pin(s), and requires you to manually set that pin low before communicating with the desired slave.
 * To emulate the functionality of the hardware SS with a manual SS pin, you should drive the SS pin low for a minimum of one baud cycle before transmission begins, and stays low for a minimum of one baud cycle after transmission completes.
 *
 * To disable hardware slave select, you must add the following code (applies to SAMD21 and 51):
 * ```cpp
 * # include "wiring_private.h"  // pinPeripheral() function
 * // Set the CTRLB register
 * SERCOM#->SPI.CTRLB.bit.MSSEN = 0; // Disable MSSEN
 * while( SERCOM#->SPI.SYNCBUSY.bit.CTRLB == 1 );  // not required, the MSSEN bit is not synchronized
 * // Set the pin periperhal of the SS pin to DIO (just in case it had been PIO_SERCOM or PIO_SERCOM_ALT)
 * pinPeripheral( ss_pin_number, PIO_DIGITAL);
 * ```
 */
#define SPI_INTERFACES_COUNT 2

// SD Card SPI
#define PIN_SPI_MOSI (33) // D33 PB12 SPI MOSI SERCOM4/PAD[0]
#define PIN_SPI_SCK (34)  // D34 PB13 SPI SCK SERCOM4/PAD[1]
#define PIN_SPI_MISO (35) // D35 PB14 SPI MISO SERCOM4/PAD[2]
                          // WARNING: This is not a valid configuration for hardware controlled SS [PIO_SERCOM(_ALT)]!
                          // For hardware SS (enabled in Adafruit core by default) MISO must be on pad 3 if MOSI is on pad 0
#define PIN_SPI_SS (29)   // D29 PB11 SPI (SD card/other) CS SERCOM4/PAD[3] [ALT!!]
                          // WARNING: This is not a valid configuration for hardware controlled SS [PIO_SERCOM(_ALT)]!
                          // For hardware SS (enabled in Adafruit core by default) the SS must be on pad 2
#define PERIPH_SPI sercom4
// Set the entire Tx config here
#define PAD_SPI_TX SPI_PAD_0_SCK_1 // Data Out (MOSI) on pad 0, SCK is on pad 1, Hardware SS is on pad 2 (Only pad 3 left for MISO)
// MISO - Rx - Main In, Sub Out (master in, slave out)
#define PAD_SPI_RX SERCOM_RX_PAD_2 // MISO is on pad 2
                                   // WARNING: the wiring of SERCOM4 for SPI is incorrect!!

    static const uint8_t SS = PIN_SPI_SS;
    static const uint8_t MOSI = PIN_SPI_MOSI;
    static const uint8_t MISO = PIN_SPI_MISO;
    static const uint8_t SCK = PIN_SPI_SCK;

// Needed for SD library
#define SDCARD_SPI SPI
#define SDCARD_MISO_PIN PIN_SPI_MISO
#define SDCARD_MOSI_PIN PIN_SPI_MOSI
#define SDCARD_SCK_PIN PIN_SPI_SCK
#define SDCARD_SS_PIN PIN_SPI_SS

// Other pins
#define PIN_ATN (PIN_SPI_SS) // Default Chip Select for SPI (See https://forum.arduino.cc/t/whats-the-purpose-of-the-new-atn-pin/318278)
    static const uint8_t ATN = PIN_ATN;

// Flash SPI
#define PIN_SPI1_MOSI (42) // D42 PA08 SPI MOSI SERCOM0/PAD[0]
#define PIN_SPI1_SCK (43)  // D43 PA09 SPI SCK SERCOM0/PAD[1]
#define PIN_SPI1_SS (20)   // D20 PA10 SPI (Flash) CS SERCOM0/PAD[2]
#define PIN_SPI1_MISO (44) // D44 PA11 SPI MISO SERCOM0/PAD[3]
#define PERIPH_SPI1 sercom0
// MOSI - Tx - Main Out, Sub In (master out, slave in)
// Set both the MOSI pad and the SCK pad here!
#define PAD_SPI1_TX SPI_PAD_0_SCK_1 // (0x0) - Data Out (MOSI) on pad 0, SCK is on pad 1, Hardware SS is on pad 2 (Only pad 3 left for MISO)
// MISO - Rx - Main In, Sub Out (master in, slave out)
#define PAD_SPI1_RX SERCOM_RX_PAD_3

    static const uint8_t SS1 = PIN_SPI1_SS;
    static const uint8_t MOSI1 = PIN_SPI1_MOSI;
    static const uint8_t MISO1 = PIN_SPI1_MISO;
    static const uint8_t SCK1 = PIN_SPI1_SCK;

/**
 * Wire (I2C) Interfaces
 *
 * I2C – Inter-Integrated Circuit (Host operation)
 *
 * @note I2C interfaces are created in libraries/Wire.cpp of the Adafruit Core based on the defines below
 *
 * @warning The SERCOM pads used for SCL and SDA are **not configurable**.
 * SDA must be on pad 0, SCL must be on pad 1!
 * In 4 wire setup, SDA_OUT must be on pad 2 and SCL_OUT must be on pad 3.
 *
 * `WIRE_IT_HANDLER` is used by the SAMD21
 * `WIRE_IT_HANDLER_0` -> `WIRE_IT_HANDLER_3` are used by the SAMD/E51
 *
 */
#define WIRE_INTERFACES_COUNT 1

#define PIN_WIRE_SDA (17) // PA22 SERCOM3/PAD[0]
#define PIN_WIRE_SCL (16) // PA23 SERCOM3/PAD[1]
#define PERIPH_WIRE sercom3
#define WIRE_IT_HANDLER SERCOM3_Handler
#define WIRE_IT_HANDLER_0 SERCOM3_0_Handler
#define WIRE_IT_HANDLER_1 SERCOM3_1_Handler
#define WIRE_IT_HANDLER_2 SERCOM3_2_Handler
#define WIRE_IT_HANDLER_3 SERCOM3_3_Handler

    static const uint8_t SDA = PIN_WIRE_SDA;
    static const uint8_t SCL = PIN_WIRE_SCL;

/**
 * USB
 *
 * @note The USB interface is created in SAMD21_USB.cpp of the Adafruit Core based on the defines below.
 * The SAMD21 file is used by both the SAMD21 and the SAMD51.
 *
 * These defines are required:
 *
 * ```cpp
 * #define PIN_USB_HOST_ENABLE (#) // Pin controlling power (VBUS) on the USB port
 * #define PIN_USB_DM (#)          // USB data minus
 * #define PIN_USB_DP (#)          // USB data plus
 * ```
 */
#define PIN_USB_HOST_ENABLE (79) // Not in use on Stonefly, but must be defined
#define PIN_USB_DM (77)          // PA24
#define PIN_USB_DP (78)          // PA25

/**
 * I2S Interfaces - not used on the Stonefly
 * The Inter-IC Sound Controller provides a bidirectional, synchronous digital audio link
 * with external audio devices.
 */
#define I2S_INTERFACES_COUNT 0

// #define I2S_DEVICE 0
// #define I2S_CLOCK_GENERATOR 3

// #define PIN_I2S_SDO (32)
// #define PIN_I2S_SDI (31)
// #define PIN_I2S_SCK PIN_SERIAL4_TX
// #define PIN_I2S_FS (33)
// #define PIN_I2S_MCK PIN_SERIAL4_RX

/*
 * On-board QSPI Flash - not used on Stonefly first print
 */
#define EXTERNAL_FLASH_DEVICES GD25Q64E
// #define EXTERNAL_FLASH_USE_QSPI

// QSPI Pins
#define PIN_QSPI_SCK (39) // PB10
#define PIN_QSPI_CS (40)  // PB11
#define PIN_QSPI_IO0 (42) // PA08
#define PIN_QSPI_IO1 (43) // PA09
#define PIN_QSPI_IO2 (41) // PA10
#define PIN_QSPI_IO3 (44) // PA11

/*
 * PCC (Parallel Capture Controller) Pins
 */
#define PIN_PCC_DEN1 (27) // PA12 - Used as UART2 Tx - SERCOM2
#define PIN_PCC_DEN2 (26) // PA13 - Used as UART2 Rx - SERCOM2
#define PIN_PCC_CLK (38)  // PA14 - Used as RTC Alert
#define PIN_PCC_XCLK (29) // ??
#define PIN_PCC_D0 (1)    // PA16 - Used as UART1 Tx - SERCOM1
#define PIN_PCC_D1 (0)    // PA17 - Used as UART1 Rx - SERCOM1
#define PIN_PCC_D2 (51)   // PA18
#define PIN_PCC_D3 (52)   // PA19
#define PIN_PCC_D4 (10)   // PA20
#define PIN_PCC_D5 (11)   // PA21
#define PIN_PCC_D6 (17)   // PA22 - Used as I2C SDA - SERCOM3
#define PIN_PCC_D7 (16)   // PA23 - Used as I2C SCL - SERCOM3
#define PIN_PCC_D8 (35)   // PB14 - Used as SPI0 MISO - SERCOM4
#define PIN_PCC_D9 (28)   // PB15 - Used as SD Card Detect
#define PIN_PCC_D10 (60)  // PC12
#define PIN_PCC_D11 (61)  // PC13
#define PIN_PCC_D12 (62)  // PC14
#define PIN_PCC_D13 (63)  // PC15

#if !defined(VARIANT_QSPI_BAUD_DEFAULT)
// TODO: meaningful value for this
#define VARIANT_QSPI_BAUD_DEFAULT 5000000
#endif

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus

/*	=========================
 *	===== SERCOM DEFINITION
 *	=========================
 */
extern SERCOM sercom0;
extern SERCOM sercom1;
extern SERCOM sercom2;
extern SERCOM sercom3;
extern SERCOM sercom4;
extern SERCOM sercom5;
extern SERCOM sercom6;
extern SERCOM sercom7;

extern Uart Serial1;
extern Uart Serial2;
extern Uart Serial3;
extern Uart Serial4;

#endif

// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_USBVIRTUAL Serial
#define SERIAL_PORT_MONITOR Serial
// Serial has no physical pins broken out, so it's not listed as HARDWARE port
#define SERIAL_PORT_HARDWARE Serial1
#define SERIAL_PORT_HARDWARE_OPEN Serial1

#endif /* _VARIANT_STONEFLY_M4_ */
