#include "bsp/pinmux.h"
#include "bsp/timer_config.h"
#include "bsp/usart.h"
#include "bsp/interrupt.h"
#include "bsp/clock.h"

#include "drivers/dht11_driver.h"
#include "drivers/dfplayer_driver.h"
#include "drivers/rgb_led_type_driver.h"
#include "drivers/DFRobot_DF2301Q_driver.h"

static DFPlayer_HandleTypeDef dfplayer0;
static DHT11_Data_TypeDef dht11;

void EPIC_trap_handler(void);
void AMUR(void);

int main(void)
{
    // Board Support Package Init
    SystemClock_Config();
    Pinmux_Init();
    Timer_Init();
    USART_Init();
    Interrupt_Init();

    // Drivers Init
    DFPlayer_Init(&dfplayer0, &husart0);
    delay_ms(6000);
    RGBLEDType_Init();
    DF2301Q_Init(&husart1);

    // Main Loop
    AMUR();
}

void EPIC_trap_handler(void)
{
    if (EPIC->RAW_STATUS & (1 << EPIC_LINE_TIMER32_2_S)) {
        TIMER32_2->INT_CLEAR = TIMER32_INT_OVERFLOW_M;
        EPIC->CLEAR = EPIC_LINE_TIMER32_2_S;
        RGBLEDType_UpdateEffect();
    }
}

void AMUR(void) {
    RGBLEDType_SetMode(RGB_MODE_STATIC);
    RGBLEDType_SetColor(50, 50, 50);

    while (1) {
        uint8_t cmd = DF2301Q_GetCommandId();
        
        switch (cmd) {
        case 103: // Turn on the light
        case 5: // Включи свет
            RGBLEDType_SetMode(RGB_MODE_STATIC);
            RGBLEDType_SetColor(100, 100, 100);
            DFPlayer_PlayTrack(&dfplayer0, 40);
            RGBLEDType_Block_Voice(700);
            break;
        case 104: // Turn off the light
        case 6: // Выключи
            RGBLEDType_SetMode(RGB_MODE_STATIC);
            RGBLEDType_SetColor(0, 0, 0);
            DFPlayer_PlayTrack(&dfplayer0, 39);
            RGBLEDType_Block_Voice(700);
            break;
        case 119: // Set to green
        case 7: // Зеленый свет
            RGBLEDType_SetMode(RGB_MODE_STATIC);
            RGBLEDType_SetColor(0, 100, 0);
            DFPlayer_PlayTrack(&dfplayer0, 40);
            RGBLEDType_Block_Voice(700);
            break;
        case 117: // Set to orange
            RGBLEDType_SetMode(RGB_MODE_STATIC);
            RGBLEDType_SetColor(100, 50, 0);
            DFPlayer_PlayTrack(&dfplayer0, 40);
            RGBLEDType_Block_Voice(700);
            break;
        case 118: // Set to yellow 
            RGBLEDType_SetMode(RGB_MODE_STATIC);
            RGBLEDType_SetColor(100, 100, 0);
            DFPlayer_PlayTrack(&dfplayer0, 40);
            RGBLEDType_Block_Voice(700);
            break;
        case 121: // Set to blue 
        case 8: // Синий свет
            RGBLEDType_SetMode(RGB_MODE_STATIC);
            RGBLEDType_SetColor(0, 0, 100);
            DFPlayer_PlayTrack(&dfplayer0, 39);
            RGBLEDType_Block_Voice(700);
            break;
        case 116: // Set to red
        case 9: // Красный свет
            RGBLEDType_SetMode(RGB_MODE_STATIC);
            RGBLEDType_SetColor(100, 0, 0);
            DFPlayer_PlayTrack(&dfplayer0, 39);
            RGBLEDType_Block_Voice(700);
            break;
        case 114: // Moonlight mode
        case 10: // Режим ночник
            DFPlayer_PlayTrack(&dfplayer0, 39);
            RGBLEDType_Block_Voice(700);
            RGBLEDType_SetColor(100, 70, 20);
            RGBLEDType_SetMode(RGB_MODE_BREATH);
            break;
        case 115: // Color mode
            DFPlayer_PlayTrack(&dfplayer0, 39);
            RGBLEDType_Block_Voice(700);
            RGBLEDType_SetMode(RGB_MODE_SMOOTH);
            break;
        case 62: // Display smiley face
            DFPlayer_PlayTrack(&dfplayer0, 39);
            RGBLEDType_Block_Voice(700);
            RGBLEDType_SetMode(RGB_MODE_DISCO);
            break;
        case 11: // Какая температура 
        case 69: // read temperature
            uint8_t bad = DHT11_ReadData(&dht11);
            if (bad != 0) {
                RGBLEDType_SetMode(RGB_MODE_STATIC);
                RGBLEDType_SetColor(100, 0, 0);
                break;
            }
            DFPlayer_PlayTrack(&dfplayer0, dht11.temperature_int + 1);
            RGBLEDType_Block_Voice(2500);
            break;
        case 12: // Какая влажность
            uint8_t bad2 = DHT11_ReadData(&dht11);
            if (bad2 != 0 ) {
                RGBLEDType_SetColor(100, 0, 0); break;
            }
            DFPlayer_PlayTrack(&dfplayer0, 40  + dht11.humidity_int / 10);
            RGBLEDType_Block_Voice(3500);
            break;
        case 2: // Hello, robot
        case 1: // Привет, Амур
            DFPlayer_PlayTrack(&dfplayer0, 37);
            RGBLEDType_Block_Voice(1200);
            break;
        default: break;
        }
        
        delay_ms(10);
    }
}