#ifndef INC_PINS_H_
#define INC_PINS_H_

#include <stdint.h>
#include <stdbool.h>

#include "board.h"

/* GPIO Pins (General)
 * SW_ENABLE = P0.5
 * BUTTON = P0.4
 * SERVO_PWM = P2.2 (STC0_OUT1)
 * SERVO_EN = P0.2
 * GPS_PWR = P0.17
 */

#define ENABLE_PORT 0
#define ENABLE_PIN 5

#define BUTTON_PORT 0
#define BUTTON_PIN 4

#define SERVO_PWM_PORT 2
#define SERVO_PWM_PIN 2

#define SERVO_EN_PORT 0
#define SERVO_EN_PIN 2

#define GPS_PWR_PORT 0
#define GPS_PWR_PIN 17

/* LCD GPIO Pins as follows:
 * CS = P0.11		- Chip Select
 * DC = P0.12		- Data / Command
 * RESET = P0.13	- Reset
 * BL = P0.14		- Backlight enable
 */

#define LCD_CS_PORT 0
#define LCD_CS_PIN 11

#define LCD_DC_PORT 0
#define LCD_DC_PIN 13

#define LCD_RST_PORT 0
#define LCD_RST_PIN 12

#define LCD_BL_PORT 0
#define LCD_BL_PIN 14

/* SPI Pins (SSP0)
 * SPI_SCK = P0.6
 * SPI_MISO = P0.8
 * SPI_MOSI = P0.9
 */

#define SPI_SCK_PORT 0
#define SPI_SCK_PIN 6

#define SPI_MISO_PORT 0
#define SPI_MISO_PIN 8

#define SPI_MOSI_PORT 0
#define SPI_MOSI_PIN 9

/* UART Pins (UART0)
 * UART_RX = P0.18
 * UART_TX = P0.19
 */

#define UART_RX_PORT 0
#define UART_RX_PIN 18

#define UART_TX_PORT 0
#define UART_TX_PIN 19

void InitPins(void);

#endif /* INC_PINS_H_ */
