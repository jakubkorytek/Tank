#include "Tank.h"



Tank::Tank()
{
	al_init();
	al_init_image_addon();
	barrelAngle = 0;
	barrelX = 50;
	barrelY = 530;


	tank = al_load_bitmap("tank.png");//�adowanie pliku png
	if (!tank)
		al_show_native_message_box(display, "ERROR", "NIE MOZNA", "OTWORZYC PLIKU TANK",NULL, NULL);


	barrel = al_load_bitmap("barrel.png");//�adowanie pliku png
	if(!barrel)
		al_show_native_message_box(display, "ERROR", "NIE MOZNA", "OTWORZYC PLIKU BARREL", NULL, NULL);

	
}


Tank::~Tank()
{
}

void Tank::setAngle(float angle)
{
	barrelAngle = angle;
}

float Tank::getAngle()
{
	return barrelAngle;
}


void Tank::draw()
{
	al_draw_scaled_rotated_bitmap(barrel, 0, 0, barrelX, barrelY, 1, 0.1, barrelAngle, NULL);//rysowanie bitmapy 
	al_draw_scaled_bitmap(tank, 0, 10, 145, 129, 0, 500, 100, 100, NULL);
	
}

void Tank::destroy()
{
	al_destroy_bitmap(tank);
	al_destroy_bitmap(barrel);
}

void Tank::setDisplay(ALLEGRO_DISPLAY * display)
{
	this->display = display;
}

int Tank::getBarrelX()
{
	return this->barrelX;
}

int Tank::getBarrelY()
{
	return this->barrelY;
}

int Tank::getBarrelWidth()
{
	return (int)al_get_bitmap_width(barrel);
}


