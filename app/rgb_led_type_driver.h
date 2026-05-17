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

extern CurrentColor_TypeDef current_color;

void RGBLEDType_Init();
void RGBLEDType_SetColor(uint8_t r, uint8_t g, uint8_t b);
void RGBLEDType_RainbowEffect(uint32_t duration_ms);

#endif // RGB_LED_TYPE