#pragma once
#include <vector>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>

struct Drawing
{
	ALLEGRO_BITMAP * bitmap;
	float x, y;
	float scaledHeight, scaledWidth, height, width;

};

using namespace std;

class AllegroWindow
{
public:
	AllegroWindow(float w, float h, string name = "", string icon = "");
	~AllegroWindow();
	void addDrawing(ALLEGRO_BITMAP * bitmap, float x, float y, float scaledHeight = 0, float scaledWidth = 0);
	void removeDrawing(ALLEGRO_BITMAP *bitmap);
	void moveDrawing(ALLEGRO_BITMAP *bitmapToMove, float newX, float newY);

	void setAsMain();
	void open();
	void close();
	void setBackground(ALLEGRO_COLOR color);
	void update();
	void setName(string name);
	void setIcon(string icon);

	void resize(float newW, float newH);
	bool isOpen();
	float getWidth();
	float getHeight();

	ALLEGRO_EVENT_SOURCE * getEventSource();

	bool operator==(ALLEGRO_DISPLAY* disp);

private:
	ALLEGRO_COLOR color;
	vector<Drawing>drawings;
	ALLEGRO_DISPLAY * display = nullptr;
	ALLEGRO_BITMAP * icon = nullptr;
	string name;
	float width, height;
	bool on = false;
};

