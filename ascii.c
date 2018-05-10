#include <stdint.h>
#include "defines.h"
#include "delays.h"
#include "ascii.h"

void draw_ascii(char msg[]) {
	ascii_gotoxy(1, 1);
	char *s = msg;
	while(*s)
		ascii_write_char(*s++);
}

void ascii_write_char(uint8_t c)
{
	while((ascii_read_status() & 0x80) == 0x80) {}
	delay_micro(8);
	ascii_write_data(c);
	delay_micro(43);
}

void ascii_gotoxy(int x, int y)
{
	unsigned char address = x - 1;
	if(y == 2)
		address += 0x40;
	ascii_write_cmd(0x80 | address);
	delay_micro(43);
}

void ascii_init(void)
{
	while((ascii_read_status() & 0x80) == 0x80) {}	/* vänta tills display är klar att ta emot kommando */
	delay_micro(8);									/* latenstid för kommando */
	ascii_write_cmd(0x38);							/* Function set kommando */
	delay_micro(39);								/* 39us */
	
	while((ascii_read_status() & 0x80) == 0x80) {}	/* vänta tills display är klar att ta emot kommando */
	delay_micro(8);									/* latenstid för kommando */
	ascii_write_cmd(0x0F);							/* Display control kommando */
	delay_micro(39);								/* 39us */
	
	while((ascii_read_status() & 0x80) == 0x80) {}	/* vänta tills display är klar att ta emot kommando */
	delay_micro(8);									/* latenstid för kommando */
	ascii_write_cmd(1);								/* Clear display kommando */
	delay_milli(2);									/* i stället för 1,53 ms */
	
	while((ascii_read_status() & 0x80) == 0x80) {}	/* vänta tills display är klar att ta emot kommando */
	delay_micro(8);									/* latenstid för kommando */
	ascii_write_cmd(0x04);							/* Entry mode set kommando */
	delay_micro(39);								/* 39us */
	
	ascii_gotoxy(1, 1);
	draw_ascii("Lusen");
}

void ascii_write_controller(uint8_t c)
{
	// Delay40ns
	ascii_ctrl_bit_set(B_E);
	GPIO_E->odrHigh = c;
	delay_250ns();
	ascii_ctrl_bit_clear(B_E);
	// Delay10ns
}

unsigned char ascii_read_controller(void)
{
	unsigned char c;
	ascii_ctrl_bit_set(B_E);
	delay_250ns();
	delay_250ns();
	c = GPIO_E->idrHigh;
	ascii_ctrl_bit_clear(B_E);
	return c;
}

void ascii_write_cmd(uint8_t command)
{
	ascii_ctrl_bit_clear(B_RS);
	ascii_ctrl_bit_clear(B_RW);
	ascii_write_controller(command);
}

void ascii_write_data(uint8_t data)
{
	ascii_ctrl_bit_set(B_RS);
	ascii_ctrl_bit_clear(B_RW);
	ascii_write_controller(data);
}

unsigned char ascii_read_status(void)
{
	GPIO_E->moder &= 0x0000FFFF;
	ascii_ctrl_bit_clear(B_RS);
	ascii_ctrl_bit_set(B_RW);
	unsigned char rv = ascii_read_controller();
	GPIO_E->moder |= 0x55550000;
	return rv;
}

unsigned char ascii_read_data(void)
{
	GPIO_E->moder &= 0x0000FFFF;
	ascii_ctrl_bit_set(B_RS);
	ascii_ctrl_bit_set(B_RW);
	unsigned char rv = ascii_read_controller();
	GPIO_E->moder |= 0x55550000;
	return rv;
}

/* addressera ASCII-display och ettställ de bitar som är 1 i x */
void ascii_ctrl_bit_set(uint8_t x)
{
	/*
	unsigned char c;
	c = *portOdrLow;
	c |= (B_SELECT | x);
	*portOdrLow = c;
	* */
	
	GPIO_E->odrLow |= (B_SELECT | x);
}

/* adressera ASCII-display och nollställ de bitar som är 1 i x */
void ascii_ctrl_bit_clear(uint8_t x)
{	
	/*
	unsigned char c;
	c = *portOdrLow;
	c = B_SELECT | (c & ~x);
	*portOdrLow = c;
	*/
	
	GPIO_E->odrLow = B_SELECT | (GPIO_E->odrLow & ~x);
}
