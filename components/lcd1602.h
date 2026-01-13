#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

namespace lcd
{
    class LCD
    {
    private:
        gpio_num_t pin_rs;
        gpio_num_t pin_en;
        gpio_num_t pin_d4;
        gpio_num_t pin_d5;
        gpio_num_t pin_d6;
        gpio_num_t pin_d7;
        void pulse_en()
        {
            gpio_set_level(pin_en, 1);
            esp_rom_delay_us(5);
            gpio_set_level(pin_en, 0);
            esp_rom_delay_us(50);
        }
        void sendBit(uint8_t rs_state, uint8_t data)
        {
            gpio_set_level(pin_rs, rs_state);

            gpio_set_level(pin_d4, (data >> 0) & 0x01);
            gpio_set_level(pin_d5, (data >> 1) & 0x01);
            gpio_set_level(pin_d6, (data >> 2) & 0x01);
            gpio_set_level(pin_d7, (data >> 3) & 0x01);

            pulse_en();
        }

        void sendByte(uint8_t rs_state, uint8_t data)
        {
            sendBit(rs_state, data >> 4);
            sendBit(rs_state, data & 0x0f);
        }

    public:
        LCD(gpio_num_t rs, gpio_num_t en,
            gpio_num_t d4, gpio_num_t d5,
            gpio_num_t d6, gpio_num_t d7) : pin_rs(rs), pin_en(en), pin_d4(d4), pin_d5(d5), pin_d6(d6), pin_d7(d7) {};
        void lcd_init();
        void lcd_clear();

        void lcd_print(const char *data);
        void lcd_set_cursor(uint8_t r, uint8_t c);
    };
};
