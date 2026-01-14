#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

namespace lcd
{
    class LCD
    {
    private:
        typedef struct {
            gpio_num_t pin_rs;
            gpio_num_t pin_en;
            gpio_num_t pin_d4;
            gpio_num_t pin_d5;
            gpio_num_t pin_d6;
            gpio_num_t pin_d7;
        } lcd_pins;

        lcd_pins pins;
        void pulse_en()
        {
            gpio_set_level(pins.pin_en, 1);
            esp_rom_delay_us(5);
            gpio_set_level(pins.pin_en, 0);
            esp_rom_delay_us(50);
        }
        void sendBit(uint8_t rs_state, uint8_t data)
        {
            gpio_set_level(pins.pin_rs, rs_state);

            gpio_set_level(pins.pin_d4, (data >> 0) & 0x01);
            gpio_set_level(pins.pin_d5, (data >> 1) & 0x01);
            gpio_set_level(pins.pin_d6, (data >> 2) & 0x01);
            gpio_set_level(pins.pin_d7, (data >> 3) & 0x01);

            pulse_en();
        }

        void sendByte(uint8_t rs_state, uint8_t data)
        {
            sendBit(rs_state, data >> 4);
            sendBit(rs_state, data & 0x0f);
        }

    public:
        LCD(const lcd_pins &p) : pins(p) {};
        void lcd_init();
        void lcd_clear();

        void lcd_print(const char *data);
        void lcd_set_cursor(uint8_t r, uint8_t c);
    };
};
