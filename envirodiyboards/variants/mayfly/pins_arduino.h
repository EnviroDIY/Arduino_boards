#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>

// ATMEL ATMEGA1284P
// (Notice that EnviroDIY Mayfly is equiped with TQFN package. The layout below is
// just a convenience to see the port names and their usage.)
//
//                 |-----ICR BIT 1 (B)----|           |--ICR BIT 0 (A)--|
//                 SD             RED  GREEN          |--Processor ADC--|
//                CS/SS           LED1 LED2           D24  D25  D26  D27
//                 D12  D11  D10  D09  D08  GND  VCC  A00  A01  A02  A03
// ____            _44___43___42___41___40___39___38___37___36___35___34_                  ____
//  |        MOSI 1| *                                                   |33 A04/D28        |
// ICR             |                                                     |                  |
// BIT  MISO/OC3A 2|                                                     |32 A05/D29       ICR
// 1(B)            |                                                     |                 BIT
//__|__  SCK/OC3B 3|                                                     |31 A06/D30 BATT  0(A)
//                 |                                                     |                  |
//         RESET  4|                                                     |30 A07/D31 RTC  __|__
//                 |                                                     |
//           VCC  5|                                                     |29 AREF
//           GND  6|                                                     |28 GND
//         XTAL2  7|                                                     |27 AVCC
//                 |                                                     |                      ____
//         XTAL1  8|                                                     |26 D23 XBEE DTR        |
//    ____         |                                                     |                       |
//     |    RXD0  9|                                                     |25 D22 SWITCHED POWER ICR
//    ICR          |                                                     |                      BIT
//    BIT   TXD0 10|                                                     |24 TDI D21 BUTTON     2(C)
//    3(D)         |                                                     |                       |
//   __|__  RXD1 11|_____________________________________________________|23 TDO D20 XBEE RTS  __|__
//                 12   13   14   15   16   17   18   19   20   21   22
//                 TXD2 D04  D05  D06  D07  VCC  GND  SCL  SDA  TCK  TMS
//                |-----ICR BIT 3 (D)----|                      D18  D19
//                                                                   XBEE
//                                                                   CTS
//                                                   |--ICR BIT 2 (C)--|
//
/*
 * Arduino digital pin numbers:
 * 0..32
 * PD0..PD7, PB0..PB7, PC0..PC7, PA0..PA7
 */

#define NUM_DIGITAL_PINS            32
#define NUM_ANALOG_INPUTS           8

#define analogInputToDigitalPin(p)  ((p < NUM_ANALOG_INPUTS) ? (p) + 24 : -1)

#define digitalPinHasPWM(p)         ((p) == 3 || (p) == 4 || (p) == 6 || (p) == 7 || (p) == 12 || (p) == 13 || (p) == 14 || (p) == 15)

static const uint8_t SS   = 12;
static const uint8_t MOSI = 13;
static const uint8_t MISO = 14;
static const uint8_t SCK  = 15;

static const uint8_t SDA = 17;
static const uint8_t SCL = 16;

static const uint8_t GROVEPWR = 22;
static const uint8_t GROVEPWR_OFF = LOW;
static const uint8_t GROVEPWR_ON = HIGH;

static const uint8_t BEEDTR = 23;
static const uint8_t BEERTS = 20;
static const uint8_t BEECTS = 19;

static const uint8_t LED2 = 8;                  // Green
static const uint8_t LED1 = 9;                  // Red

static const uint8_t BATVOLTPIN = 30;           // A6
#define BATVOLT_R1      47                      // in fact 4.7M
#define BATVOLT_R2      100                     // in fact 10M

static const uint8_t A0 = 24;
static const uint8_t A1 = 25;
static const uint8_t A2 = 26;
static const uint8_t A3 = 27;
static const uint8_t A4 = 28;
static const uint8_t A5 = 29;
static const uint8_t A6 = 30;
static const uint8_t A7 = 31;

/*
   PCINT31-24: D7-0   : bit 3
   PCINT15-8:  D15-8  : bit 1
   PCINT23-16: D23-16 : bit 2
   PCINT7-0:   D31-24 : bit 0 (also A0..A7)
*/

