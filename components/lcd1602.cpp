#include "lcd1602.h"

void lcd::LCD::lcd_init()
{
    vTaskDelay(pdMS_TO_TICKS(500));
    gpio_reset_pin(pins.pin_rs);
    gpio_reset_pin(pins.pin_en);
    gpio_reset_pin(pins.pin_d4);
    gpio_reset_pin(pins.pin_d5);
    gpio_reset_pin(pins.pin_d6);
    gpio_reset_pin(pins.pin_d7);

    gpio_set_direction(pins.pin_rs, GPIO_MODE_OUTPUT);
    gpio_set_direction(pins.pin_en, GPIO_MODE_OUTPUT);
    gpio_set_direction(pins.pin_d4, GPIO_MODE_OUTPUT);
    gpio_set_direction(pins.pin_d5, GPIO_MODE_OUTPUT);
    gpio_set_direction(pins.pin_d6, GPIO_MODE_OUTPUT);
    gpio_set_direction(pins.pin_d7, GPIO_MODE_OUTPUT);

    sendBit(0, 0x3);
    vTaskDelay(pdMS_TO_TICKS(5));
    sendBit(0, 0x3);
    vTaskDelay(pdMS_TO_TICKS(5));
    sendBit(0, 0x3);
    vTaskDelay(pdMS_TO_TICKS(5));
    sendBit(0, 0x2);
    vTaskDelay(pdMS_TO_TICKS(5));

    sendByte(0, 0x28);
    vTaskDelay(pdMS_TO_TICKS(2));
    sendByte(0, 0x0c);
    vTaskDelay(pdMS_TO_TICKS(2));
    sendByte(0, 0x06);
    vTaskDelay(pdMS_TO_TICKS(2));
    sendByte(0, 0x01);
    vTaskDelay(pdMS_TO_TICKS(10));
}

void lcd::LCD::lcd_clear()
{
    sendByte(0, 0x01);
    esp_rom_delay_us(1);
}

void lcd::LCD::lcd_print(const char *data)
{
    while (*data)
    {
        sendByte(1, *data++);
    }
}

void lcd::LCD::lcd_set_cursor(uint8_t r, uint8_t c)
{
    uint8_t num[] = {0x00, 0x40};
    sendByte(0, 0x80 + num[r] + c);
}
