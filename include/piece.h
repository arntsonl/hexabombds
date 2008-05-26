#pragma once

#include "helper.h"
#include "spriteMan.h"

class Piece
{
public:
	Piece();
	Piece(unsigned int,unsigned int,int, spriteMan*, bool); // x, y, color, sprite manager, main sprite?
	~Piece();
	void setLocation(unsigned int,unsigned int);
	int getColor() {return color;}
private:
	int color;
	int spriteID;
	u8 x,y;
	bool isMainSprite;
	spriteMan * spritePtr;
};
