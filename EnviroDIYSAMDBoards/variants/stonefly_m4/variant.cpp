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

/**
 * Pin descriptions
 *
 * The structure of the pin description array: (from WVariant.h)
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
        // 0/1 - SERCOM/UART (Serial1)
        {PORTA, 17, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, TC2_CH1, TC2_CH1, EXTERNAL_INT_1}, // D0 UART2 Rx SERCOM1/PAD[1]
        {PORTA, 16, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, TC2_CH0, TC2_CH0, EXTERNAL_INT_0}, // D1 UART2 Tx SERCOM1/PAD[0]

        // 2..5 - Grove GPIOs
        {PORTC, 5, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5},        // D2 GPIO Digital Grove 1
        {PORTC, 6, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6},        // D3 GPIO Digital Grove 1 - SDI12 Data
        {PORTA, 7, PIO_ANALOG, (PIN_ATTR_ANALOG | PIN_ATTR_PWM_E), ADC_Channel7, TC1_CH1, TC1_CH1, EXTERNAL_INT_7}, // D4 GPIO Digital Grove 2, GPIO Analog
        {PORTB, 19, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC1_CH1, TCC1_CH1, EXTERNAL_INT_3},               // D5 GPIO Digital Grove 2

        // 6..7 - Feather Left GPIOs
        {PORTB, 20, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC1_CH2, TCC1_CH2, EXTERNAL_INT_4}, // D6 GPIO Digital Feather Left
        {PORTB, 21, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC1_CH3, TCC1_CH3, EXTERNAL_INT_5}, // D7 GPIO Digital Feather Left

        // 8..9 - LEDs
        {PORTC, 26, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_10}, // D8 LED Green
        {PORTC, 27, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_11}, // D9 LED Red

        // 10..11 - Feather Left GPIOs
        {PORTA, 20, PIO_DIGITAL, PIN_ATTR_PWM_E, No_ADC_Channel, TC7_CH0, TC7_CH0, EXTERNAL_INT_4}, // D10 GPIO Digital Feather Left
        {PORTA, 21, PIO_DIGITAL, PIN_ATTR_PWM_E, No_ADC_Channel, TC7_CH1, TC7_CH1, EXTERNAL_INT_5}, // D11 GPIO Digital Feather Left

        // 12 - 12V power control (optional)
        {PORTB, 22, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6}, // D12 GPIO Digital Power Enable 12V Regulator (optional)

        // 13 - LED
        {PORTC, 28, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_12}, // D13 LED Orange

        // 14..15 - UART Bee (Serial1)
        {PORTB, 17, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, TC6_CH1, TC6_CH1, EXTERNAL_INT_1}, // D14 UART1 Bee RX SERCOM5/PAD[1]
        {PORTB, 16, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, TC6_CH0, TC6_CH0, EXTERNAL_INT_0}, // D15 UART1 Bee Tx SERCOM5/PAD[0]

        // 16..17 - I2C pins (SDA/SCL)
        {PORTA, 23, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, TC4_CH1, TC4_CH1, EXTERNAL_INT_7}, // D16 I2C SCL SERCOM3/PAD[1]
        {PORTA, 22, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, TC4_CH0, TC4_CH0, EXTERNAL_INT_6}, // D17 I2C SDA SERCOM3/PAD[0]

        // 18..20 - Bee Header
        {PORTB, 31, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_15},        // D18 GPIO Digital Power Enable Bee
        {PORTB, 0, PIO_DIGITAL, (PIN_ATTR_ANALOG | PIN_ATTR_PWM_E), ADC_Channel12, TC7_CH0, TC7_CH0, EXTERNAL_INT_0}, // D19 GPIO Digital Bee CTS (Bee pin 12)
        {PORTB, 3, PIO_DIGITAL, (PIN_ATTR_ANALOG | PIN_ATTR_PWM_E), ADC_Channel15, TC6_CH1, TC6_CH1, EXTERNAL_INT_3}, // D20 GPIO Digital Bee RTS (Bee pin 16)

        // 21..22 - Button, Switched Power
        {PORTC, 1, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1},   // D21 GPIO Digital Input User Button
        {PORTA, 27, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_11}, // D22 GPIO Digital Power Enable 3.3V Regulator (optionally 5V and 12V)

        // 23 - Bee Header
        {PORTB, 1, PIO_DIGITAL, (PIN_ATTR_ANALOG | PIN_ATTR_PWM_E), ADC_Channel13, TC7_CH1, TC7_CH1, EXTERNAL_INT_1}, // D23 GPIO Digital Bee DTR/SLEEP (Bee pin 9)

        // 24..25 - SD Card LED's
        {PORTC, 10, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC0_CH0, TCC0_CH0, EXTERNAL_INT_10}, // D24 SD Card LED Green
        {PORTC, 11, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC0_CH1, TCC0_CH1, EXTERNAL_INT_11}, // D25 SD Card LED Red

        // 26 - 5V power control (optional)
        {PORTB, 25, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9}, // D26 GPIO Digital Power Enable 5V Regulator (optional)

        // 27..29 - Bee Header
        {PORTC, 0, PIO_DIGITAL, PIN_ATTR_ANALOG_ALT, ADC_Channel10, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_0},        // D27 GPIO Digital Bee RI (Bee Pin 20)
        {PORTC, 2, PIO_DIGITAL, PIN_ATTR_ANALOG_ALT, ADC_Channel4, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2},         // D28 GPIO Digital Bee STATUS/DIO9 (Bee pin 13)
        {PORTB, 2, PIO_DIGITAL, (PIN_ATTR_ANALOG | PIN_ATTR_PWM_E), ADC_Channel14, TC6_CH0, TC6_CH0, EXTERNAL_INT_2}, // D29 GPIO Digital Bee Reset (Bee pin 5)

        // 30 - Feather Left Power Enable
        {PORTC, 7, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9}, // D30 GPIO Digital Power Enable Feather Left

        // 31 - RTC Interrupt
        {PORTA, 14, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_14}, // D31 GPIO Digital Input RTC Alert

        // 32..35 - SPI SD Card
        {PORTB, 15, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, TC5_CH1, TC5_CH1, EXTERNAL_INT_15}, // D32 SPI0 (SD Card) MISO SERCOM4/PAD[3]
        {PORTB, 12, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, TC4_CH0, TC4_CH0, EXTERNAL_INT_12}, // D33 SPI0 (SD Card) MOSI SERCOM4/PAD[0]
        {PORTB, 13, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, TC4_CH1, TC4_CH1, EXTERNAL_INT_13}, // D34 SPI0 (SD Card) SCK SERCOM4/PAD[1]
        {PORTB, 14, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, TC5_CH0, TC5_CH0, EXTERNAL_INT_14}, // D35 SPI0 (SD Card) SS/CS SERCOM4/PAD[2]

        // 36..37 - UART4 Feather Right (Serial4)
        {PORTC, 17, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, TCC0_CH1, TCC0_CH1, EXTERNAL_INT_1}, // D36 UART4 RX SERCOM6/PAD[1] (Feather Right)
        {PORTC, 16, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, TCC0_CH0, TCC0_CH0, EXTERNAL_INT_0}, // D37 UART4 TX SERCOM6/PAD[0] (Feather Right)

        // 38 - Feather Right Power Enable
        {PORTC, 3, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3}, // D38 GPIO Digital Power Enable Feather Right

        // 39..44 - External Flash QSPI
        {PORTB, 10, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_10}, // D39 QSPI (Flash) SCK
        {PORTB, 11, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_11}, // D40 QSPI (Flash) CS
        {PORTA, 8, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, NOT_AN_INTERRUPT}, // D41 QSPI (Flash) IO0
        {PORTA, 9, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9},   // D42 QSPI (Flash) IO1
        {PORTA, 10, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_10}, // D43 QSPI (Flash) IO2
        {PORTA, 11, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_11}, // D44 QSPI (Flash) IO3

        // 45..46 - RX/TX LEDS
        {PORTB, 23, PIO_DIGITAL, PIN_ATTR_PWM_E, No_ADC_Channel, TC7_CH1, TC7_CH1, EXTERNAL_INT_7},         // D45 LED RX, used as output only
        {PORTB, 24, PIO_DIGITAL, PIN_ATTR_PWM_G, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_8}, // D46 LED TX, used as output only

        // 47..49 - Software Debugging (SWD)
        {PORTA, 30, PIO_COM, PIN_ATTR_PWM_E, No_ADC_Channel, TC6_CH0, TC6_CH0, EXTERNAL_INT_14}, // D47 SWD SWCLK
        {PORTA, 31, PIO_COM, PIN_ATTR_PWM_E, No_ADC_Channel, TC6_CH1, TC6_CH1, EXTERNAL_INT_15}, // D48 SWD SWDIO
        {PORTB, 30, PIO_COM, PIN_ATTR_PWM_E, No_ADC_Channel, TC0_CH0, TC0_CH0, EXTERNAL_INT_14}, // D49 SWD SWO

        // 50..56 - Feather Right GPIOs
        {PORTA, 15, PIO_DIGITAL, PIN_ATTR_PWM_E, No_ADC_Channel, TC3_CH1, TC3_CH1, EXTERNAL_INT_15},  // D50 GPIO Digital Feather Right
        {PORTA, 18, PIO_DIGITAL, PIN_ATTR_PWM_E, No_ADC_Channel, TC3_CH0, TC3_CH0, EXTERNAL_INT_2},   // D51 GPIO Digital Feather Right
        {PORTA, 19, PIO_DIGITAL, PIN_ATTR_PWM_E, No_ADC_Channel, TC3_CH1, TC3_CH1, EXTERNAL_INT_3},   // D52 GPIO Digital Feather Right
        {PORTC, 18, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC0_CH2, TCC0_CH2, EXTERNAL_INT_2}, // D53 GPIO Digital Feather Right
        {PORTC, 19, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC0_CH3, TCC0_CH3, EXTERNAL_INT_3}, // D54 GPIO Digital Feather Right
        {PORTC, 20, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC0_CH4, TCC0_CH4, EXTERNAL_INT_4}, // D55 GPIO Digital Feather Right
        {PORTC, 21, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC0_CH5, TCC0_CH5, EXTERNAL_INT_5}, // D56 GPIO Digital Feather Right

        // 57..63 - Bottom Header Only GPIOs
        {PORTC, 24, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_8}, // D57 GPIO Digital (Bottom Header Only)
        {PORTC, 25, PIO_DIGITAL, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9}, // D58 GPIO Digital (Bottom Header Only)
        {PORTB, 18, PIO_DIGITAL, PIN_ATTR_PWM_F, No_ADC_Channel, TCC1_CH0, TCC1_CH0, EXTERNAL_INT_2},         // D59 GPIO Digital (Bottom Header Only)
        {PORTC, 12, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, TCC0_CH2, TCC0_CH2, EXTERNAL_INT_12},         // D60 GPIO Digital (SERCOM7/PAD[0])
        {PORTC, 13, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, TCC0_CH3, TCC0_CH3, EXTERNAL_INT_13},         // D61 GPIO Digital (SERCOM7/PAD[1])
        {PORTC, 14, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, TCC0_CH4, TCC0_CH4, EXTERNAL_INT_14},         // D62 GPIO Digital (SERCOM7/PAD[2])
        {PORTC, 15, PIO_SERCOM, PIN_ATTR_PWM_F, No_ADC_Channel, TCC0_CH5, TCC0_CH5, EXTERNAL_INT_15},         // D63 GPIO Digital (SERCOM7/PAD[3])

        // 64..65 - UART3 Feather Left
        {PORTA, 13, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, TC2_CH1, TC2_CH1, EXTERNAL_INT_13}, // D64 UART3 RX SERCOM2/PAD[1]
        {PORTA, 12, PIO_SERCOM, PIN_ATTR_PWM_E, No_ADC_Channel, TC2_CH0, TC2_CH0, EXTERNAL_INT_12}, // D65 UART3 TX SERCOM2/PAD[0]

        // 66..76 - Analog pins
        {PORTA, 2, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2},            // D66 GPIO Analog (DAC, ADC)
        {PORTA, 5, PIO_ANALOG, (PIN_ATTR_ANALOG | PIN_ATTR_PWM_E), ADC_Channel5, TC0_CH1, TC0_CH1, EXTERNAL_INT_5}, // D67 GPIO Analog (DAC, ADC, PWM)
        {PORTB, 6, PIO_ANALOG, PIN_ATTR_ANALOG_ALT, ADC_Channel8, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6},        // D68 GPIO Analog (ADC)
        {PORTB, 7, PIO_ANALOG, PIN_ATTR_ANALOG_ALT, ADC_Channel9, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7},        // D69 GPIO Analog (ADC)
        {PORTB, 8, PIO_ANALOG, (PIN_ATTR_ANALOG | PIN_ATTR_PWM_E), ADC_Channel2, TC4_CH0, TC4_CH0, EXTERNAL_INT_8}, // D70 GPIO Analog (ADC, PWM)
        {PORTB, 9, PIO_ANALOG, (PIN_ATTR_ANALOG | PIN_ATTR_PWM_E), ADC_Channel3, TC4_CH1, TC4_CH1, EXTERNAL_INT_9}, // D71 GPIO Analog (ADC, PWM)
        {PORTA, 4, PIO_ANALOG, (PIN_ATTR_ANALOG | PIN_ATTR_PWM_E), ADC_Channel4, TC0_CH0, TC0_CH0, EXTERNAL_INT_4}, // D72 GPIO Analog (ADC, PWM)
        {PORTB, 5, PIO_ANALOG, PIN_ATTR_ANALOG_ALT, ADC_Channel7, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5},        // D73 GPIO Analog (ADC)
        {PORTA, 6, PIO_ANALOG, (PIN_ATTR_ANALOG | PIN_ATTR_PWM_E), ADC_Channel6, TC1_CH0, TC1_CH0, EXTERNAL_INT_6}, // D74 GPIO Analog Input Light Sensor
        {PORTB, 4, PIO_ANALOG, PIN_ATTR_ANALOG_ALT, ADC_Channel6, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_4},        // D75 GPIO Analog Input Volt Divider Battery
        {PORTA, 3, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel1, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3},            // D76 Analog DAC/VREF

        // 77..79 - USB
        {PORTA, 24, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_8},             // D77 USB D-
        {PORTA, 25, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9},             // D78 USB D+
        {NOT_A_PORT, 0, PIO_NOT_A_PIN, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, NOT_AN_INTERRUPT}, // D79 USB Host enable

        // 80..81 - Alternate use of A9 and A7 (DAC output)
        {PORTA, 2, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2},            // D80 GPIO Analog (DAC, ADC)
        {PORTA, 5, PIO_ANALOG, (PIN_ATTR_ANALOG | PIN_ATTR_PWM_E), ADC_Channel5, TC0_CH1, TC0_CH1, EXTERNAL_INT_5}, // D81 GPIO Analog (DAC, ADC, PWM)

};

/**
 * Timer/counter instances list and generic clock instances list
 */

