#include <stdint.h>

void ascii_write_char(uint8_t c);
void ascii_gotoxy(int x, int y);
void ascii_init(void);
void ascii_write_controller(uint8_t c);
unsigned char ascii_read_controller(void);
void ascii_write_cmd(uint8_t command);
unsigned char ascii_read_status(void);
unsigned char ascii_read_data(void);
void ascii_ctrl_bit_set(uint8_t x);
void ascii_ctrl_bit_clear(uint8_t x);