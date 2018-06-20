#include "AllegroWindow.h"



AllegroWindow::AllegroWindow(float w, float h, string name ="", string icon = "")
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

void AllegroWindow::addBox(WrittenBox & box)
{
	boxes.push_back(box);
}

void AllegroWindow::removeBox(WrittenBox & box)
{
	bool kill = false; int i = 0;
	for (int i = 0; i < boxes.size(); i++) {
		if (boxes[i] == box)
			kill = true;
	}
	i--;
	if (kill) {
		boxes.erase(boxes.begin() + i);
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
		for (WrittenBox& box : boxes)
			box.draw();
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

bool AllegroWindow::isOpen()
{
	return on;
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
