#ifndef DHT11_DRIVER
#define DHT11_DRIVER

#include "gpio.h"
#include "mik32_memory_map.h"
#include "scr1_timer.h"

// D11
#define DHT11_PIN_PORT GPIO_1
#define DHT11_PIN_NUM (1)

#define SCR1_TIMER_GET_TIME()                                                   \
  (((uint64_t)(SCR1_TIMER->MTIMEH) << 32) | (SCR1_TIMER->MTIME))

#define SYSTEM_FREQ_HZ 32000000UL


typedef struct {
    uint8_t humidity_int;      // Целая часть влажности
    uint8_t humidity_dec;      // Дробная часть влажности
    uint8_t temperature_int;   // Целая часть температуры
    uint8_t temperature_dec;   // Дробная часть температуры
} DHT11_Data_TypeDef;

void delay_us(uint32_t us);
uint8_t DHT11_ReadData(DHT11_Data_TypeDef *data);

#endif /* DHT11_DRIVER */