#ifndef RGB_LED_TYPE
#define RGB_LED_TYPE
#include "bsp/timer_config.h"

#define SYSTEM_FREQ_HZ 32000000UL
#define PWM_FREQ_HZ (1000)
#define PWM_PERIOD_TICKS (SYSTEM_FREQ_HZ / PWM_FREQ_HZ)

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} CurrentColor_TypeDef;

typedef enum {
    RGB_MODE_STATIC = 0,        // Статический цвет
    RGB_MODE_SMOOTH,            // Плавное переливание
    RGB_MODE_DISCO,             // Дискотека (смена цветов)
    RGB_MODE_BREATH,            // Дыхание
    RGB_MODE_RAINBOW,           // Радуга
    RGB_MODE_PULSE,             // Для голоса
} RGB_Mode_TypeDef;

extern CurrentColor_TypeDef current_color;

void RGBLEDType_Init();
void RGBLEDType_SetColor(uint8_t r, uint8_t g, uint8_t b);

void RGBLEDType_SetMode(RGB_Mode_TypeDef mode);
void RGBLEDType_UpdateEffect(void);

void RGBLEDType_Block_Voice(uint32_t ms);
#endif // RGB_LED_TYPE