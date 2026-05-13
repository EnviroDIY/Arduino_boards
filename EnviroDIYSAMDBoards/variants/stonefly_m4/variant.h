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

/** Frequency of the board main oscillator, typically 32768 Hz */
#define VARIANT_MAINOSC (32768ul)

/** Master clock frequency */
#define VARIANT_MCK (F_CPU)

/** Generic clock frequencies (SAMD51 only, remove for SAMD21)*/
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
 *        Version Information
 *----------------------------------------------------------------------------*/

/** Major version number (X.x.x) */
#define STONEFLY_VERSION_MAJOR 0
/** Minor version number (x.X.x) */
#define STONEFLY_VERSION_MINOR 3
/** Patch version number (x.x.X) */
#define STONEFLY_VERSION_PATCH 7

/**
 * Macro to convert version number into an integer
 *
 * To be used in comparisons, such as STONEFLY_VERSION >= STONEFLY_VERSION_VAL(4, 0, 0)
 */
#define STONEFLY_VERSION_VAL(major, minor, patch) ((major << 16) | (minor << 8) | (patch))

/**
 * Current Board version, as an integer
 *
 * To be used in comparisons, such as STONEFLY_VERSION >= STONEFLY_VERSION_VAL(4, 0, 0)
 */
#define STONEFLY_VERSION STONEFLY_VERSION_VAL(STONEFLY_VERSION_MAJOR, \
                                              STONEFLY_VERSION_MINOR, \
                                              STONEFLY_VERSION_PATCH)

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

// Number of pins defined in PinDescription array
#define PINS_COUNT (81u)
#define NUM_DIGITAL_PINS (45u)
#define NUM_ANALOG_INPUTS (19u)
#define NUM_ANALOG_OUTPUTS (2u)
// Mapping from analog pin number to digital pin number
// This can be a function if pin numbers are contiguous or it can specify the mapping for each pin explicitly.
#define analogInputToDigitalPin(p) ((p < 10)    ? 66 + (p) \
                                    : (p == 10) ? 4        \
                                    : (p == 11) ? 19       \
                                    : (p == 12) ? 20       \
                                    : (p == 13) ? 23       \
                                    : (p == 14) ? 24       \
                                    : (p == 15) ? 25       \
                                    : (p == 16) ? 26       \
                                    : (p == 17) ? 21       \
                                    : (p == 18) ? 17       \
                                                : -1)

// These macros are used to map digital pin numbers to their corresponding port registers and bit masks for the SAMD architecture.
// You should not need to change these macros, as they are designed to work with the g_APinDescription array defined in the variant's pins_arduino.c file.
#define digitalPinToPort(P) (&(PORT->Group[g_APinDescription[P].ulPort]))
#define digitalPinToBitMask(P) (1 << g_APinDescription[P].ulPin)
// #define analogInPinToBit(P)        ( )
#define portOutputRegister(port) (&(port->OUT.reg))
#define portInputRegister(port) (&(port->IN.reg))
#define portModeRegister(port) (&(port->DIR.reg))
#define digitalPinHasPWM(P) (g_APinDescription[P].ulPWMChannel != NOT_ON_PWM || g_APinDescription[P].ulTCChannel != NOT_ON_TIMER)

/**
 * digitalPinToTimer(..) is AVR-specific and is not defined for SAMD
 * architecture. If you need to check if a pin supports PWM you must
 * use digitalPinHasPWM(..).
 *
 * https://github.com/arduino/Arduino/issues/1833
 */
// #define digitalPinToTimer(P)

// LEDs
// Optional macros for user LEDs.
#define PIN_LED_8 (8)    // PC26 User Green
#define PIN_LED_9 (9)    // PC27 User Red
#define PIN_LED_13 (13)  // PC28 User Purple
#define PIN_LED_RXL (45) // PB23
#define PIN_LED_TXL (46) // PB24
#define PIN_LED PIN_LED_13
#define PIN_LED2 PIN_LED_8
#define PIN_LED3 PIN_LED_9
#define PIN_LED4 PIN_LED_RXL
#define PIN_LED5 PIN_LED_TXL
#define LED_BUILTIN PIN_LED_13
#define PIN_LED_ORANGE PIN_LED_13
#define PIN_LED_GREEN PIN_LED_8
#define PIN_LED_RED PIN_LED_9

/**
 * Analog pin definitions
 * Explicitly define each analog pin number to its corresponding digital pin number
 */

// Standard analog pins as defines
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

#define PIN_A10 (4)
#define PIN_A11 (19)
#define PIN_A12 (20)
#define PIN_A13 (23)
#define PIN_A14 (24)
#define PIN_A15 (25)
#define PIN_A16 (26)
#define PIN_A17 (21)
#define PIN_A18 (17)

// DAC pins as defines
#define PIN_DAC0 PIN_A0
#define PIN_DAC1 PIN_A1

    // shorter forms as static constants
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
    static const uint8_t A17 = PIN_A17;
    static const uint8_t A18 = PIN_A18;

    static const uint8_t DAC0 = PIN_DAC0;
    static const uint8_t DAC1 = PIN_DAC1;

