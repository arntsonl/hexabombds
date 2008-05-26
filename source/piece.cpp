#include "piece.h"
#include <stdio.h>

// default constructor
Piece::Piece()
{
}

// int x,y color
Piece::Piece(unsigned int newX, unsigned int newY, int newColor, spriteMan * newPtr, bool isMain) 
{
	x = newX;
	y = newY;
	color = newColor;
	spritePtr = newPtr;
	isMainSprite = isMain;
	if ( newColor == PIECE_HIGHLIGHT )
	{
		spriteID = spritePtr->addSprite(x,y,color); // set our sprite ID to 0 for highlight piece
		spritePtr->moveSprite(x,y,spriteID,true);
	}
	else
	{
		if ( isMainSprite == true ) // is in the main sprite list
		{
			spriteID = spritePtr->addSprite(x,y,color);
		}
		else // is in the sub sprite list
		{
			spriteID = spritePtr->addSubSprite(x,y,color);
		}
	}
}

// default deconstructor
Piece::~Piece()
{
	spritePtr->eraseSpriteID(spriteID);
}

void Piece::setLocation(unsigned int newX, unsigned int newY)
{
	x = newX;
	y = newY;
	if ( isMainSprite == true )
	{
		spritePtr->moveSprite(x,y,spriteID,false);
	}
	else
	{
		spritePtr->moveSubSprite(x,y,spriteID,false);
	}
}
