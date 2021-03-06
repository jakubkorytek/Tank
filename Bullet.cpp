#include "Bullet.h"



Bullet::Bullet()
{
	al_init();
	al_init_image_addon();
	isHere = false;
	score = 0;

}


Bullet::~Bullet()
{
}

void Bullet::draw(int x, int y, float velocity, float angle, double gravity, Target *target)
{
	isHere = true;//po naci�ni�ciu spacji pocisk staje si� aktywny

	//p�tla wy�wietlaj�ca po pixelu trajektori� lotu
	for (int i = x; i < 1600; i++)
	{
		//obliczanie rzutu uko�nego
		this->y =y - (i*tan(angle)) + (gravity*i*i )/(2 * velocity* velocity*cos(angle)*cos(angle));

		//rysowanie
		al_draw_pixel(i, this->y, al_map_rgb(255, 255, 255));
		al_flip_display();

		//wykrywanie kolizji
		if (target->getX() == i && (target->getY() < this->y && (60 + target->getY()) > this->y))
		{
			target->createNew();//po wykryciu kolizji generuj� now� tarcz� strzelnicz�
			score += 10;//zwi�kszam wynik
			isHere = false;
			break;
		}
	}
	isHere = false;
	
}

void Bullet::destroy()
{
}


bool Bullet::hello()
{
	return this->isHere;
}

int Bullet::getScore()
{
	return this->score;
}
