#pragma once
#include "driver/gpio.h"
#include "esp_rom_sys.h"

void lcd_init(gpio_num_t rs, gpio_num_t en, gpio_num_t d4, gpio_num_t d5, gpio_num_t d6, gpio_num_t d7);

void lcd_print(lcd_pins_t* pin, const char* data);

void lcd_choice_display(lcd_pins_t* pin, uint8_t r, uint8_t c);

void lcd_clear(lcd_pins_t *pins);
