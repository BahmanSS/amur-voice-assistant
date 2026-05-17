#include "pinmux.h"

void Pinmux_Init(void)
{
    // Включить  тактирование GPIO_0 и GPIO_1
    PM->CLK_APB_P_SET |= PM_CLOCK_APB_P_GPIO_0_M;
    PM->CLK_APB_P_SET |= PM_CLOCK_APB_P_GPIO_1_M;

    // ===== RGB LED =====
    SET_TWO_BIT(PAD_CONFIG->PORT_0_CFG, RGB_R_PIN, 2);      // Настройка пинов в режим таймера (функция 2)
    SET_TWO_BIT(PAD_CONFIG->PORT_0_CFG, RGB_G_PIN, 2);
    SET_TWO_BIT(PAD_CONFIG->PORT_0_CFG, RGB_B_PIN, 2);
    SET_TWO_BIT(PAD_CONFIG->PORT_0_DS, RGB_R_PIN, 0);       // Нагрузочная способность 2 мА
    SET_TWO_BIT(PAD_CONFIG->PORT_0_DS, RGB_G_PIN, 0);
    SET_TWO_BIT(PAD_CONFIG->PORT_0_DS, RGB_B_PIN, 0);
    SET_TWO_BIT(PAD_CONFIG->PORT_0_PUPD, RGB_R_PIN, 0);     // Подтяжка отключена
    SET_TWO_BIT(PAD_CONFIG->PORT_0_PUPD, RGB_G_PIN, 0);
    SET_TWO_BIT(PAD_CONFIG->PORT_0_PUPD, RGB_B_PIN, 0);

    // ===== DHT11 =====
    SET_TWO_BIT(PAD_CONFIG->PORT_1_CFG, DHT11_PIN, 0);      // первая функция (порт общего назначения)
    SET_TWO_BIT(PAD_CONFIG->PORT_1_PUPD, DHT11_PIN, 0);     // Подтяжка отключена
    DHT11_PORT->DIRECTION_OUT = (1 << DHT11_PIN);           // Настроить пин как ВЫХОД
    DHT11_PORT->SET = (1 << DHT11_PIN);                     // Установить высокий уровень

    // ===== DFPlayer =====
    SET_TWO_BIT(PAD_CONFIG->PORT_0_CFG, DFPLAYER_TX_PIN, 1); // вторая функция (последовательный интерфейс)
    SET_TWO_BIT(PAD_CONFIG->PORT_0_CFG, DFPLAYER_RX_PIN, 1);

    // ===== DF2301Q =====
    SET_TWO_BIT(PAD_CONFIG->PORT_1_CFG, DF2301Q_SDA_PIN, 1); // вторая функция (последовательный интерфейс)
    SET_TWO_BIT(PAD_CONFIG->PORT_1_CFG, DF2301Q_SCL_PIN, 1); 
}