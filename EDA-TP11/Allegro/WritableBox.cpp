#include "WritableBox.h"






//BoxyNox::~BoxyNox()
//{
//}
//
//void BoxyNox::input(ALLEGRO_EVENT& ev)
//{
//	int character = ev.keyboard.unichar;
//	if (text.length() < maxLenght) {
//		switch (mode) {
//		case KeyboardMode::Alphabetic:
//			addLowerCaseLetter(character);
//			addUpperCaseLetter(character);
//			break;
//		case KeyboardMode::Alphanumeric:
//			addLowerCaseLetter(character);
//			addUpperCaseLetter(character);
//			addNumber(character);
//			break;
//		case KeyboardMode::Numeric:
//			addNumber(character);
//			break;
//		}
//	}
//	deleteLetter(ev.keyboard.keycode);
//
//
//}
//
//bool BoxyNox::operator==(BoxyNox & box)
//{
//	if (box.bitmap == this->bitmap)
//		return true;
//	else
//		return false;
//}
//
//void BoxyNox::addNumber(int num)
//{
//	if (num >= '0' && num <= '9')
//		this->text += (char)num;
//}
//
//void BoxyNox::addLowerCaseLetter(int let)
//{
//	if ('a' <= let && let <= 'z')
//		this->text += (char)let;
//}
//
//void BoxyNox::addUpperCaseLetter(int let)
//{
//	if ('A' <= let && let <= 'Z')
//		this->text += (char)let;
//}
//
//void BoxyNox::deleteLetter(int let)
//{
//	if (let == ALLEGRO_KEY_DELETE)
//		text.pop_back();
//}
