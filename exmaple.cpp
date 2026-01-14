#include "lcd1602.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

lcd::LCD::lcd_pins lcdPins = {
    .pin_rs = GPIO_NUM_21,
    .pin_en = GPIO_NUM_22,
    .pin_d4 = GPIO_NUM_18,
    .pin_d5 = GPIO_NUM_19,
    .pin_d6 = GPIO_NUM_23,
    .pin_d7 = GPIO_NUM_5
};


extern "C" void app_main()
{
    lcd_mode.lcd_init();
    lcd_mode.lcd_set_cursor(0, 3);
    lcd_mode.lcd_print("Hello World");
}
