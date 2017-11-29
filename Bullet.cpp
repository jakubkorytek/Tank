#include "Bullet.h"



Bullet::Bullet()
{
	al_init();
	al_init_image_addon();
	bullet = al_load_bitmap("bullet.png");
	isHere = false;
	target.createNew();

}


Bullet::~Bullet()
{
}

void Bullet::draw(int x, int y, float velocity, float angle, double gravity)
{
	isHere = true;//po naci�ni�ciu spacji pocisk staje si� aktywny
	for (int i = x; i < 1600; i++)//p�tla wy�wietlaj�ca po pixelu trajektori� lotu
	{
		target.draw();
		this->y =y - (i*tan(angle)) + (gravity*i*i )/(2 * velocity* velocity*cos(angle)*cos(angle));//obliczanie rzutu uko�nego
		al_draw_pixel(i, this->y, al_map_rgb(255, 255, 255));
		if (target.collision(i, this->y))
			target.createNew();
		al_flip_display();
	}
	isHere = false;
}

void Bullet::destroy()
{
	al_destroy_bitmap(bullet);
}


bool Bullet::hello()
{
	return this->isHere;
}
