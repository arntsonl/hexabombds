#pragma once

// This is the player class. Players will consist
// of a physics actor, life points, current ID (player ID?),
// a sprite pointer

#include "stateMan.h"
#include "spriteMan.h"
#include "helper.h"
#include "board.h" 
#include "piece.h"

class Player
{
public:
	Player();
	Player(spriteMan*,Board*);
	~Player();
	
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void update();
	
	void setSpritePtr(spriteMan*);
	void setBoardPtr(Board*);

	u32 getX() { return boardX; }
	u32 getY() { return boardY; }
	void setXY(unsigned int inX,unsigned int inY);
	
	void explodeBlock();
	void touchPieceDown();
	void touchPieceSwipe();

private:
	int life; // 4 lives?
	unsigned int boardX,boardY;
	
	Piece * hPiece; // highlight piece
	spriteMan * sManager; // current sprite manager in graphics engine
	Board * board;
};
