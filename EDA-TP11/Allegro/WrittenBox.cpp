#include "WrittenBox.h"






WrittenBox::WrittenBox(float x_, float y_, float width_, float height_, string text_, ALLEGRO_FONT * font, const char * fontColor)
{
	this->x = x_;
	this->y = y_;
	this->width = width_;
	this->height = height_;
	this->text = text_;
	this->bitmap = al_create_bitmap(width_, height_);
	this->font =font;
	this->fontColor = al_color_name(fontColor);
	this->backgroundColor = al_map_rgba(0, 0, 0, 0);
	this->borderColor = al_map_rgba(0, 0, 0, 0);
	this->borderThickness = 0;
	this->button = false;

	this->setUp();
}

WrittenBox::WrittenBox(float x_, float y_, float width_, float height_, int fontSize_, string text_, const char * fontPath, const char * fontColor)
{
	this->x = x_;
	this->y = y_;
	this->width = width_;
	this->height = height_;
	this->text = text_;
	this->bitmap = al_create_bitmap(width_, height_);
	this->font = al_load_font(fontPath, -fontSize_, ALLEGRO_ALIGN_CENTRE);
	this->fontColor = al_color_name(fontColor);
	this->backgroundColor = al_map_rgba(0, 0, 0, 0);
	this->borderColor = al_map_rgba(0, 0, 0, 0);
	this->borderThickness = 0;
	this->button = false;

	this->setUp();
}

void WrittenBox::setBackgroundColor(const char * color )
{
	if (color != nullptr) {
		this->backgroundColor = al_color_name(color);
		unsigned char r, g, b;
		al_unmap_rgb(this->backgroundColor, &r, &g, &b);
		this->pressedColor = al_map_rgb((r > 50) ? r - 50 : r, (g > 50) ? g - 50 : g, (b > 50) ? b - 50 : b);
	}
	else
		this->backgroundColor = al_map_rgba(0, 0, 0, 0);
	this->setUp();
}

void WrittenBox::setBorderColor(const char * color)
{
	if (color != nullptr)
		this->borderColor = al_color_name(color);
	else
		this->borderColor = al_map_rgba(0, 0, 0, 0);
	this->setUp();
}

void WrittenBox::setBorderThickness(float thickness)
{
	this->borderThickness = thickness;
	setUp();
}

void WrittenBox::TransformIntoButton(const char * backgroundColor, const char * borderColor, float thickness)
{
	setBorderThickness(thickness);
	setBorderColor(borderColor);
	setBackgroundColor(backgroundColor);
	this->button = true;
}

void WrittenBox::TransformIntoText()
{
	this->button = false;
	setBorderColor(nullptr);
	setBackgroundColor(nullptr);
	setBorderThickness(0);
}

bool WrittenBox::checkIfPressed(float x, float y)
{
	if (button) {
		if ((this->x <= x) && (x <= this->x + this->width))
			if ((this->y <= y) && (y <= (this->y + this->height)))
				this->pressed = true;
		
	}
	if (pressed) {
		ALLEGRO_COLOR temp = backgroundColor;
		backgroundColor = pressedColor;
		pressedColor = temp;
		this->setUp();
	}

	return this->pressed;
}

bool WrittenBox::isPressed()
{
	return this->pressed;
}

WrittenBox::~WrittenBox()
{
	if (this->bitmap)
		al_destroy_bitmap(this->bitmap);
	if (this->font)
		al_destroy_font(this->font);
}

bool WrittenBox::operator==(WrittenBox & box)
{
	if (box.bitmap == this->bitmap)
		return true;
	else
		return false;
}

ALLEGRO_BITMAP * WrittenBox::getBitmap()
{
	return this->bitmap;
}

float WrittenBox::getX()
{
	return this->x;
}

float WrittenBox::getY()
{
	return this->y;
}

void WrittenBox::draw()
{
	al_draw_bitmap(this->bitmap,this->x,this->y,0);
}

void WrittenBox::unpressButton()
{
	this->pressed = false;
	ALLEGRO_COLOR temp = pressedColor;
	pressedColor = backgroundColor;
	backgroundColor = temp;
	setUp();
}

void WrittenBox::setUp()
{
	ALLEGRO_BITMAP * c = al_get_backbuffer(al_get_current_display());
	al_set_target_bitmap(this->bitmap);

	al_clear_to_color(this->backgroundColor);
	al_draw_rectangle(0, 0, this->width, this->height, this->borderColor, this->borderThickness);

	al_draw_text(this->font, this->fontColor, this->width / 2.0, (this->height / 2.0) - (al_get_font_line_height(this->font)/2.0), ALLEGRO_ALIGN_CENTRE, this->text.c_str());

	al_set_target_bitmap(c);
}
