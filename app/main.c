#include "bsp/pinmux.h"
#include "bsp/timer_config.h"
#include "bsp/usart.h"

#include "dht11_driver.h"
#include "dfplayer_driver.h"
#include "rgb_led_type_driver.h"
#include "DFRobot_DF2301Q_driver.h"

#define MS_TO_TICKS(ms)                                                         \
  ((SYSTEM_FREQ_HZ / 1000) * (ms))

static DFPlayer_HandleTypeDef dfplayer0;
static DHT11_Data_TypeDef dht11;

static void SystemClock_Config(void)
{
    PCC_InitTypeDef PCC_OscInit = {0};

    PCC_OscInit.OscillatorEnable = PCC_OSCILLATORTYPE_ALL;
    PCC_OscInit.FreqMon.OscillatorSystem = PCC_OSCILLATORTYPE_OSC32M;
    PCC_OscInit.FreqMon.Force32KClk = PCC_FREQ_MONITOR_SOURCE_OSC32K;
    PCC_OscInit.HSI32MCalibrationValue = 128;
    PCC_OscInit.LSI32KCalibrationValue = 8;
    HAL_PCC_Config(&PCC_OscInit);
}

void delay_ms(uint32_t ms) {
   uint64_t end_mtimer = SCR1_TIMER_GET_TIME() + MS_TO_TICKS(ms);
   while (SCR1_TIMER_GET_TIME() < end_mtimer)
     ;
}

int main(void)
{
    SystemClock_Config();
    Pinmux_Init();
    Timer_Init();
    USART_Init();

    DFPlayer_Init(&dfplayer0, &husart0);
    delay_ms(6000);
    RGBLEDType_Init();
    DF2301Q_Init(&husart1);

    while (1) {
        uint8_t cmd = DF2301Q_GetCommandId();

        switch (cmd) {
        case 0x74: RGBLEDType_SetColor(100, 0, 0); break;
        case 0x79: RGBLEDType_SetColor(0, 0, 100); break;
        case 0x77: RGBLEDType_SetColor(0, 100, 0); break;
        case 103: RGBLEDType_SetColor(100, 100, 100); break;
        case 104: RGBLEDType_SetColor(0, 0, 0); break;
        case 69: 
            uint8_t bad = DHT11_ReadData(&dht11);
            DFPlayer_PlayTrack(&dfplayer0, dht11.temperature_int + 2);
            break;
        default: break;
        }
        
        delay_ms(10);
    }
}