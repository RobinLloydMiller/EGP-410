#ifndef _COLOR_H
#define _COLOR_H

#include "DeanLib/Trackable.h"

class Color: public Trackable
{
public:
	int getR();
	int getG();
	int getB();
	Color(int red, int green, int blue);
	~Color();

private:
	int mR;
	int mG;
	int mB;
};

#endif