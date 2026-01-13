#include "lcd1602.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

lcd::LCD lcd_mode(GPIO_NUM_4, GPIO_NUM_14,
                  GPIO_NUM_25, GPIO_NUM_26,
                  GPIO_NUM_32, GPIO_NUM_33);

extern "C" void app_main()
{
    lcd_mode.lcd_init();
    lcd_mode.lcd_set_cursor(0, 3);
    lcd_mode.lcd_print("Hello World");
}
