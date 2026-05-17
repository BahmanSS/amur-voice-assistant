#ifndef DFRobot_DF2301Q_H
#define DFRobot_DF2301Q_H

#include "bsp/usart.h"

#define DF2301Q_I2C_ADDR (0x64)

#define DF2301Q_REG_CMDID        0x02    // Чтение ID команды
#define DF2301Q_REG_MUTE         0x04    // Установка mute (1 - mute, 0 - unmute)
#define DF2301Q_REG_VOLUME       0x05    // Громкость (1-7)
#define DF2301Q_REG_WAKE_TIME    0x06    // Время пробуждения (0-255 сек)

uint8_t DF2301Q_Init(USART_HandleTypeDef *husart1);
uint8_t DF2301Q_GetCommandId(void);
// void DF2301Q_SetVolume(uint8_t volume);
// void DF2301Q_SetMuteMode(uint8_t mute);
// void DF2301Q_SetWakeTime(uint8_t seconds);

#endif // DFRobot_DF2301Q_H