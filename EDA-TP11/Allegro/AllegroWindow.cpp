#include "AllegroWindow.h"



AllegroWindow::AllegroWindow(float w, float h, string name, string icon)
{
	width = w;
	height = h;

	if (name.size() > 0)
		setName(name);
	if (icon.size() > 0)
		setIcon(icon);
}

AllegroWindow::~AllegroWindow()
{
	close();
	if (icon != nullptr)
		al_destroy_bitmap(icon);
}

void AllegroWindow::addDrawing(ALLEGRO_BITMAP * bitmap, float x, float y, float scaledHeight, float scaledWidth)
{ 
	Drawing temp;
	temp.bitmap = bitmap;
	temp.x = x;
	temp.y = y;
	temp.height = al_get_bitmap_height(bitmap);
	temp.width = al_get_bitmap_width(bitmap);

	if (scaledHeight == 0)
		temp.scaledHeight = temp.height;
	else
		temp.scaledHeight = scaledHeight;
	if (scaledWidth == 0)
		temp.scaledWidth = temp.width;
	else 
		temp.scaledWidth = scaledWidth;
	drawings.push_back(temp);
}


void AllegroWindow::removeDrawing(ALLEGRO_BITMAP * bitmap)
{
	bool kill = false; int i = 0;
	for ( i = 0; i < drawings.size() && !kill; i++) {
		if (drawings[i].bitmap == bitmap)
			kill = true;
	}
	i--;
	if (kill) {
		drawings.erase(drawings.begin() + i);
	}
}

void AllegroWindow::moveDrawing(ALLEGRO_BITMAP * bitmapToMove, float newX, float newY)
{
	bool move = false; int i = 0;
	for (int i = 0; i < drawings.size(); i++) {
		if (drawings[i].bitmap == bitmapToMove)
			move = true;
	}
	i--;
	if (move) {
		drawings[i].x = newX;
		drawings[i].y = newY;

	}
}

void AllegroWindow::setAsMain()
{
	if (on)
		al_set_target_backbuffer(this->display);
}

void AllegroWindow::open()
{
	if (!this->on) {
		this->on = true;
		this->display = al_create_display(width, height);
		if (name.size() > 0)
			al_set_window_title(display, name.c_str());
		if (icon != nullptr)
			al_set_display_icon(display, icon);
	}
}

void AllegroWindow::close()
{
	if (this->on) {
		this->on = false;
		al_destroy_display(this->display);
		this->display = nullptr;
	}
}

void AllegroWindow::setBackground(ALLEGRO_COLOR color)
{
	this->color = color;
}

void AllegroWindow::update()
{
	if (on) {
		al_clear_to_color(color);
		for (Drawing& drawing : drawings)
			al_draw_scaled_bitmap(drawing.bitmap, 0, 0,drawing.width, drawing.height , drawing.x, drawing.y, drawing.scaledWidth, drawing.scaledHeight, 0);		
		al_flip_display();
	}

}

void AllegroWindow::setName(string name)
{
	this->name = name;
}

void AllegroWindow::setIcon(string icon)
{
	this->icon = al_load_bitmap(icon.c_str());
}

void AllegroWindow::resize(float newW, float newH)
{
	this->width = newW;
	this->height = newH;
	al_resize_display(this->display, newW, newH);
}

bool AllegroWindow::isOpen()
{
	return on;
}

float AllegroWindow::getWidth()
{
	return this->width;
}

float AllegroWindow::getHeight()
{
	return this->height;
}

ALLEGRO_EVENT_SOURCE * AllegroWindow::getEventSource()
{
	return al_get_display_event_source(display);
}

bool AllegroWindow::operator==(ALLEGRO_DISPLAY * disp)
{
	if (this->display == disp)
		return true;
	else
		return false;
}
