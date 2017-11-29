#include "Target.h"



Target::Target()
{
}


Target::~Target()
{
}

void Target::createNew()
{
	x = 400 + rand() % 1200;
	y = 500 - rand() % 500;
}

void Target::draw()
{
	for (int i = 0; i < 60; i++)
		al_draw_pixel(x, y + i, al_map_rgb(255, 0, 0));
}

bool Target::collision(int x, int y)
{
	if (x == this->x && (y>this->y && y<this->y + 60))
	{
		return true;
	}
	return false;
}
