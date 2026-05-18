#include "rgb_led_type_driver.h"
#include "mik32_memory_map.h"
#include "power_manager.h"

CurrentColor_TypeDef current_color = {0, 0, 0};

static RGB_Mode_TypeDef current_mode = RGB_MODE_STATIC;
static uint32_t effect_counter = 0;
static uint8_t effect_state = 0;
static uint8_t breath_value = 0;
static uint8_t breath_dir = 1;

// Цвета для дискотеки
static const uint8_t disco_colors[][3] = {
    {100, 0, 0},    // Красный
    {0, 100, 0},    // Зелёный
    {0, 0, 100},    // Синий
    {100, 100, 0},  // Жёлтый
    {100, 0, 100},  // Пурпурный
    {0, 100, 100},  // Голубой
    {100, 100, 100} // Белый
};
#define DISCO_COLORS_COUNT 7

static uint8_t breath_target_r = 0, breath_target_g = 0, breath_target_b = 0;

void RGBLEDType_SetColor(uint8_t r, uint8_t g, uint8_t b)
{
    current_color.r = r;
    current_color.g = g;
    current_color.b = b;
    
    Timer32_1_Set_OCR(PWM_CH_R, (PWM_PERIOD_TICKS / 100) * r);
    Timer32_1_Set_OCR(PWM_CH_G, (PWM_PERIOD_TICKS / 100) * g);
    Timer32_1_Set_OCR(PWM_CH_B, (PWM_PERIOD_TICKS / 100) * b);
}

void RGBLEDType_Init(void)
{
    current_color.r = 0;
    current_color.g = 0;
    current_color.b = 0;
    current_mode = RGB_MODE_STATIC;
    effect_counter = 0;
    effect_state = 0;
    breath_value = 0;
    breath_dir = 1;
    breath_target_r = 0;
    breath_target_g = 0;
    breath_target_b = 0;
    RGBLEDType_SetColor(0, 0, 0);
}

void RGBLEDType_SetMode(RGB_Mode_TypeDef mode)
{
    current_mode = mode;
    effect_counter = 0;
    effect_state = 0;
    breath_value = 0;
    breath_dir = 1;
    
    // Для режима дыхания сохраняем целевой цвет
    if (mode == RGB_MODE_BREATH) {
        breath_target_r = current_color.r;
        breath_target_g = current_color.g;
        breath_target_b = current_color.b;
    }
}


void RGBLEDType_UpdateEffect(void)
{
    effect_counter++;
    
    switch (current_mode) {
        case RGB_MODE_STATIC:
            // Ничего не делаем
            break; 
        case RGB_MODE_SMOOTH:
            // Плавное переливание (полный цикл ~10 секунд)
            {
                uint8_t val = (effect_counter * 2) % 255;
                if (val < 85) {
                    RGBLEDType_SetColor(100, val * 100 / 85, 0);
                } else if (val < 170) {
                    RGBLEDType_SetColor(100 - (val - 85) * 100 / 85, 100, 0);
                } else {
                    RGBLEDType_SetColor(0, 100 - (val - 170) * 100 / 85, 100);
                }
            }
            break;
            
        case RGB_MODE_DISCO:
            // Дискотека: смена цвета каждые 300 мс (6 тиков)
            if (effect_counter % 6 == 0) {
                static uint8_t disco_idx = 0;
                disco_idx = (disco_idx + 1) % DISCO_COLORS_COUNT;
                RGBLEDType_SetColor(disco_colors[disco_idx][0],
                                    disco_colors[disco_idx][1],
                                    disco_colors[disco_idx][2]);
            }
            break;
        case RGB_MODE_BREATH:
            // Дыхание: плавное изменение яркости
            if (effect_counter % 2 == 0) {
                if (breath_dir) {
                    breath_value += 5;
                    if (breath_value >= 100) {
                        breath_value = 100;
                        breath_dir = 0;
                    }
                } else {
                    breath_value -= 5;
                    if (breath_value <= 0) {
                        breath_value = 0;
                        breath_dir = 1;
                    }
                }
                RGBLEDType_SetColor(
                    breath_target_r * breath_value / 100,
                    breath_target_g * breath_value / 100,
                    breath_target_b * breath_value / 100
                );
            }
            break;
            
        case RGB_MODE_RAINBOW:
            {
                uint8_t hue = effect_counter % 360;
                uint8_t r, g, b;
                if (hue < 120) {
                    if (hue < 60) {
                        r = 100;
                        g = (hue * 100) / 60;
                        b = 0;
                    } else {
                        r = 100 - ((hue - 60) * 100) / 60;
                        g = 100;
                        b = 0;
                    }
                } else if (hue < 240) {
                    hue -= 120;
                    if (hue < 60) {
                        r = 0;
                        g = 100;
                        b = (hue * 100) / 60;
                    } else {
                        r = 0;
                        g = 100 - ((hue - 60) * 100) / 60;
                        b = 100;
                    }
                } else {
                    hue -= 240;
                    if (hue < 60) {
                        r = (hue * 100) / 60;
                        g = 0;
                        b = 100;
                    } else {
                        r = 100;
                        g = 0;
                        b = 100 - ((hue - 60) * 100) / 60;
                    }
                }
                RGBLEDType_SetColor(r, g, b);
            }
            break;
        case RGB_MODE_PULSE:
            {
                int angle = (effect_counter * 15) % 180;
                if (angle < 60) {
                    int val = (angle * 100) / 60;
                    RGBLEDType_SetColor(0, val / 2, 100);
                } else if (angle < 120) {
                    int val = 100 - ((angle - 60) * 100) / 60;
                    RGBLEDType_SetColor(0, val / 2, 100);
                } else {
                    int val = 100 - ((angle - 120) * 100) / 60;
                    RGBLEDType_SetColor(0, 0, val);
                }
            }
            break;
        default: break;
    }
}

void RGBLEDType_Block_Voice(uint32_t ms) {
    uint8_t saved_r = current_color.r;
    uint8_t saved_g = current_color.g;
    uint8_t saved_b = current_color.b;
    RGB_Mode_TypeDef saved_mode = current_mode;
    RGBLEDType_SetMode(RGB_MODE_PULSE);
    delay_ms(ms);
    RGBLEDType_SetMode(saved_mode);
    RGBLEDType_SetColor(saved_r, saved_g, saved_b);
}