// Timer/counter instances list (you shouldn't need to change it)
const void *g_apTCInstances[TCC_INST_NUM + TC_INST_NUM] = {TCC0, TCC1, TCC2, TCC3, TCC4, TC0, TC1, TC2, TC3, TC4, TC5, TC6, TC7};
// generic clock instances list (you shouldn't need to change it)
const uint32_t GCLK_CLKCTRL_IDs[TCC_INST_NUM + TC_INST_NUM] = {TCC0_GCLK_ID, TCC1_GCLK_ID, TCC2_GCLK_ID, TCC3_GCLK_ID, TCC4_GCLK_ID, TC0_GCLK_ID, TC1_GCLK_ID, TC2_GCLK_ID, TC3_GCLK_ID, TC4_GCLK_ID, TC5_GCLK_ID, TC6_GCLK_ID, TC7_GCLK_ID};

/**
 * SERCOM instances
 */

// Multi-serial objects instantiation
// There are 8 SERCOMs on the SAMD51 and 6 on the SAMD21
SERCOM sercom0(SERCOM0);
SERCOM sercom1(SERCOM1);
SERCOM sercom2(SERCOM2);
SERCOM sercom3(SERCOM3);
SERCOM sercom4(SERCOM4);
SERCOM sercom5(SERCOM5);
// Comment out the SERCOMs below for the SAMD21, which only has 6 SERCOMs
SERCOM sercom6(SERCOM6);
SERCOM sercom7(SERCOM7);

