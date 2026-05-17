#include "timer_config.h"

void TimerRGB_Init(void)
{
    // Включение тактирования TIMER32_1
    PM->CLK_APB_P_SET |= PM_CLOCK_APB_P_TIMER32_1_M;
    
    // Базовая настройка таймера
    TIMER32_1->ENABLE = 0;
    TIMER32_1->TOP = PWM_PERIOD_TICKS;
    TIMER32_1->PRESCALER = 0;
    TIMER32_1->CONTROL = TIMER32_CONTROL_MODE_UP_M | TIMER32_CONTROL_CLOCK_PRESCALER_M;
    TIMER32_1->INT_MASK = 0;
    TIMER32_1->INT_CLEAR = 0xFFFFFFFF;
    
    // Канал 2 (D5) — Красный
    Timer32_1_Set_OCR(1,0);
    //TIMER32_1->CHANNELS[PWM_CH_R].OCR = 0;
    TIMER32_1->CHANNELS[PWM_CH_R].CNTRL = TIMER32_CH_CNTRL_MODE_PWM_M | TIMER32_CH_CNTRL_ENABLE_M;
    
    // Канал 3 (D6) — Зелёный
    Timer32_1_Set_OCR(2,0);
    //TIMER32_1->CHANNELS[PWM_CH_G].OCR = 0;
    TIMER32_1->CHANNELS[PWM_CH_G].CNTRL = TIMER32_CH_CNTRL_MODE_PWM_M | TIMER32_CH_CNTRL_ENABLE_M;
    
    // Канал 4 (D9) — Синий
    Timer32_1_Set_OCR(3,0);
    //TIMER32_1->CHANNELS[PWM_CH_B].OCR = 0;
    TIMER32_1->CHANNELS[PWM_CH_B].CNTRL = TIMER32_CH_CNTRL_MODE_PWM_M | TIMER32_CH_CNTRL_ENABLE_M;
    
    // Запуск таймера
    TIMER32_1->ENABLE = 1;
}

void Timer_Init(void)
{
    TimerRGB_Init();
}

void delay_ms(uint32_t ms) {
   uint64_t end_mtimer = SCR1_TIMER_GET_TIME() + MS_TO_TICKS(ms);
   while (SCR1_TIMER_GET_TIME() < end_mtimer)
     ;
}