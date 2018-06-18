#pragma once
#include <string>
#include "AllegroClassV2.h"
using namespace std;


typedef struct textData
{
	float x, y, width, height;
	int fontSize;
	string text;
	const char * path;
	const char * color;
};


class WrittenBox
{
public:
	WrittenBox(float x_, float y_, float width_, float height_, int fontSize_, string text_, const char * fontPath, const char * fontColor);
	void setBackgroundColor(const char * color);
	void setBorderColor(const char *  color);
	void setBorderThickness(float thickness);
	void TransformIntoButton(const char * backgroundColor, const char * borderColor, float thickness);
	void TransformIntoText();
	bool checkIfPressed(float x, float y);
	~WrittenBox();
	void draw();

	string getText() { return text; }
	void setText(string text) { this->text = text; }
protected:
	void setUp();
	bool button;
	string text;
	ALLEGRO_BITMAP * bitmap;
	ALLEGRO_COLOR fontColor;
	ALLEGRO_COLOR backgroundColor;
	ALLEGRO_COLOR borderColor;
	float borderThickness;
	float x;
	float y;
	float width;
	float height;
	ALLEGRO_FONT * font;
	
};

