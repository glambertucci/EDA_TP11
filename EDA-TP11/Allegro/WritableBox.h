#pragma once
#include "WrittenBox.h"
#include <string>
#include <vector>

using namespace std;

//enum class KeyboardMode
//{
//	Numeric, Alphabetic, Alphanumeric 
//};


class WritableBox :
	public WrittenBox
{
public:
	WritableBox(int mode,float x_, float y_, unsigned int maxLenght, int fontSize_, const char * fontPath, const char * fontColor) :
		WrittenBox(x_, y_, (2 + maxLenght) * fontSize_ ,3 * fontSize_ , fontSize_, "", fontPath, fontColor) {
		this->mode = mode;
		this->maxLenght = maxLenght;
	}
	~WritableBox();
	void input(ALLEGRO_EVENT& ev);

	bool operator==(WritableBox&box);
private:
	void addNumber(int num);
	void addLowerCaseLetter(int let);
	void addUpperCaseLetter(int let);
	void deleteLetter(int let);
	int mode;
	unsigned int maxLenght;
};

