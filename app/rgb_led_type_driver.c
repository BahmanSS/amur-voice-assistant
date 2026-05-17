#include "rgb_led_type_driver.h"

CurrentColor_TypeDef current_color = {0, 0, 0};

// TODO: перенесети функцию для установки ocr в timer_config
void RGBLEDType_SetColor(uint8_t r, uint8_t g, uint8_t b)
{
    current_color.r = r;
    current_color.b = b;
    current_color.g = g;
    Timer32_1_Set_OCR(PWM_CH_R, (PWM_PERIOD_TICKS / 100) * r);
    Timer32_1_Set_OCR(PWM_CH_G, (PWM_PERIOD_TICKS / 100) * g);
    Timer32_1_Set_OCR(PWM_CH_B, (PWM_PERIOD_TICKS / 100) * b);
}

void RGBLEDType_Init()
{
    current_color.r = 1;
    current_color.b = 1;
    current_color.g = 1;
    RGBLEDType_SetColor(1, 1, 1);
}

void RGBLEDType_RainbowEffect(uint32_t duration_ms)
{
    // Сохраняем текущий цвет
    uint8_t saved_r = current_color.r;
    uint8_t saved_g = current_color.g;
    uint8_t saved_b = current_color.b;
    
    // Количество шагов: полный круг 360° с шагом 5° = 72 шага
    const int steps = 360 / 5;  // 72 шага
    
    // Время одного шага
    uint32_t step_delay = duration_ms / steps;
    
    for (int step = 0; step < steps; step++) {
        // Угол: 0, 5, 10, ... 355 градусов
        int angle = step * 5;
        
        // Разбиваем на 6 секторов по 60 градусов
        int sector = angle / 60;      // 0..5
        int pos = angle % 60;         // 0..59
        
        // Яркость в секторе (0..100)
        int brightness = (pos * 100) / 60;
        int inv_brightness = 100 - brightness;
        
        switch (sector) {
            case 0:  // Красный → Жёлтый
                RGBLEDType_SetColor(100, brightness, 0);
                break;
            case 1:  // Жёлтый → Зелёный
                RGBLEDType_SetColor(inv_brightness, 100, 0);
                break;
            case 2:  // Зелёный → Голубой
                RGBLEDType_SetColor(0, 100, brightness);
                break;
            case 3:  // Голубой → Синий
                RGBLEDType_SetColor(0, inv_brightness, 100);
                break;
            case 4:  // Синий → Пурпурный
                RGBLEDType_SetColor(brightness, 0, 100);
                break;
            default: // Пурпурный → Красный (sector 5)
                RGBLEDType_SetColor(100, 0, inv_brightness);
                break;
        }
        
        delay_ms(step_delay);
    }
    
    // Возвращаем исходный цвет
    RGBLEDType_SetColor(saved_r, saved_g, saved_b);
}