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

#include "variant.h"

/*
 * Pins descriptions
 *
 * The structure of the pin descrption array: (from WVariant.h)
 * typedef struct _PinDescription
 * {
 *   EPortType       ulPort ; // IO Pin Controller PORT/group
 *   uint32_t        ulPin ;  // The pin within the PORT (not the physical pin number!)
 *   EPioType        ulPinType ; // The peripheral controlling the pin, see WVariant.h
 *   uint32_t        ulPinAttribute ; // See Pin Attributes to be OR-ed in WVariant.h
 *   EAnalogChannel  ulADCChannelNumber ; // ADC Channel number in the SAM device
 *   EPWMChannel     ulPWMChannel ; // The pulse wave management channel (tied to the timer channel)
 *   ETCChannel      ulTCChannel ; //  The Timer/Counter for Control applications (TCC) peripheral channel
 *   EExt_Interrupts ulExtInt ; // For attachInterrupt(), which external interrupt does this pin tie to
 * } PinDescription ;
 */
const PinDescription g_APinDescription[] =
    {
        // 0..13 - Digital pins
        // ----------------------
        // 0/1 - SERCOM/UART (Serial1)
        {PORTA, 17, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1}, // D0 UART1 RX SERCOM1/PAD[1]
        {PORTA, 16, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_0}, // D1 UART1 TX SERCOM1/PAD[0]

        // 2..5 - Grove GPIOs
        // ----------------------
        {PORTC, 5, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5},  // D2 Grove 1
        {PORTC, 6, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6},  // D3 Grove 1 - SDI12 Data
        {PORTB, 18, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC1_CH0, NOT_ON_TIMER, EXTERNAL_INT_2},     // D4 Grove 2
        {PORTB, 19, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3}, // D5 Grove 2

        // 6..7 - Feather Left GPIOs
        // ----------------------
        {PORTB, 20, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC1_CH2, NOT_ON_TIMER, EXTERNAL_INT_4}, // D6 Feather Left
        {PORTB, 21, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC1_CH3, NOT_ON_TIMER, EXTERNAL_INT_5}, // D7 Feather Left

        // 8..9 - LEDs
        // ----------------------
        {PORTC, 26, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_10}, // D8 LED Green
        {PORTC, 27, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_11}, // D9 LED Red

        // 10..12 - Feather Left GPIOs
        // ----------------------
        {PORTA, 20, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_4}, // D10 Feather Left
        {PORTA, 21, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5}, // D11 Feather Left
        {PORTB, 22, PIO_DIGITAL, PIN_ATTR_PWM_E, No_ADC_Channel, TC7_CH0, TC7_CH0, EXTERNAL_INT_6},           // D12 GPIO

        // 13 - LED
        // ----------------------
        {PORTC, 28, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_12}, // D13 LED Purple

        // 14..15 - UART Bee
        // --------------------
        {PORTB, 17, PIO_SERCOM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1}, // D14 UART Bee RX SERCOM5/PAD[1]
        {PORTB, 16, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, TC6_CH0, TC6_CH0, EXTERNAL_INT_0},           // D15 UART Bee TX SERCOM5/PAD[0]

        // 16..17 - I2C pins (SDA/SCL)
        // ----------------------
        {PORTA, 23, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, TC4_CH1, TC4_CH1, EXTERNAL_INT_7}, // D16 I2C SCL SERCOM3/PAD[1]
        {PORTA, 22, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, TC4_CH0, TC4_CH0, EXTERNAL_INT_6}, // D17 I2C SDA SERCOM3/PAD[0]

        // 18..19 - Bee Header
        // ----------------------
        {PORTB, 31, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_15},        // D18 Bee Power Control
        {PORTB, 0, PIO_DIGITAL, (PIN_ATTR_ANALOG | PIN_ATTR_PWM_E), ADC_Channel12, TC7_CH0, TC7_CH0, EXTERNAL_INT_0}, // D19 Bee CTS (Bee pin 12)

        // 20 - SPI/Flash Chip Select
        // ----------------------
        {PORTA, 10, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_10}, // D20 SPI (Flash) CS SERCOM0/PAD[2]

        // 21..22 - Button, Power
        // ----------------------
        {PORTC, 1, PIO_DIGITAL, PIN_ATTR_ANALOG_ALT, ADC_Channel11, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1}, // D21 User Button
        {PORTA, 27, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_11}, // D22 Switched 3.3V Enable

        // 23..25 - Bee Header
        // ----------------------
        {PORTB, 1, PIO_DIGITAL, (PIN_ATTR_ANALOG | PIN_ATTR_PWM_E), ADC_Channel13, TC7_CH1, TC7_CH1, EXTERNAL_INT_1}, // D23 Bee DTR/SLEEP (Bee pin 9)
        {PORTB, 2, PIO_DIGITAL, (PIN_ATTR_ANALOG | PIN_ATTR_PWM_E), ADC_Channel14, TC6_CH0, TC6_CH0, EXTERNAL_INT_2}, // D24 Bee Reset (Bee pin 5)
        {PORTB, 3, PIO_DIGITAL, (PIN_ATTR_ANALOG | PIN_ATTR_PWM_E), ADC_Channel15, TC6_CH1, TC6_CH1, EXTERNAL_INT_3}, // D25 Bee RTS (Bee pin 16)

        // 26..27 - UART2 Feather Right
        // --------------------
        {PORTA, 13, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, TC2_CH1, TC2_CH1, EXTERNAL_INT_13}, // D26 UART2 RX SERCOM2/PAD[1]
        {PORTA, 12, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, TC2_CH0, TC2_CH0, EXTERNAL_INT_12}, // D27 UART2 TX SERCOM2/PAD[0]

        // 28 - SD Card Detect
        // ----------------------
        {PORTB, 15, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC4_CH1, NOT_ON_TIMER, EXTERNAL_INT_15}, // D28 SD Card Detect

        // 29 - SPI/SD Card Chip Select
        // ----------------------
        {PORTB, 11, PIO_SERCOM_ALT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_11}, // D29 SPI (SD card/other) CS SERCOM4/PAD[3]

        // 30..32 - SD Card
        // ----------------------
        {PORTB, 10, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_10}, // D30 SD Card Power
        {PORTC, 10, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_10}, // D31 SD Card LED Green
        {PORTC, 11, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_11}, // D32 SD Card LED Red

        // 33..35 - SPI SD Card
        // ----------------------
        {PORTB, 12, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, TCC3_CH0, NOT_ON_TIMER, EXTERNAL_INT_12}, // D33 SPI MOSI SERCOM4/PAD[0]
        {PORTB, 13, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, TCC3_CH1, NOT_ON_TIMER, EXTERNAL_INT_13}, // D34 SPI SCK SERCOM4/PAD[1]
        {PORTB, 14, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, TCC4_CH0, NOT_ON_TIMER, EXTERNAL_INT_14}, // D35 SPI MISO SERCOM4/PAD[2]

        // 36..37 - UART3 Feather Left
        // --------------------
        {PORTC, 17, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, TCC0_CH1, NOT_ON_TIMER, EXTERNAL_INT_1}, // D36 UART3 RX SERCOM6/PAD[1]
        {PORTC, 16, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, TCC0_CH0, NOT_ON_TIMER, EXTERNAL_INT_0}, // D37 UART3 TX SERCOM6/PAD[0]

        // 38..41 - More Digital Pins
        {PORTA, 14, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC2_CH0, NOT_ON_TIMER, EXTERNAL_INT_14},     // D38 RTC Alert
        {PORTB, 25, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9},  // D39 Charge State 1
        {PORTC, 24, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_8},  // D40 Charge State 2
        {PORTC, 0, PIO_DIGITAL, PIN_ATTR_ANALOG_ALT, ADC_Channel10, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_0}, // D41 GPIO

        // 42..44 - SPI Flash
        // ----------------------
        {PORTA, 8, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NMI}, // D42 SPI MOSI SERCOM0/PAD[0]
        {PORTA, 9, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9},   // D43 SPI SCK SERCOM0/PAD[1]
        {PORTA, 11, PIO_SERCOM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_11}, // D44 SPI MISO SERCOM0/PAD[3]

        // 45..46 - RX/TX LEDS
        // --------------------
        {PORTB, 23, PIO_OUTPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7}, // D45 LED RX, used as output only
        {PORTB, 24, PIO_OUTPUT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_8}, // D46 LED TX, used as output only

        // 47..49 - SWD
        // --------------------
        {PORTA, 30, PIO_COM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_14}, // D47 SWCLK
        {PORTA, 31, PIO_COM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_15}, // D48 SWDIO
        {PORTB, 30, PIO_COM, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_14}, // D49 SWO

        // 50..56 - Feather Right GPIOs
        // ----------------------
        {PORTA, 15, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC2_CH1, NOT_ON_TIMER, EXTERNAL_INT_15}, // D50 Feather Right
        {PORTA, 18, PIO_DIGITAL, PIN_ATTR_PWM_E, No_ADC_Channel, TC3_CH0, TC3_CH0, EXTERNAL_INT_2},        // D51 Feather Right
        {PORTA, 19, PIO_DIGITAL, PIN_ATTR_PWM_E, No_ADC_Channel, TC3_CH1, TC3_CH1, EXTERNAL_INT_3},        // D52 Feather Right
        {PORTC, 18, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC0_CH2, NOT_ON_TIMER, EXTERNAL_INT_2},  // D53 Feather Right
        {PORTC, 19, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC0_CH3, NOT_ON_TIMER, EXTERNAL_INT_3},  // D54 Feather Right
        {PORTC, 20, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC0_CH4, NOT_ON_TIMER, EXTERNAL_INT_4},  // D55 Feather Right
        {PORTC, 21, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC0_CH5, NOT_ON_TIMER, EXTERNAL_INT_5},  // D56 Feather Right

        // 57..65 - More GPIOs
        // ----------------------
        {PORTC, 25, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9},             // D57 Fuel Gage Alert
        {PORTA, 7, PIO_DIGITAL, (PIN_ATTR_ANALOG | PIN_ATTR_PWM_E), ADC_Channel7, TC1_CH1, NOT_ON_TIMER, EXTERNAL_INT_7}, // D58 Bee RI (Bee Pin 20)
        {PORTC, 7, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9},              // D59 Feather Power Enable
        {PORTC, 12, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_12},            // D60 GPIO (SERCOM7 Tx)
        {PORTC, 13, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_13},            // D61 GPIO (SERCOM7 Rx)
        {PORTC, 14, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_14},            // D62 GPIO (SERCOM7)
        {PORTC, 15, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_15},            // D63 GPIO (SERCOM7)
        {PORTC, 2, PIO_DIGITAL, PIN_ATTR_ANALOG_ALT, ADC_Channel4, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2},             // D64 Bee STATUS/DIO9
        {PORTC, 3, PIO_DIGITAL, PIN_ATTR_ANALOG_ALT, ADC_Channel5, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3},             // D65 Switched 5V/12V Enable (optional)

        // 66..75 - Analog pins
        // --------------------
        {PORTB, 4, PIO_ANALOG, PIN_ATTR_ANALOG_ALT, ADC_Channel6, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_4},             // D66 Analog GPIO
        {PORTB, 5, PIO_ANALOG, PIN_ATTR_ANALOG_ALT, ADC_Channel7, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5},             // D67 Analog GPIO
        {PORTB, 6, PIO_ANALOG, PIN_ATTR_ANALOG_ALT, ADC_Channel8, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6},             // D68 Analog GPIO
        {PORTB, 7, PIO_ANALOG, PIN_ATTR_ANALOG_ALT, ADC_Channel9, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7},             // D69 Analog GPIO
        {PORTB, 8, PIO_ANALOG, PIN_ATTR_ANALOG_ALT, ADC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_8},             // D70 Analog GPIO
        {PORTB, 9, PIO_ANALOG, PIN_ATTR_ANALOG_ALT, ADC_Channel1, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9},             // D71 Analog GPIO
        {PORTA, 4, PIO_ANALOG, (PIN_ATTR_ANALOG | PIN_ATTR_PWM_E), ADC_Channel4, TC0_CH0, TC0_CH0, EXTERNAL_INT_4},      // D72 Analog GPIO
        {PORTA, 5, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel5, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5},                 // D73 Analog GPIO
        {PORTA, 6, PIO_ANALOG, (PIN_ATTR_ANALOG | PIN_ATTR_PWM_E), ADC_Channel6, TC1_CH0, NOT_ON_TIMER, EXTERNAL_INT_6}, // D74 Light Sensor
        {PORTA, 2, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2},                 // D75 Battery Volt Divider

        // 76 (AREF)
        {PORTA, 3, PIO_ANALOG, PIN_ATTR_ANALOG, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3}, // D76 DAC/VREFP

        // 77..79 - USB
        // --------------------
        {PORTA, 24, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_8},              // D76 USB D-
        {PORTA, 25, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9},              // D77 USB D+
        {NOT_A_PORT, 0, PIO_NOT_A_PIN, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // USB Host enable DOES NOT EXIST ON THIS BOARD

        // ----------------------
        // 80..81 - Alternate use of A9 and A7 (DAC output)
        {PORTA, 2, PIO_ANALOG, PIN_ATTR_ANALOG, DAC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2}, // D80 Analog DAC/VOUT[0]
        {PORTA, 5, PIO_ANALOG, PIN_ATTR_ANALOG, DAC_Channel1, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5}, // D81 Analog DAC/VOUT[1]
};

const void *g_apTCInstances[TCC_INST_NUM + TC_INST_NUM] = {TCC0, TCC1, TCC2, TCC3, TCC4, TC0, TC1, TC2, TC3, TC4, TC5, TC6, TC7};
const uint32_t GCLK_CLKCTRL_IDs[TCC_INST_NUM + TC_INST_NUM] = {TCC0_GCLK_ID, TCC1_GCLK_ID, TCC2_GCLK_ID, TCC3_GCLK_ID, TCC4_GCLK_ID, TC0_GCLK_ID, TC1_GCLK_ID, TC2_GCLK_ID, TC3_GCLK_ID, TC4_GCLK_ID, TC5_GCLK_ID, TC6_GCLK_ID, TC7_GCLK_ID};

// Multi-serial objects instantiation
SERCOM sercom0(SERCOM0);
SERCOM sercom1(SERCOM1);
SERCOM sercom2(SERCOM2);
SERCOM sercom3(SERCOM3);
SERCOM sercom4(SERCOM4);
SERCOM sercom5(SERCOM5);
SERCOM sercom6(SERCOM6);
SERCOM sercom7(SERCOM7);

// Serial1 (Grove) [SERCOM1]
Uart Serial1(&SERCOM_SERIAL1, PIN_SERIAL1_RX, PIN_SERIAL1_TX, PAD_SERIAL1_RX, PAD_SERIAL1_TX);

void SERCOM1_0_Handler()
{
    Serial1.IrqHandler();
}
void SERCOM1_1_Handler()
{
    Serial1.IrqHandler();
}
void SERCOM1_2_Handler()
{
    Serial1.IrqHandler();
}
void SERCOM1_3_Handler()
{
    Serial1.IrqHandler();
}

// Serial2 (Feather Wing Right) [SERCOM2]
Uart Serial2(&SERCOM_SERIAL2, PIN_SERIAL2_RX, PIN_SERIAL2_TX, PAD_SERIAL2_RX, PAD_SERIAL2_TX);

void SERCOM2_0_Handler()
{
    Serial2.IrqHandler();
}
void SERCOM2_1_Handler()
{
    Serial2.IrqHandler();
}
void SERCOM2_2_Handler()
{
    Serial2.IrqHandler();
}
void SERCOM2_3_Handler()
{
    Serial2.IrqHandler();
}

// Serial3 (Feather Wing Left) [SERCOM6]
Uart Serial3(&SERCOM_SERIAL3, PIN_SERIAL3_RX, PIN_SERIAL3_TX, PAD_SERIAL3_RX, PAD_SERIAL3_TX);

void SERCOM6_0_Handler()
{
    Serial3.IrqHandler();
}
void SERCOM6_1_Handler()
{
    Serial3.IrqHandler();
}
void SERCOM6_2_Handler()
{
    Serial3.IrqHandler();
}
void SERCOM6_3_Handler()
{
    Serial3.IrqHandler();
}

// Serial4 (Bee) [SERCOM5]
Uart Serial4(&SERCOM_SERIAL4, PIN_SERIAL4_RX, PIN_SERIAL4_TX, PAD_SERIAL4_RX, PAD_SERIAL4_TX);

void SERCOM5_0_Handler()
{
    Serial4.IrqHandler();
}
void SERCOM5_1_Handler()
{
    Serial4.IrqHandler();
}
void SERCOM5_2_Handler()
{
    Serial4.IrqHandler();
}
void SERCOM5_3_Handler()
{
    Serial4.IrqHandler();
}
