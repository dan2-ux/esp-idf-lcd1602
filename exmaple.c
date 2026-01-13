#include "lcd1602.h"

void app_main(void) {
    // 1️⃣ Set your pins once
    lcd_set_pins(GPIO_NUM_4, GPIO_NUM_5, GPIO_NUM_18, GPIO_NUM_19, GPIO_NUM_21, GPIO_NUM_22);

    // 2️⃣ Initialize LCD
    lcd_init();

    // 3️⃣ Use it freely without passing pins
    lcd_print("Hello, ESP32!");
    lcd_set_cursor(1, 0);
    lcd_print("LCD1602 Test");

    vTaskDelay(pdMS_TO_TICKS(2000));
    lcd_clear();
}
