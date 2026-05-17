#ifndef DFPLAYER_MINI
#define DFPLAYER_MINI

#include "bsp/usart.h"

//              1        2       3      4        5       6      7       8         9        10
// Format: START_BYTE VERSION LENGTH COMMAND FEEDBACK PARAM1 PARAM2 CHECKSUM1 CHECKSUM2 END_BYTE

#define START_BYTE   0x7E
#define VERSION      0xFF
#define LENGTH       0x06
#define NO_ASK       0x00       // FEEDBACK
#define END_BYTE     0xEF

#define BAUDRATE     9600

typedef struct {
    uint8_t volume;
    USART_HandleTypeDef* huart;
} DFPlayer_HandleTypeDef;

static uint8_t DFPlayer_SendCmd(DFPlayer_HandleTypeDef* dfplayer, uint8_t cmd, uint16_t prm);

uint8_t DFPlayer_Init(DFPlayer_HandleTypeDef* dfplayer, USART_HandleTypeDef* huart);
uint8_t DFPlayer_PlayTrack(DFPlayer_HandleTypeDef* dfplayer, uint16_t track);
uint8_t DFPlayer_SetPath(DFPlayer_HandleTypeDef* dfplayer, uint8_t path);
uint8_t DFPlayer_SetVolume(DFPlayer_HandleTypeDef* dfplayer, uint8_t volume);
uint8_t DFPlayer_Pause(DFPlayer_HandleTypeDef* dfplayer);
uint8_t DFPlayer_Play(DFPlayer_HandleTypeDef* dfplayer);
uint8_t DFPlayer_SetPlaybackMode(DFPlayer_HandleTypeDef* dfplayer, uint8_t mode);

#endif