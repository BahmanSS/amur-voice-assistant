#include "bsp/pinmux.h"
#include "bsp/timer_config.h"
#include "bsp/usart.h"

#include "dht11_driver.h"
#include "dfplayer_driver.h"
#include "rgb_led_type_driver.h"
#include "DFRobot_DF2301Q_driver.h"

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
        case 103: // Turn on the light
        case 5:
            // Включи свет
            DFPlayer_PlayTrack(&dfplayer0, 40);
            RGBLEDType_SetColor(100, 100, 100);
            break;
        case 104: // Turn off the light
        case 6:
            // Выключи
            DFPlayer_PlayTrack(&dfplayer0, 39);
            RGBLEDType_SetColor(0, 0, 0);
            break;
        case 0x77: // Set to green
        case 7:
            // Зеленый свет
            DFPlayer_PlayTrack(&dfplayer0, 40);
            RGBLEDType_SetColor(0, 100, 0);
            break;
        case 0x79: // Set to blue 
        case 8:
            // Синий свет
            DFPlayer_PlayTrack(&dfplayer0, 39);
            RGBLEDType_SetColor(0, 0, 100);
            break;
        case 0x74: // Set to red
        case 9:
            // Красный свет
            DFPlayer_PlayTrack(&dfplayer0, 39);
            RGBLEDType_SetColor(100, 0, 0);
            break;
        case 114: // Moonlight mode
        case 10: 
            // Режим ночник
            DFPlayer_PlayTrack(&dfplayer0, 39);
            RGBLEDType_SetColor(60, 45, 10);
            break;
        case 11: // Какая температура 
        case 69:
            // read temperature
            uint8_t bad = DHT11_ReadData(&dht11);
            if (bad != 0) {
                RGBLEDType_SetColor(100, 0, 0); break;
            }
            DFPlayer_PlayTrack(&dfplayer0, dht11.temperature_int + 1);
            RGBLEDType_RainbowEffect(3000);
            break;
        case 12:
            // Какая влажность
            uint8_t bad2 = DHT11_ReadData(&dht11);
            if (bad2 != 0 ) {
                RGBLEDType_SetColor(100, 0, 0); break;
            }
            
            DFPlayer_PlayTrack(&dfplayer0, 40  + dht11.humidity_int / 10);
            RGBLEDType_RainbowEffect(3000);
            break;
        case 2: // Hello, robot
        case 1:
            // Амур
            DFPlayer_PlayTrack(&dfplayer0, 37);
            RGBLEDType_RainbowEffect(700);
            break;
        
        default: break;
        }
        
        delay_ms(10);
    }
}