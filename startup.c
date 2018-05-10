void startup(void) __attribute__((naked)) __attribute__((section (".start_section")) );

void startup ( void )
{
__asm volatile(
	" LDR R0,=0x2001C000\n"		/* set stack */
	" MOV SP,R0\n"
	" BL main\n"				/* call main */
	"_exit: B .\n"				/* never return */
	) ;
}

#include <stdlib.h>
#include <stdint.h>
#include "graphics.h"
#include "defines.h"
#include "delays.h"
#include "keypad.h"
#include "ball.h"
#include "ascii.h"

GEOMETRY lusen_geometry =
{
	SIZE * SIZE,
	SIZE,SIZE,
	{
		{1,1}, {2,1},
		{1,2}, {2,2}
	}
};
	
OBJECT lusen =
{
	&lusen_geometry,
	0,0,
	1,1,
	draw_object,
	clear_object,
	move_object,
	set_object_speed
};

GEOMETRY fruit_geometry =
{
	SIZE * SIZE,
	SIZE,SIZE,
	{
		{9,3}, {10,3},
		{9,4}, {10,4}
	}
};
	
OBJECT fruit =
{
	&fruit_geometry,
	0,0,
	9,3,
	draw_object,
	clear_object,
	move_object,
	set_object_speed
};

void init_app(void) {
	// Display init
	GPIO_E->moder = 0x55555555;
	GPIO_E->otyper = 0x0000;
	GPIO_E->ospeedr = 0x55555555;
	GPIO_E->pupdr = 0xAAAAAAAA;
	
	// Keypad init
	GPIO_D->moder = 0x55005555;
	GPIO_D->otyper &= 0x0FFF;
	GPIO_D->pupdr |= 0xAAAAAAAA;
}

void main(void) {	
	init_app();
	ascii_init();
	graphic_initialize();
	//graphic_clear_screen();
	draw_ascii("0");
	
	int speed = 40;
	int score = 0;
	
	POBJECT pLusen = &lusen;
	POBJECT pFruit = &fruit;
	
	//random_position(pFruit);
	pFruit->draw(pFruit);
	pLusen->set_speed(pLusen, SIZE, 0);
	
	while(1) {
		pLusen->move(pLusen);
		
		switch (keyb()) {
			case 2: pLusen->set_speed(pLusen, 0, -SIZE); break;
			case 4: pLusen->set_speed(pLusen, -SIZE, 0); break;
			case 6: pLusen->set_speed(pLusen, SIZE, 0); break;
			case 8: pLusen->set_speed(pLusen, 0, SIZE); break;
		}
		
		if ((pLusen->posx == pFruit->posx) && (pLusen->posy == pFruit->posy)) {
			score++;
			pFruit->clear(pFruit);
			random_position(pFruit);
			pFruit->draw(pFruit);
			draw_ascii(itoa(score));
			speed -= 1;
		}
		
		//delay_milli(speed);
	}
}
