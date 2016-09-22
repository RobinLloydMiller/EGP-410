#include "Color.h"

Color::Color(int red, int green, int blue)
{
	mR = red;
	mG = green;
	mB = blue;
}

Color::~Color()
{

}

int Color::getR()
{
	return mR;
}

int Color::getG()
{
	return mG;
}

int Color::getB()
{
	return mB;
}