#define digitalPinToPCICR(p)    (((p) >= 0 && (p) < NUM_DIGITAL_PINS) ? (&PCICR) : ((uint8_t *)0))
#define digitalPinToPCICRbit(p) (((p) <= 7) ? 3         : (((p) <= 15) ? 1         : (((p) <= 23) ? 2         : 0)))
#define digitalPinToPCMSK(p)    (((p) <= 7) ? (&PCMSK3) : (((p) <= 15) ? (&PCMSK1) : (((p) <= 23) ? (&PCMSK2) : (&PCMSK0))))
#define digitalPinToPCMSKbit(p) ((p) % 8)

#ifdef ARDUINO_MAIN

// These are used as index in port_to_XYZ arrays, right?
#define PA 1
#define PB 2
#define PC 3
#define PD 4

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
const uint16_t PROGMEM port_to_mode_PGM[] =
{
	NOT_A_PORT,
	(uint16_t) &DDRA,
	(uint16_t) &DDRB,
	(uint16_t) &DDRC,
	(uint16_t) &DDRD,
};

const uint16_t PROGMEM port_to_output_PGM[] =
{
	NOT_A_PORT,
	(uint16_t) &PORTA,
	(uint16_t) &PORTB,
	(uint16_t) &PORTC,
	(uint16_t) &PORTD,
};

const uint16_t PROGMEM port_to_input_PGM[] =
{
	NOT_A_PORT,
	(uint16_t) &PINA,
	(uint16_t) &PINB,
	(uint16_t) &PINC,
	(uint16_t) &PIND,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] =
{
	PD, /* 0 */
	PD,
	PD,
	PD,
	PD,
	PD,
	PD,
	PD,
	PB, /* 8 */
	PB,
	PB,
	PB,
	PB,
	PB,
	PB,
	PB,
	PC, /* 16 */
	PC,
	PC,
	PC,
	PC,
	PC,
   	PC,
	PC,
	PA, /* 24 */
	PA,
	PA,
	PA,
	PA,
	PA,
	PA,
	PA  /* 31 */
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] =
{
	_BV(0), /* 0, port D */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(0), /* 8, port B */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(0), /* 16, port C */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(0), /* 24, port A */
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(6),
	_BV(7)
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] =
{
	NOT_ON_TIMER, 	/* 0  - PD0 */
	NOT_ON_TIMER, 	/* 1  - PD1 */
	NOT_ON_TIMER, 	/* 2  - PD2 */
	NOT_ON_TIMER, 	/* 3  - PD3 */
	TIMER1B,     	/* 4  - PD4 */
	TIMER1A,     	/* 5  - PD5 */
	TIMER2B,     	/* 6  - PD6 */
	TIMER2A,     	/* 7  - PD7 */
	NOT_ON_TIMER, 	/* 8  - PB0 */
	NOT_ON_TIMER, 	/* 9  - PB1 */
	NOT_ON_TIMER, 	/* 10 - PB2 */
	TIMER0A,     	/* 11 - PB3 */
	TIMER0B, 	/* 12 - PB4 */
	NOT_ON_TIMER, 	/* 13 - PB5 */
	TIMER3A, 	/* 14 - PB6 */
	TIMER3B,	/* 15 - PB7 */
	NOT_ON_TIMER, 	/* 16 - PC0 */
	NOT_ON_TIMER,   /* 17 - PC1 */
	NOT_ON_TIMER,   /* 18 - PC2 */
	NOT_ON_TIMER,   /* 19 - PC3 */
	NOT_ON_TIMER,   /* 20 - PC4 */
	NOT_ON_TIMER,   /* 21 - PC5 */
	NOT_ON_TIMER,   /* 22 - PC6 */
	NOT_ON_TIMER,   /* 23 - PC7 */
	NOT_ON_TIMER,   /* 24 - PA0 */
	NOT_ON_TIMER,   /* 25 - PA1 */
	NOT_ON_TIMER,   /* 26 - PA2 */
	NOT_ON_TIMER,   /* 27 - PA3 */
	NOT_ON_TIMER,   /* 28 - PA4 */
	NOT_ON_TIMER,   /* 29 - PA5 */
	NOT_ON_TIMER,   /* 30 - PA6 */
	NOT_ON_TIMER   /* 31 - PA7 */
};

#endif // ARDUINO_MAIN

#endif // Pins_Arduino_h
// vim:ai:cin:sts=2 sw=2 ft=cpp
