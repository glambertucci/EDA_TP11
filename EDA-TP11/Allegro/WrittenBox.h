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
	WrittenBox(float x_, float y_, float width_, float height_, string text_, ALLEGRO_FONT * font, const char * fontColor);

	WrittenBox(float x_, float y_, float width_, float height_, int fontSize_, string text_, const char * fontPath, const char * fontColor);
	// Cambia el color de fondo del cuadro de texto
	void setBackgroundColor(const char * color);
	// Cambia el color del borde del cuadro de texto
	void setBorderColor(const char *  color);
	// Cambia el ancho del borde del cuadro de texto
	void setBorderThickness(float thickness);
	// Transforma al cuadro de texto en un boton
	void TransformIntoButton(const char * backgroundColor, const char * borderColor, float thickness);
	// Transforma a un boton en un cuadro de texto
	void TransformIntoText();
	// Si es un boton, se fija si se clickeo en el.
	bool checkIfPressed(float x, float y);
	bool isPressed();
	~WrittenBox();
	// Dibuja al cuadro de texto
	void draw();
	void unpressButton();

	bool operator==(WrittenBox&box);
	ALLEGRO_BITMAP * getBitmap();
	float getX();
	float getY();
	string getText() { return text; }
	void setText(string text) { this->text = text; }
protected:
	//Actualiza al bitmap interno con los datos de la clase.
	void setUp();
	bool pressed;
	bool button;
	string text;
	ALLEGRO_BITMAP * bitmap;
	ALLEGRO_COLOR fontColor;
	ALLEGRO_COLOR backgroundColor;
	ALLEGRO_COLOR pressedColor;
	ALLEGRO_COLOR borderColor;
	float borderThickness;
	float x;
	float y;
	float width;
	float height;
	ALLEGRO_FONT * font;
	
};

