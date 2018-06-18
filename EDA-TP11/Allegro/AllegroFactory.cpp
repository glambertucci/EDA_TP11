#include "AllegroFactory.h"
//
//AllegroKeyboardFactory::~AllegroKeyboardFactory()
//{
//	int i;
//	for (i = 0; i < boxes.size(); i++)
//		delete boxes[i];
//}
//
////BoxyNox * AllegroKeyboardFactory::createWritableBox(int mode, float x_, float y_, unsigned int maxLenght, int fontSize_, const char * fontPath, const char * fontColor)
////{
////		BoxyNox * temp = new BoxyNox(mode, x_, y_, maxLenght, fontSize_, fontPath, fontColor);
////		boxes.push_back(temp);
////		return temp;
////}
//
//void AllegroKeyboardFactory::destroy(BoxyNox * box)
//{
//	int i;
//	bool kill = false;
//	for (i = 0; i < boxes.size(); i++) {
//		if (boxes[i] == box)
//			kill = true;
//	}
//	if (kill) {
//		boxes.erase(boxes.begin() + i);
//		delete box;
//	}
//}
