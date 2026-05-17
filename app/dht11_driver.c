#include "dht11_driver.h"

uint8_t DHT11_ReadData(DHT11_Data_TypeDef *data) {
    uint8_t bytes[5] = {0};
    
    DHT11_PIN_PORT->DIRECTION_OUT = (1 << DHT11_PIN_NUM);
    DHT11_PIN_PORT->SET = (1 << DHT11_PIN_NUM);
    delay_us(1000);  // Небольшая пауза для стабилизации

    DHT11_PIN_PORT->CLEAR = (1 << DHT11_PIN_NUM);
    delay_us(190000);
    DHT11_PIN_PORT->DIRECTION_IN = (1 << DHT11_PIN_NUM);
    if ((DHT11_PIN_PORT->STATE & (1 << DHT11_PIN_NUM)) == 0) { return 1; }
    delay_us(20);
    if ((DHT11_PIN_PORT->STATE & (1 << DHT11_PIN_NUM)) != 0) { return 2; }
    delay_us(50);
    if ((DHT11_PIN_PORT->STATE & (1 << DHT11_PIN_NUM)) == 0) { return 3; }

    while ((DHT11_PIN_PORT->STATE & (1 << DHT11_PIN_NUM)) != 0);
    

    // чтение пяти 8-битных данных
    for(uint8_t i = 0; i < 5; ++i) {
		bytes[i] = 0;
		for(uint8_t j = 0; j < 8; j++) {
            
			while ((DHT11_PIN_PORT->STATE & (1 << DHT11_PIN_NUM)) == 0);
            
            
			delay_us(7);
			if((DHT11_PIN_PORT->STATE & (1 << DHT11_PIN_NUM)) != 0) {
                bytes[i] = bytes[i] | (1 << (7 - j));
            }
            
			while((DHT11_PIN_PORT->STATE & (1 << DHT11_PIN_NUM)) != 0);
            
		}
	}
    

    uint8_t checksum = bytes[0] + bytes[1] + bytes[2] + bytes[3];

    if (checksum != bytes[4]) { return 4; }

    data->humidity_int = bytes[0];
    data->humidity_dec = bytes[1];
    data->temperature_int = bytes[2];
    data->temperature_dec = bytes[3];

    return 0;
}

void delay_us(uint32_t us) {
    uint64_t end_mtimer = SCR1_TIMER_GET_TIME() + (SYSTEM_FREQ_HZ / 1000000UL * us);
    while (SCR1_TIMER_GET_TIME() < end_mtimer)
        ;
}