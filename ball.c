#include "ball.h"

unsigned short lfsr = 0xACE1u;
unsigned short bit;
int turn_x = 1;
int turn_y = 1;

unsigned short rand()
{
	bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
	return lfsr =  (lfsr >> 1) | (bit << 15);
}


void set_object_speed(POBJECT o, int speedx, int speedy) {
	o->dirx = speedx;
	o->diry = speedy;
}

void set_random_speed(POBJECT o, int min, int max)
{
	o->dirx = (char)(rand()%max)+min;
	o->diry = (char)(rand()%max)+min;
		
	if(o->posx + o->dirx*turn_x < 1)
		turn_x = 1;
	if(o->posy + o->diry*turn_y < 1)
		turn_y = 1;
	if(o->posx + o->geo->sizex + o->dirx*turn_x > 128)
		turn_x = -1;
	if(o->posy + o->geo->sizey + o->diry*turn_y > 64)
		turn_y = -1;
	o->dirx *= turn_x;
	o->diry *= turn_y;
}

void draw_object(POBJECT o) {
	for(int i = 0; i < o->geo->numpoints; i++) {
		pixel(o->geo->px[i].x, o->geo->px[i].y, 1);
	}
}

void clear_object(POBJECT o) {
	for(int i = 0; i < o->geo->numpoints; i++) {
		pixel(o->geo->px[i].x, o->geo->px[i].y, 0);
	}
}

void random_position(POBJECT o) {
	short rand_x = ((rand() / 2) % 126) + 1;
	short rand_y = ((rand() / 2) % 62) + 1;
	for (int i = 0; i < 4; i++) {
		o->geo->px[i].x = rand_x + i % 2;
		if (i < 2)
			o->geo->px[i].y = rand_y;
		else
			o->geo->px[i].y = rand_y + 1;
	}
	o->posx = rand_x;
	o->posy = rand_y;
}

void update_object(POBJECT o) {
	for(int i = 0; i < o->geo->numpoints; i++) {
		o->geo->px[i].x += o->dirx;
		o->geo->px[i].y += o->diry;
	}
	o->posx += o->dirx;
	o->posy += o->diry;
}

void move_random_direction(POBJECT o)
{
	clear_object(o);
	update_object(o);
	draw_object(o);
}

void move_object(POBJECT o) {
	clear_object(o);
	update_object(o);
	
	if(o->posx < 1) {
		draw_ascii("DEATH");
		while(1){};
	}
	if((o->posx + o->geo->sizex) > 128) {
		draw_ascii("DEATH");
		while(1){};
	}
	if(o->posy < 1) {
		draw_ascii("DEATH");
		while(1){};
	}
	if((o->posy + o->geo->sizey) > 64) {
		draw_ascii("DEATH");
		while(1){};
	}
		
	draw_object(o);
}
