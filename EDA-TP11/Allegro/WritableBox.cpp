#include "WritableBox.h"






WritableBox::~WritableBox()
{
}

void WritableBox::input(ALLEGRO_KEYBOARD_EVENT ev)
{
	int character = ev.keycode;
	if (text.length() < maxLenght) {
		switch (mode) {
		case KeyboardMode::Alphabetic:
			addLowerCaseLetter(character);
			break;
		case KeyboardMode::Alphanumeric:
			addLowerCaseLetter(character);
			addNumber(character);
			break;
		case KeyboardMode::Numeric:
			addNumber(character);
			break;
		}
	}
	deleteLetter(character);

	this->setUp();
}

void WritableBox::clearText()
{
	this->text = "";
	this->setUp();
}



void WritableBox::addNumber(int num)
{
	if (num >= ALLEGRO_KEY_0 && num <= ALLEGRO_KEY_9)
		this->text += '0' + (num -ALLEGRO_KEY_0);
}

void WritableBox::addLowerCaseLetter(int let)
{
	if (ALLEGRO_KEY_A <= let && let <= ALLEGRO_KEY_Z)
		this->text += 'a' + (let - ALLEGRO_KEY_A);
	else if (let == ALLEGRO_KEY_SPACE)
		text += ' ';
}


void WritableBox::deleteLetter(int let)
{
	if (let == ALLEGRO_KEY_BACKSPACE && text.size()>0)
		text.pop_back();
}