/**
 * USART (Serial) objects instantiation and interrupt handler assignment
 *
 * Create a Uart object for each SERCOM that you want to use as a Serial port.
 * The constructor takes the SERCOM instance, the RX and TX pin numbers, the RX and TX pads, and optionally the RTS and CTS pin numbers (if using hardware flow control).
 *
 * Then, create an interrupt handler for each SERCOM that calls the IrqHandler() method of the corresponding Uart object.
 */

// Serial1 (Bee) [SERCOM5]
// Uart(SERCOM *_s, uint8_t _pinRX, uint8_t _pinTX, SercomRXPad _padRX, SercomUartTXPad _padTX);
// Uart(SERCOM *_s, uint8_t _pinRX, uint8_t _pinTX, SercomRXPad _padRX, SercomUartTXPad _padTX, uint8_t _pinRTS, uint8_t _pinCTS);
Uart Serial1(&SERCOM_SERIAL1, PIN_SERIAL1_RX, PIN_SERIAL1_TX, PAD_SERIAL1_RX, PAD_SERIAL1_TX);

void SERCOM5_0_Handler()
{
    Serial1.IrqHandler();
}
void SERCOM5_1_Handler()
{
    Serial1.IrqHandler();
}
void SERCOM5_2_Handler()
{
    Serial1.IrqHandler();
}
void SERCOM5_3_Handler()
{
    Serial1.IrqHandler();
}

