#include "usart.h"

USART_HandleTypeDef husart0 = {0};
USART_HandleTypeDef husart1 = {0};

void USART_Init(void)
{
    husart0.Instance = UART_0;
    husart0.transmitting = Enable;
    husart0.receiving = Enable;
    husart0.baudrate = 9600;

    HAL_USART_Init(&husart0);

    husart1.Instance = UART_1;
    husart1.transmitting = Enable;
    husart1.receiving = Enable;
    husart1.baudrate = 9600;

    HAL_USART_Init(&husart1);
}