#pragma once
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <cmath>
#include "Target.h"
class Bullet
{
private:
	int x, y;
	double angle;
	bool isHere;
	ALLEGRO_BITMAP *bullet;
	Target target;

public:
	Bullet();
	~Bullet();
	void draw(int x,int y, float velocity,float angle, double gravity);
	void destroy();
	bool hello();

};