// Serial2 (Grove) [SERCOM1]
// Uart(SERCOM *_s, uint8_t _pinRX, uint8_t _pinTX, SercomRXPad _padRX, SercomUartTXPad _padTX);
// Uart(SERCOM *_s, uint8_t _pinRX, uint8_t _pinTX, SercomRXPad _padRX, SercomUartTXPad _padTX, uint8_t _pinRTS, uint8_t _pinCTS);
Uart Serial2(&SERCOM_SERIAL2, PIN_SERIAL2_RX, PIN_SERIAL2_TX, PAD_SERIAL2_RX, PAD_SERIAL2_TX);

void SERCOM1_0_Handler()
{
    Serial2.IrqHandler();
}
void SERCOM1_1_Handler()
{
    Serial2.IrqHandler();
}
void SERCOM1_2_Handler()
{
    Serial2.IrqHandler();
}
void SERCOM1_3_Handler()
{
    Serial2.IrqHandler();
}

// Serial3 (Feather Wing Left) [SERCOM2]
// Uart(SERCOM *_s, uint8_t _pinRX, uint8_t _pinTX, SercomRXPad _padRX, SercomUartTXPad _padTX);
// Uart(SERCOM *_s, uint8_t _pinRX, uint8_t _pinTX, SercomRXPad _padRX, SercomUartTXPad _padTX, uint8_t _pinRTS, uint8_t _pinCTS);
Uart Serial3(&SERCOM_SERIAL3, PIN_SERIAL3_RX, PIN_SERIAL3_TX, PAD_SERIAL3_RX, PAD_SERIAL3_TX);

