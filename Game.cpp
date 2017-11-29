#include "Game.h"

Game::Game()
{
	
	if (al_is_keyboard_installed())
		al_show_native_message_box(display, "super", "mamy", "klawiature", NULL, NULL);
	i = 0;
	power = 3;
	al_init_font_addon();
	font = al_create_builtin_font();
	
}

Game::~Game()
{
}



void Game::update()
{
	
}

void Game::draw()
{
	
		al_clear_to_color(al_map_rgb(0, 0, 0));//czyszczenie bitmapy 
		tank.draw();//rysowanie
		for (int i = 50; i < tank.getBarrelX() + barrelX; i++)
		{
			al_draw_pixel(i, 530, al_map_rgb(255, 0, 255));
		}
		for (int i = 530; i > tank.getBarrelY() - barrelY; i--)
		{
			al_draw_pixel(tank.getBarrelX() + barrelX, i, al_map_rgb(255, 0, 255));
		}
		snprintf(Angle, sizeof(Angle), "%g", (tank.getAngle() * -180) / pi);
		snprintf(Width, sizeof(Width), "%d", tank.getBarrelWidth());
		snprintf(PosX, sizeof(PosX), "%g", tank.getBarrelX()+barrelX);
		snprintf(PosY, sizeof(PosY), "%g", tank.getBarrelY() - barrelY);
		snprintf(bheight, sizeof(bheight), "%g", barrelX);
		snprintf(bwidth, sizeof(bwidth), "%g", barrelY);
		snprintf(powLvl, sizeof(powLvl), "%d", power);
		al_draw_text(font, al_map_rgb(255, 255, 255), 10, 40, 0, "Poczatek lufy:");
		al_draw_text(font, al_map_rgb(255, 255, 255), 10, 60, 0, "X = 50  Y=530");
		al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 80, 0, "Kat = ");
		al_draw_textf(font, al_map_rgb(255, 255, 255), 100, 80, 0, Angle);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 100, 0, "Sila wystrzalu: ");
		al_draw_textf(font, al_map_rgb(255, 255, 255), 140, 100, 0, powLvl);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 120, 0, "Dlugosc lufy = ");
		al_draw_textf(font, al_map_rgb(255, 255, 255), 150, 120, 0, Width);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 140, 0, "Dlugosc a = ");
		al_draw_textf(font, al_map_rgb(255, 255, 255), 150, 140, 0, bwidth);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 160, 0, "Dlugosc b = ");
		al_draw_textf(font, al_map_rgb(255, 255, 255), 150, 160, 0, bheight);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 180, 0, "Polozenie konca lufy X = ");
		al_draw_textf(font, al_map_rgb(255, 255, 255), 220, 180, 0, PosX);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 200, 0, "Polozenie konca lufy Y = ");
		al_draw_textf(font, al_map_rgb(255, 255, 255), 220, 200, 0, PosY);

		al_flip_display();
}

void Game::destroy()
{
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	tank.destroy();
	bullet.destroy();
}

void Game::gameLoop()
{
	al_init();//inicjalizacja biblioteki 
	al_install_keyboard();
	al_init_image_addon();
	al_install_mouse();
	display = al_create_display(1600, 600);//tworzenie okna 1600x600
	al_set_window_title(display, "Tank");

	FPS = 10.0f;
	done = false;

	tank.setDisplay(display);
	timer = al_create_timer(1.0f / FPS);//kontrola fps
	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_start_timer(timer);
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(queue, &ev);
		al_get_keyboard_state(&keyState);
		degree = (tank.getAngle()*180)/pi;//przypisanie k¹ta lufy czo³gu i przeliczenie na stopnie
		if (input.isKeyPressed(ev, ALLEGRO_KEY_ESCAPE))
			done = true;
		else if (input.isKeyPressed(ev, ALLEGRO_KEY_W))
		{
			degree -= 5;
			if (degree < -75)//biblioteka allegro obraca obiekty w ich praw¹ stronê czyli na logikê nasze 90 stopni to -90 dla biblioteki
				degree = -75;
			barrelY = tank.getBarrelWidth()* sin((degree*pi) / -180);//obliczanie pozycji koñca lufy z trygonometrii 
			barrelX = tank.getBarrelWidth()* cos((degree*pi) / -180);//145 to szerokoœæ grafiki lufy, 0.8 to jej skalowanie do rysowania
		}
		else if (input.isKeyPressed(ev, ALLEGRO_KEY_S))
		{
			degree += 5;
			if (degree > 0)
				degree = 0;
			barrelY = tank.getBarrelWidth()* sin((degree*pi) / -180);//obliczanie pozycji koñca lufy z trygonometrii 
			barrelX = tank.getBarrelWidth()* cos((degree*pi) / -180);//145 to szerokoœæ grafiki lufy, 0.8 to jej skalowanie do rysowania
		}
		else if (input.isKeyPressed(ev, ALLEGRO_KEY_D))
		{
			power += 1;
			if (power > 8)
				power = 8;
		}
		else if (input.isKeyPressed(ev, ALLEGRO_KEY_A))
		{
			power -= 1;
			if (power < 1)
				power = 1;
		}
		else if (input.isKeyPressed(ev, ALLEGRO_KEY_SPACE))
		{
			if (!bullet.hello())
				bullet.draw(tank.getBarrelX()+barrelX,tank.getBarrelY()-barrelY, velocity*power, ((degree*pi)/-180), gravity);
				//przekazanie wspó³rzêdnych koñca lufy jako pocz¹tek trajektorii lotu
		}
		tank.setAngle((degree*pi)/180);//zamiana stopni na radiany 
		Game::draw();
		
	}
	Game::destroy();
}