// Resolution of the ADC (Analog to Digital Converter)
// This should be 12 for all SAMD boards
#define ADC_RESOLUTION 12

/**
 * USART (Serial) interfaces
 *
 * USART – Synchronous and Asynchronous Receiver and Transmitter
 *
 * Here you should define the pins and SERCOM pads used for each USART (serial) interface on your board.
 * You should end up with 5 defines for each serial interface:
 * - `PIN_SERIAL#_RX` - the digital pin number for the RX line of the serial interface, can be any SERCOM pad (0-3)
 * - `PIN_SERIAL#_TX` - the digital pin number for the TX line of the serial interface, must be SERCOM pad 0
 * - `PAD_SERIAL#_RX` - the SERCOM RX pad used for this serial interface (see below)
 * - `PAD_SERIAL#_TX` - the SERCOM TX pad used for this serial interface (see below)
 * - `SERCOM_SERIAL#` - the SERCOM instance used for this serial interface (e.g. sercom0, sercom1, etc.)
 *
 *
 * The UART Objects themselves are created in variant.cpp using one of two constructors
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

// Serial1 (Bee)
#define PIN_SERIAL1_RX (27) // PB17 SERCOM5/PAD[1]
// ^ Can be any pad (0-3) on a SAMD51 or SAMD21
#define PIN_SERIAL1_TX (28) // PB16 SERCOM5/PAD[0]
// ^ Must always be pad 0
#define PAD_SERIAL1_TX (UART_TX_PAD_0)
#define PAD_SERIAL1_RX (SERCOM_RX_PAD_1)
#define SERCOM_SERIAL1 sercom5

// Serial2 (Grove)
#define PIN_SERIAL2_RX (0) // PA17 SERCOM1/PAD[1]
#define PIN_SERIAL2_TX (1) // PA16 SERCOM1/PAD[0]
#define PAD_SERIAL2_TX (UART_TX_PAD_0)
#define PAD_SERIAL2_RX (SERCOM_RX_PAD_1)
#define SERCOM_SERIAL2 sercom1

// Serial3 (Feather Wing Left)
#define PIN_SERIAL3_RX (64) // PA13 SERCOM2/PAD[1]
#define PIN_SERIAL3_TX (65) // PA12 SERCOM2/PAD[0]
#define PAD_SERIAL3_TX (UART_TX_PAD_0)
#define PAD_SERIAL3_RX (SERCOM_RX_PAD_1)
#define SERCOM_SERIAL3 sercom2

// Serial4 (Feather Wing Right)
#define PIN_SERIAL4_RX (36) // PC17 SERCOM6/PAD[1]
#define PIN_SERIAL4_TX (37) // PC16 SERCOM6/PAD[0]
#define PAD_SERIAL4_TX (UART_TX_PAD_0)
#define PAD_SERIAL4_RX (SERCOM_RX_PAD_1)
#define SERCOM_SERIAL4 sercom6

/**
 * SPI Interfaces
 *
 * SPI – Serial Peripheral Interface (Host operation)
 *
 * Here you should define the pins and SERCOM pads used for each SPI interface on your board.
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
 * This means that the SS pin must be the specified pad on the SERCOM restricting you to using only the single slave attached to that SS pin.
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
 * // Set the pin peripheral of the SS pin to DIO (just in case it had been PIO_SERCOM or PIO_SERCOM_ALT)
 * pinPeripheral( ss_pin_number, PIO_DIGITAL);
 * ```
 */
#define SPI_INTERFACES_COUNT 1

// SD Card SPI
#define PIN_SPI_MOSI (33) // D33 PB12 SPI MOSI SERCOM4/PAD[0]
// ^ Digital pin for SPI Data Out (MOSI as host, MISO as client) can be pad 0 or 3 on a SAMD51 or 0, 2, or 3 on a SAMD21
#define PIN_SPI_SCK (34) // D34 PB13 SPI SCK SERCOM4/PAD[1]
// ^ Digital pin for SPI SCK must be pad 1 on a SAMD51 or 1 or 3 on a SAMD21
#define PIN_SPI_SS (35) // D35 PB11 SPI (SD card/other) CS SERCOM4/PAD[2]
// ^ Digital pin for SPI CS must always be pad 2
#define PIN_SPI_MISO (32) // D32 PB15 SPI MISO SERCOM4/PAD[3]
// ^ Digital pin for SPI MISO SERCOM4/PAD[3]
#define PERIPH_SPI sercom4
// ^ the SERCOM instance used for this SPI interface (e.g. sercom0, sercom1, etc.)

// Set the entire Tx config here
#define PAD_SPI_TX SPI_PAD_0_SCK_1 // Data Out (MOSI) on pad 0, SCK is on pad 1, Hardware SS is on pad 2 (Only pad 3 left for MISO)
// MISO - Rx - Main In, Sub Out (master in, slave out)
#define PAD_SPI_RX SERCOM_RX_PAD_3 // MISO is on pad 3

    // static constants for the SPI pins, you should not need to modify these
    static const uint8_t SS = PIN_SPI_SS;
    static const uint8_t MOSI = PIN_SPI_MOSI;
    static const uint8_t MISO = PIN_SPI_MISO;
    static const uint8_t SCK = PIN_SPI_SCK;

