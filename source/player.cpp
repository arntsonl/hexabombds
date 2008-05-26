#include "player.h"

#include <string.h>
#include <stdio.h>

Player::Player()
{
	iprintf("Warning, init a player with default.\n");
}

Player::Player(spriteMan* spritePtr, Board* boardPtr)
{
	this->setSpritePtr(spritePtr);
	this->setBoardPtr(boardPtr);
	boardX = boardY = 4;
	if ( boardX%2 == 0 )
	{
		hPiece = new Piece((boardX*23+4),(boardY*20-17), PIECE_HIGHLIGHT, spritePtr, true);
	}
	// Else x is odd, we do want to offset the y
	else
	{
		hPiece = new Piece((boardX*23+4),(boardY*20-7), PIECE_HIGHLIGHT, spritePtr, true);
	}
}

Player::~Player()
{
	delete hPiece;
}

void Player::setSpritePtr(spriteMan * sManagerPtr)
{
	this->sManager = sManagerPtr;
}

void Player::setBoardPtr(Board * boardPtr)
{
	board = boardPtr;
}

void Player::setXY(unsigned int inX,unsigned int inY)
{
	if ( board->checkValidBoardSpace(inX,inY) )
	{
		boardX = inX;
		boardY = inY;
	}
}

void Player::moveLeft()
{
	if ( board->checkValidBoardSpace(boardX-1,boardY) )
	{
		boardX = boardX-1;
		if ( boardX%2 == 0 )
		{
			hPiece->setLocation(boardX*23+4,boardY*20-17);
		}
		else
		{
			hPiece->setLocation(boardX*23+4,boardY*20-7);
		}
	}
}

void Player::moveRight()
{
	if ( board->checkValidBoardSpace(boardX+1,boardY) )
	{
		boardX = boardX+1;
		if ( boardX%2 == 0 )
		{
			hPiece->setLocation(boardX*23+4,boardY*20-17);
		}
		else
		{
			hPiece->setLocation(boardX*23+4,boardY*20-7);
		}
	}
}

void Player::moveUp()
{
	if ( board->checkValidBoardSpace(boardX,boardY-1) )
	{
		boardY = boardY-1;
		if ( boardX%2 == 0 )
		{
			hPiece->setLocation(boardX*23+4,boardY*20-17);
		}
		else
		{
			hPiece->setLocation(boardX*23+4,boardY*20-7);
		}
	}
}

void Player::moveDown()
{
	if ( board->checkValidBoardSpace(boardX,boardY+1) )
	{
		boardY = boardY+1;
		if ( boardX%2 == 0 )
		{
			hPiece->setLocation(boardX*23+4,boardY*20-17);
		}
		else
		{
			hPiece->setLocation(boardX*23+4,boardY*20-7);
		}
	}
}

void Player::explodeBlock()
{
	int piecesExploded = board->explodePiece(boardX,boardY);
}

void Player::update()
{
}

