#include "ball.h"

void set_object_speed(POBJECT o, int speedx, int speedy) {
	o->dirx = speedx;
	o->diry = speedy;
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

void update_object(POBJECT o) {
	for(int i = 0; i < o->geo->numpoints; i++) {
		o->geo->px[i].x += o->dirx;
		o->geo->px[i].y += o->diry;
	}
	o->posx += o->dirx;
	o->posy += o->diry;
}

void move_object(POBJECT o) {
	clear_object(o);
	update_object(o);
	
	if(o->posx < 1)
		o->dirx *= -1;
	if((o->posx + o->geo->sizex) > 128)
		o->dirx *= -1;
	if(o->posy < 1)
		o->diry *= -1;
	if((o->posy + o->geo->sizey) > 64)
		o->diry *= -1;
		
	draw_object(o);
}
