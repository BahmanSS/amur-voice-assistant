#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

#include "power_manager.h"
#include "pad_config.h"
#include "gpio.h"
#include "mik32_memory_map.h"

#define SET_TWO_BIT(REG, NUM, TWO_BITS)                                         \
  ((REG) = ((REG) & ~PAD_CONFIG_PIN_M(NUM)) | PAD_CONFIG_PIN(NUM, (TWO_BITS)))

/*
 * ===== Назначение пинов платы Ace Uno (MK32 Амур) =====
 *
 * DHT11:    D11  (PORT 1.1)  - датчик температуры и влажности(1-wire)
 * 
 * RGB Type: D5  (PORT 0.1)  - красный канал (PWM, TIMER32_1 CH1)
 *           D6  (PORT 0.2)  - зелёный канал (PWM, TIMER32_1 CH2)
 *           D9  (PORT 0.3)  - синий канал   (PWM, TIMER32_1 CH3)
 * 
 * DFPlayer: TX0  (PORT 0.5)  - UART TX, передача команд плееру
 *           RX0  (PORT 0.6)  - UART RX, приём ответов от плеера(опционально)
 * 
 * DF2301Q:  TX1 (PORT 1.8) - UART TX, передача команд плееру(опционально)
 *           RX1 (PORT 1.9) - UART RX, приём ответов от плеера
 * 
 */

// ===== DHT11 (датчик температуры и влажности, 1-wire) =====
#define DHT11_PORT      GPIO_1
#define DHT11_PIN       (1)   // D11

// ===== RGB LED (ШИМ-управление лентой) =====
#define RGB_PORT        GPIO_0
#define RGB_R_PIN       (1)   // D5, TIMER32_1 канал 1
#define RGB_G_PIN       (2)   // D6, TIMER32_1 канал 2
#define RGB_B_PIN       (3)   // D9, TIMER32_1 канал 3

// ===== DFPlayer Mini (MP3-плеер, UART) =====
#define DFPLAYER_PORT   GPIO_0
#define DFPLAYER_RX_PIN (5)   // D0, RX — приём ответов от плеера
#define DFPLAYER_TX_PIN (6)   // D1, TX — передача команд плееру

// ===== DF2301Q (Модуль распознвоания речи, UART) =====
#define DF2301Q_PORT GPIO_1
#define DF2301Q_SDA_PIN (8)
#define DF2301Q_SCL_PIN (9)

void Pinmux_Init();

#endif // PIN_CONFIG_H