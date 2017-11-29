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
	isHere = true;//po naciœniêciu spacji pocisk staje siê aktywny
	for (int i = x; i < 1600; i++)//pêtla wyœwietlaj¹ca po pixelu trajektoriê lotu
	{
		target.draw();
		this->y =y - (i*tan(angle)) + (gravity*i*i )/(2 * velocity* velocity*cos(angle)*cos(angle));//obliczanie rzutu ukoœnego
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
