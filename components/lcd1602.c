#include "lcd1602.h"

// ====== INTERNAL STATIC VARIABLES ======
typedef struct {
    gpio_num_t rs;
    gpio_num_t en;
    gpio_num_t d4;
    gpio_num_t d5;
    gpio_num_t d6;
    gpio_num_t d7;
} lcd_pins_t;

static lcd_pins_t lcdPins;      // store user-provided pins internally
static int lcd_initialized = 0; // ensure init before printing
static int lcd_pins_set = 0;    // ensure pins are set before init

// ====== INTERNAL FUNCTIONS ======
static void pulse_enable() {
    gpio_set_level(lcdPins.en, 1);
    vTaskDelay(pdMS_TO_TICKS(1));
    gpio_set_level(lcdPins.en, 0);
    vTaskDelay(pdMS_TO_TICKS(1));
}

static void sendBit(uint8_t rs_state, uint8_t data) {
    gpio_set_level(lcdPins.rs, rs_state);
    gpio_set_level(lcdPins.d4, (data >> 0) & 1);
    gpio_set_level(lcdPins.d5, (data >> 1) & 1);
    gpio_set_level(lcdPins.d6, (data >> 2) & 1);
    gpio_set_level(lcdPins.d7, (data >> 3) & 1);
    pulse_enable();
}

static void sendByte(uint8_t rs_state, uint8_t data) {
    sendBit(rs_state, data >> 4);   // high nibble
    sendBit(rs_state, data & 0x0F); // low nibble
}

void lcd_init(void) {
    lcdPins.rs = rs;
    lcdPins.en = en;
    lcdPins.d4 = d4;
    lcdPins.d5 = d5;
    lcdPins.d6 = d6;
    lcdPins.d7 = d7;
    lcd_pins_set = 1;
    if (!lcd_pins_set) return; // safety: ensure pins are set

    // Reset and configure pins
    gpio_reset_pin(lcdPins.rs);
    gpio_reset_pin(lcdPins.en);
    gpio_reset_pin(lcdPins.d4);
    gpio_reset_pin(lcdPins.d5);
    gpio_reset_pin(lcdPins.d6);
    gpio_reset_pin(lcdPins.d7);

    gpio_set_direction(lcdPins.rs, GPIO_MODE_OUTPUT);
    gpio_set_direction(lcdPins.en, GPIO_MODE_OUTPUT);
    gpio_set_direction(lcdPins.d4, GPIO_MODE_OUTPUT);
    gpio_set_direction(lcdPins.d5, GPIO_MODE_OUTPUT);
    gpio_set_direction(lcdPins.d6, GPIO_MODE_OUTPUT);
    gpio_set_direction(lcdPins.d7, GPIO_MODE_OUTPUT);

    vTaskDelay(pdMS_TO_TICKS(50));

    // Initialization sequence
    sendBit(0, 0x3);
    vTaskDelay(pdMS_TO_TICKS(5));
    sendBit(0, 0x3);
    vTaskDelay(pdMS_TO_TICKS(5));
    sendBit(0, 0x3);
    vTaskDelay(pdMS_TO_TICKS(5));
    sendBit(0, 0x2); // 4-bit mode
    vTaskDelay(pdMS_TO_TICKS(5));

    sendByte(0, 0x28); // Function set
    sendByte(0, 0x0C); // Display ON
    sendByte(0, 0x06); // Entry mode set
    sendByte(0, 0x01); // Clear display
    vTaskDelay(pdMS_TO_TICKS(5));

    lcd_initialized = 1;
}

void lcd_print(const char* data) {
    if (!lcd_initialized) return;
    while (*data) {
        sendByte(1, *data++);
    }
}

void lcd_set_cursor(uint8_t row, uint8_t col) {
    if (!lcd_initialized) return;
    uint8_t addr = (row == 0) ? 0x80 + col : 0x80 + 0x40 + col;
    sendByte(0, addr);
}

void lcd_clear(void) {
    if (!lcd_initialized) return;
    sendByte(0, 0x01);
    vTaskDelay(pdMS_TO_TICKS(5));
}
