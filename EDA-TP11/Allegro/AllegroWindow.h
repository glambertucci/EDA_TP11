#pragma once
#include "WrittenBox.h"
#include <vector>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>



using namespace std;

class AllegroWindow
{
public:
	AllegroWindow(float w, float h, string name = "", string icon = "");
	~AllegroWindow();

	void addBox(WrittenBox& box);
	void removeBox(WrittenBox&box);
	void setAsMain();
	void open();
	void close();
	void setBackground(ALLEGRO_COLOR color);
	void update();
	void setName(string name);
	void setIcon(string icon);

	bool isOpen();

	ALLEGRO_EVENT_SOURCE * getEventSource();

	bool operator==(ALLEGRO_DISPLAY* disp);

private:
	ALLEGRO_COLOR color;
	vector<WrittenBox&>boxes;
	ALLEGRO_DISPLAY * display = nullptr;
	ALLEGRO_BITMAP * icon = nullptr;
	string name;
	float width, height;
	bool on = false;
};

