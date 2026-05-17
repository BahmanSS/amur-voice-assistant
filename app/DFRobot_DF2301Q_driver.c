#include "DFRobot_DF2301Q_driver.h"

static USART_HandleTypeDef* df2301q_husart = NULL;

uint8_t DF2301Q_Init(USART_HandleTypeDef *husart1)
{
    df2301q_husart = husart1;
    return 0;
}

uint8_t DF2301Q_GetCommandId(void)
{
    if (df2301q_husart == NULL) return 1;

    uint8_t buffer[32];
    uint8_t buffer_index = 0;
    uint8_t byte = 0;
        
    do {
        if (HAL_USART_Receive(df2301q_husart, (char*)&byte, 100) != true) {
            continue;
        }
    } while (byte != 0xF4);
    
    buffer[0] = byte;
    
    buffer_index = 1;
    for (int i = 1; i < 10; i++) {
        if (HAL_USART_Receive(df2301q_husart, (char*)&buffer[i], 100) != true) {
            buffer_index = 0;
            break;
        }
        buffer_index++;
    }
    return buffer[7];
}
