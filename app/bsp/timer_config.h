#ifndef TIMER_CONFIG_H
#define TIMER_CONFIG_H

#include "power_manager.h"
#include "mik32_memory_map.h"
#include "timer32.h"

// ===== TIMER32_1: PWM для RGB =====
#define PWM_CH_R         1
#define PWM_CH_G         2
#define PWM_CH_B         3

#define SYSTEM_FREQ_HZ 32000000UL
#define PWM_FREQ_HZ (1000)
#define PWM_PERIOD_TICKS (SYSTEM_FREQ_HZ / PWM_FREQ_HZ)

#define Timer32_1_Set_OCR(channel, ocr) \
    do { TIMER32_1->CHANNELS[channel].OCR = ocr; } while(0)

void TimerRGB_Init(void);
void Timer_Init(void);

#endif // TIMER_CONFIG_H
