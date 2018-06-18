#pragma once
#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_video.h>

using namespace std;

class AllegroDisplayFactory
{
public:
	AllegroDisplayFactory(){}
	~AllegroDisplayFactory() { for (ALLEGRO_DISPLAY * disp : all) destroy(disp); }
	/*
		El modo de destruccion automatico hace que se destruyan todas las pantallas cuando se destruye al objeto. De estar desactivado se tienen que destruir manualemente
	*/
	ALLEGRO_DISPLAY * create(unsigned int w, unsigned int h, bool automaticDestruction = true) {
		ALLEGRO_DISPLAY * temp = al_create_display(w, h);
		if (temp)
			if (automaticDestruction) {
				all.push_back(temp);
			}
		return temp;
	}
	void destroy(ALLEGRO_DISPLAY * display) { al_destroy_display(display); }

private:
	vector<ALLEGRO_DISPLAY *> all;
};




class AllegroBitmapFactory
{
public:
	AllegroBitmapFactory(){}
	~AllegroBitmapFactory(){ for (ALLEGRO_BITMAP * bmap : all) destroy(bmap); }
	ALLEGRO_BITMAP * create(unsigned int w, unsigned int h, bool automaticDestruction = true) {
		ALLEGRO_BITMAP * temp = al_create_bitmap(w, h);
		if (temp)
			if (automaticDestruction) {
				all.push_back(temp);
			}
		return temp;
	}
	void destroy(ALLEGRO_BITMAP * bmap) { al_destroy_bitmap(bmap); }

private:
	vector<ALLEGRO_BITMAP *> all;
};

enum class PrimitiveTypes
{
	Square,Rectangle,FilledRectangle, RoundedRectangle, Triangle, FilledTriangle, Ellipse, FilledEllipse, PieSlice, FilledPieSlice
};

class AllegroPrimitivesFactory
{
public:
	AllegroPrimitivesFactory(){}

	~AllegroPrimitivesFactory(){}
	ALLEGRO_BITMAP * createCircle(float radius ,ALLEGRO_COLOR color,bool filled = true, float thickness = 0) {
		ALLEGRO_BITMAP * temp = al_create_bitmap((radius+thickness) * 2, (radius + thickness) * 2);
		if (temp) {
			al_set_target_bitmap(temp);
			if (filled)
				al_draw_filled_circle((radius + thickness), (radius + thickness), radius, color);
			else
				al_draw_circle((radius + thickness), (radius + thickness), radius, color, thickness);
			al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
		}
		return temp;
	}


private:

};
