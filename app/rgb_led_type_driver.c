#include "rgb_led_type_driver.h"

// TODO: перенесети функцию для установки ocr в timer_config
void RGBLEDType_SetColor(uint8_t r, uint8_t g, uint8_t b)
{
    Timer32_1_Set_OCR(PWM_CH_R, (PWM_PERIOD_TICKS / 100) * r);
    Timer32_1_Set_OCR(PWM_CH_G, (PWM_PERIOD_TICKS / 100) * g);
    Timer32_1_Set_OCR(PWM_CH_B, (PWM_PERIOD_TICKS / 100) * b);
}

void RGBLEDType_Init()
{
    RGBLEDType_SetColor(1, 1, 1);
}


