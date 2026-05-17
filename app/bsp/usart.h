#ifndef USART_H
#define USART_H

#include "mik32_hal_usart.h"

extern USART_HandleTypeDef husart0; // dfplayer 
extern USART_HandleTypeDef husart1; // dfrobor df2301q

void USART_Init(void);

#endif // USART_H