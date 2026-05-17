#ifndef TIMER_CONFIG_H
#define TIMER_CONFIG_H

#include "power_manager.h"
#include "mik32_memory_map.h"
#include "timer32.h"
#include "scr1_timer.h"

// ===== TIMER32_1: PWM для RGB =====
#define PWM_CH_R         1
#define PWM_CH_G         2
#define PWM_CH_B         3

#define SYSTEM_FREQ_HZ 32000000UL
#define PWM_FREQ_HZ (1000)
#define PWM_PERIOD_TICKS (SYSTEM_FREQ_HZ / PWM_FREQ_HZ)

#define Timer32_1_Set_OCR(channel, ocr) \
    do { TIMER32_1->CHANNELS[channel].OCR = ocr; } while(0)

#define MS_TO_TICKS(ms)                                                         \
  ((SYSTEM_FREQ_HZ / 1000) * (ms))

#define SCR1_TIMER_GET_TIME()                                                   \
  (((uint64_t)(SCR1_TIMER->MTIMEH) << 32) | (SCR1_TIMER->MTIME))

void TimerRGB_Init(void);
void Timer_Init(void);

void delay_ms(uint32_t ms);

#endif // TIMER_CONFIG_H
