#include "dfplayer_driver.h"

uint8_t DFPlayer_SendCmd(DFPlayer_HandleTypeDef* dfplayer, uint8_t cmd, uint16_t prm) {
    uint8_t tx_buffer[10];
    uint8_t rx_buffer[10];

    tx_buffer[0] = START_BYTE;
    tx_buffer[1] = VERSION;
    tx_buffer[2] = LENGTH;
    tx_buffer[3] = cmd;
    tx_buffer[4] = NO_ASK;
    tx_buffer[5] = (prm >> 8) & 0xFF;
    tx_buffer[6] = prm & 0xFF;
    tx_buffer[7] = END_BYTE;

    for (uint8_t i = 0; i < 8; ++i) {
        HAL_USART_Transmit(dfplayer->huart, tx_buffer[i], USART_TIMEOUT_DEFAULT);
    }
    
    return 0;
}

uint8_t DFPlayer_Init(DFPlayer_HandleTypeDef *dfplayer, USART_HandleTypeDef *huart)
{
    dfplayer->huart = huart;
    dfplayer->huart->baudrate = BAUDRATE;
    return 0;
}

uint8_t DFPlayer_PlayTrack(DFPlayer_HandleTypeDef *dfplayer, uint16_t track)
{
    if (track > 2999) {
        track = 2999;
    }
    return DFPlayer_SendCmd(dfplayer, 0x03, track);
}

uint8_t DFPlayer_SetPath(DFPlayer_HandleTypeDef *dfplayer, uint8_t path)
{
    if (path > 10) {
        path = 10;
    }
    return DFPlayer_SendCmd(dfplayer, 0x0F, path << 8);
}

uint8_t DFPlayer_SetVolume(DFPlayer_HandleTypeDef *dfplayer, uint8_t volume)
{
    if (volume > 30) {
        volume = 30;
    }
    dfplayer->volume = volume;
    return DFPlayer_SendCmd(dfplayer, 0x06, volume);
}

uint8_t DFPlayer_Pause(DFPlayer_HandleTypeDef *dfplayer)
{
    return DFPlayer_SendCmd(dfplayer, 0x0E, 0);
}

uint8_t DFPlayer_Play(DFPlayer_HandleTypeDef *dfplayer)
{
    return DFPlayer_SendCmd(dfplayer, 0x0D, 0);
}

uint8_t DFPlayer_SetPlaybackMode(DFPlayer_HandleTypeDef *dfplayer, uint8_t mode)
{
    if (mode > 3) {
        mode = 0;
    }
    return DFPlayer_SendCmd(dfplayer, 0x08, mode);
}