void SERCOM2_0_Handler()
{
    Serial3.IrqHandler();
}
void SERCOM2_1_Handler()
{
    Serial3.IrqHandler();
}
void SERCOM2_2_Handler()
{
    Serial3.IrqHandler();
}
void SERCOM2_3_Handler()
{
    Serial3.IrqHandler();
}

// Serial4 (Feather Wing Right) [SERCOM6]
// Uart(SERCOM *_s, uint8_t _pinRX, uint8_t _pinTX, SercomRXPad _padRX, SercomUartTXPad _padTX);
// Uart(SERCOM *_s, uint8_t _pinRX, uint8_t _pinTX, SercomRXPad _padRX, SercomUartTXPad _padTX, uint8_t _pinRTS, uint8_t _pinCTS);
Uart Serial4(&SERCOM_SERIAL4, PIN_SERIAL4_RX, PIN_SERIAL4_TX, PAD_SERIAL4_RX, PAD_SERIAL4_TX);

void SERCOM6_0_Handler()
{
    Serial4.IrqHandler();
}
void SERCOM6_1_Handler()
{
    Serial4.IrqHandler();
}
void SERCOM6_2_Handler()
{
    Serial4.IrqHandler();
}
void SERCOM6_3_Handler()
{
    Serial4.IrqHandler();
}
