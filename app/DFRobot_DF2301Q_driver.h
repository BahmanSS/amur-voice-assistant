#ifndef DFRobot_DF2301Q_H
#define DFRobot_DF2301Q_H

#include "bsp/usart.h"

uint8_t DF2301Q_Init(USART_HandleTypeDef *husart1);
uint8_t DF2301Q_GetCommandId(void);

#endif // DFRobot_DF2301Q_H