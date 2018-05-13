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
	/*
	SIZE * SIZE,
	SIZE,SIZE,
	*/
	28,
	5,8,
	{
		{11,9},           {13,9},           {15,9},
		{11,10},          {13,10},          {15,10},
		         {12,11}, {13,11}, {14,11},
		{11,12}, {12,12}, {13,12}, {14,12}, {15,12},
		{11,13}, {12,13}, {13,13}, {14,13}, {15.13},
		         {12,14}, {13,14}, {14,14},
		{11,15},          {13,15},          {15,15},
		{11,16},          {13,16},          {15,16}
	}
};
	
OBJECT lusen =
{
	&lusen_geometry,
	0,0,
	11,9,
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

GEOMETRY enemy_geometry =
{
	8,
	4,4,
	
	{
		         {51,30},  
				 {51,31}, {52,31}, {53,31},
		{50,32} ,{51,32}, {52,32},
					      {52,33}
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

OBJECT enemy = 
{
	&enemy_geometry,
	0,0,
	50,30,
	draw_object,
	clear_object,
	move_random_direction,
	set_random_speed
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

void draw_frame()
{
	for(int i = 0; i < 128; i++)
		pixel(i,1,1);
	for(int i = 0; i < 64; i++)
		pixel(1,i,1);
	for(int i = 0; i < 128; i++)
		pixel(i,64,1);
	for(int i = 0; i < 64; i++)
		pixel(128,i,1);
}

unsigned char is_on(POBJECT o1, POBJECT o2)
{
	if((o1->posx+o1->geo->sizex>o2->posx)&&(o2->posx+o2->geo->sizex>o1->posx)
	 &&(o1->posy+o1->geo->sizey>o2->posy)&&(o2->posy+o2->geo->sizey>o1->posy))
	{
		return 1;
	}
	return 0;
}

void main(void) {	
	init_app();
	ascii_init();
	graphic_initialize();
	//graphic_clear_screen();
	draw_ascii("0");
	draw_frame();

	int speed = 40;
	int score = 0;
	
	POBJECT pLusen = &lusen;
	POBJECT pFruit = &fruit;
	POBJECT pEnemy = &enemy;
	
	//random_position(pFruit);
	pFruit->draw(pFruit);
	pEnemy->draw(pEnemy);
	pLusen->set_speed(pLusen, SIZE, 0);
	
	while(1) {
		pLusen->move(pLusen);
		pEnemy->move(pEnemy);
		
		if(is_on(pEnemy, pLusen))
		{
			draw_ascii("DEATH by Enemy");
			while(1){}
		}
		
		switch (keyb()) {
			case 2: pLusen->set_speed(pLusen, 0, -SIZE); break;
			case 4: pLusen->set_speed(pLusen, -SIZE, 0); break;
			case 6: pLusen->set_speed(pLusen, SIZE, 0); break;
			case 8: pLusen->set_speed(pLusen, 0, SIZE); break;
		}
		pEnemy->set_speed(pEnemy, 1, 30);
		
		if (is_on(pLusen, pFruit)) {
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
