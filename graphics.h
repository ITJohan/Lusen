#include <stdint.h>

static void graphic_ctrl_bit_set(uint8_t x);
static void graphic_ctrl_bit_clear(uint8_t x);
static void select_controller(uint8_t controller);
static void graphic_wait_ready(void);
static uint8_t graphic_read(uint8_t controller);
static uint8_t graphic_read_data(uint8_t controller);
static void graphic_write(uint8_t value, uint8_t controller);
static void graphic_write_command(uint8_t command, uint8_t controller);
static void graphic_write_data(uint8_t data, uint8_t controller);
void graphic_clear_screen(void);
void graphic_initialize(void);
void pixel(int x, int y, int set);