// Defines needed for SD/SdFat library
#define SDCARD_SPI SPI
#define SDCARD_MISO_PIN PIN_SPI_MISO
#define SDCARD_MOSI_PIN PIN_SPI_MOSI
#define SDCARD_SCK_PIN PIN_SPI_SCK
#define SDCARD_SS_PIN PIN_SPI_SS

// Other pins
#define PIN_ATN (PIN_SPI_SS) // Default Chip Select for SPI (See https://forum.arduino.cc/t/whats-the-purpose-of-the-new-atn-pin/318278)
    static const uint8_t ATN = PIN_ATN;

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

#define PIN_WIRE_SDA (30) // PA22 SERCOM3/PAD[0]
// ^ Digital pin for I2C Data (SDA) must be pad 0 on a SAMD51 or SAMD21
#define PIN_WIRE_SCL (29) // PA23 SERCOM3/PAD[1]
// ^ Digital pin for I2C Clock (SCL) must be pad 1 on a SAMD51 or SAMD21
#define PERIPH_WIRE sercom3
// ^ the SERCOM instance used for this I2C interface (e.g. sercom0, sercom1, etc.)

// Wire interrupt handlers
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
#define PIN_USB_HOST_ENABLE (79) // This must be defined, even if it is not used on your board, to avoid compilation errors.
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

/**
 * On-board QSPI Flash
 */
#define EXTERNAL_FLASH_DEVICES GD25Q64E
#define EXTERNAL_FLASH_USE_QSPI

// QSPI Pins
#define PIN_QSPI_SCK (39) // PB10
#define PIN_QSPI_CS (40)  // PB11
#define PIN_QSPI_IO0 (42) // PA08
#define PIN_QSPI_IO1 (43) // PA09
#define PIN_QSPI_IO2 (41) // PA10
#define PIN_QSPI_IO3 (44) // PA11

#if !defined(VARIANT_QSPI_BAUD_DEFAULT)
// TODO: meaningful value for this
#define VARIANT_QSPI_BAUD_DEFAULT 5000000
#endif

/**
 * PCC (Parallel Capture Controller) Pins
 *
 * There is only one possible pin for each signal for PCC.
 * Here you define which digital pin number you've assigned to the corresponding port/pin on your board
 */
#define PIN_PCC_DEN1 (65) // PA12
#define PIN_PCC_DEN2 (66) // PA13
#define PIN_PCC_CLK (31)  // PA14
#define PIN_PCC_XCLK (29) // ??
#define PIN_PCC_D0 (1)    // PA16
#define PIN_PCC_D1 (0)    // PA17
#define PIN_PCC_D2 (51)   // PA18
#define PIN_PCC_D3 (52)   // PA19
#define PIN_PCC_D4 (10)   // PA20
#define PIN_PCC_D5 (11)   // PA21
#define PIN_PCC_D6 (17)   // PA22
#define PIN_PCC_D7 (16)   // PA23
#define PIN_PCC_D8 (35)   // PB14
#define PIN_PCC_D9 (32)   // PB15
#define PIN_PCC_D10 (60)  // PC12
#define PIN_PCC_D11 (61)  // PC13
#define PIN_PCC_D12 (62)  // PC14
#define PIN_PCC_D13 (63)  // PC15

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

// Extern all SERCOM instances here
// SAMD21 has 6 SERCOMs, SAMD51 has 8 SERCOMs
extern SERCOM sercom0;
extern SERCOM sercom1;
extern SERCOM sercom2;
extern SERCOM sercom3;
extern SERCOM sercom4;
extern SERCOM sercom5;
extern SERCOM sercom6;
extern SERCOM sercom7;

// extern all USART/Serial ports here
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

/*----------------------------------------------------------------------------
 *       Other defines
 *
 * Put other defines that will be convenient for your users or libraries here.
 *----------------------------------------------------------------------------*/

#define SerialBee Serial1
static const uint8_t BEEPWR = 18;
static const uint8_t BEERX = PIN_SERIAL1_RX;
static const uint8_t BEETX = PIN_SERIAL1_TX;
static const uint8_t BEEDTR = 23;
static const uint8_t BEERTS = 20;
static const uint8_t BEECTS = 19;
static const uint8_t BEERESET = 24;

static const uint8_t GROVEPWR = 22;
static const uint8_t GROVEPWR_OFF = 0;
static const uint8_t GROVEPWR_ON = 1;

static const uint8_t BATVOLTPIN = 75; // A9
#define BATVOLT_R1 47                 // in fact 4.7M
#define BATVOLT_R2 100                // in fact 10M

#endif /* _VARIANT_STONEFLY_M4_ */

// cSpell:words RXPO DIPO DOPO MSSEN SYNCBUSY PERIPH XCLK LINUXBRIDGE
