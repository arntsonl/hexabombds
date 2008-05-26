#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum {
	PIECE_STATE_INACTIVE=0,
	PIECE_STATE_ACTIVE
};

typedef enum {
	BOARD_IDLE = 0,
	BOARD_UPDATE,
	BOARD_ANIMATE,
	BOARD_REFILL
};

Board::Board()
{
	iprintf("Without specifying your sprite manager, board can't work\n");
}

Board::Board(spriteMan * newPtr)
{
	spritePtr = newPtr;
	for(int i = 0; i < 81; i++)
	{
		boardSpace[i/9][i%9] = 0;
		boardSpaceState[i/9][i%9] = PIECE_STATE_INACTIVE; // 0 = inactive, 1 = active
	}
	boardState = BOARD_IDLE;
}

Board::~Board()
{
	for ( int y = 0; y < 9; y++)
	{
		for ( int x = 0; x < 9; x++)
		{
			if ( this->boardSpace[y][x] != 0 )
			{
				delete this->boardSpace[y][x];
				this->boardSpace[y][x] = 0;
			}
		}
	}
}

void Board::generateRandomBoard()
{
	for(unsigned int y = 0; y < 9; y++)
	{
		for(unsigned int x = 0; x < 9; x++)
		{
			if ( checkValidBoardSpace(x,y) )
			{
				addBoardPiece(x, y, rand()%5+1);
			}
		}
	}
}

int Board::checkBoardColor(unsigned int x, unsigned int y)
{
	if ( checkValidBoardSpace(x,y) && boardSpace[y][x] != 0)
	{
		return boardSpace[y][x]->getColor();
	}
	else
	{
		return -1;
	}
}

bool Board::checkValidBoardSpace(unsigned int x, unsigned int y)
{
	// Special pieces that will always return false
	if ( (x == 0 && y == 0) || (x == 0 && y == 8) || (x == 8 && y == 0) || (x == 8 && y == 8))
	{
		return false;
	}
	// If its an odd row, and y == 8 (last row), we cannot have this so return false
	else if ( (x%2 > 0) && (y == 8) )
	{
		return false;
	}
	else if ( (x > 8) || (y > 8) )
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Board::addBoardPiece(unsigned int x, unsigned int y, int color)
{
	if ( x >= 9 || y >= 9 )
	{
		iprintf("Error, cannot exceed 9 width or height\n");
		return;
	}
	if ( this->boardSpace[y][x] == 0 )
	{
		// If x is even, we do not want to offset the y
		if ( x%2 == 0 )
		{
			this->boardSpace[y][x] = new Piece((x*23+20),(y*20), color, spritePtr, true);
		}
		// Else x is odd, we do want to offset the y
		else
		{
			this->boardSpace[y][x] = new Piece((x*23+20),(y*20+10), color, spritePtr, true);
		}
	}
	else
	{
		iprintf("Board space is not empty!\n");
	}
}

void Board::removeBoardPiece(unsigned int x, unsigned int y)
{
	if ( this->boardSpace[y][x] != 0 )
	{
		delete this->boardSpace[y][x];
		this->boardSpace[y][x] = 0;
		this->boardSpaceState[y][x] = PIECE_STATE_INACTIVE; // piece is now inactive
		// We also need to remove the sprite
	}
}

u8 Board::getPieceState(unsigned int x, unsigned int y)
{
	return this->boardSpaceState[y][x]; 
}

// Board update function goes through the board & looks for "Active" spaces, or spaces
// that are marked for removal in this case.
void Board::Update()
{
	if ( boardState == BOARD_UPDATE )
	{
		for(int y=0; y<9; y++)
		{
			for(int x=0; x<9; x++)
			{
				if ( this->boardSpaceState[y][x] == PIECE_STATE_ACTIVE )
				{
					// Possbily set our board state to transitioning!
					
					// Remove this piece
					removeBoardPiece(x,y);
					boardState = BOARD_ANIMATE;
				}
			}
		}
	}
	else if ( boardState == BOARD_ANIMATE )
	{
		boardState = BOARD_REFILL;
	}
	else if ( boardState == BOARD_REFILL )
	{
		for(int y=0; y < 9; y++)
		{
			for(int x=0; x<9; x++)
			{
				if ( checkValidBoardSpace(x,y) && this->boardSpace[y][x] == 0 )
				{
					// Move all our pieces above this one down
					for(int tempY=y;tempY>0;tempY--)
					{
						if ( this->boardSpace[tempY-1][x] != 0 )
						{
							this->boardSpace[tempY][x] = this->boardSpace[tempY-1][x];
							this->boardSpace[tempY-1][x] = 0;
							if(x%2 == 0)
								this->boardSpace[tempY][x]->setLocation((x*23+20),(tempY*20));
							else
								this->boardSpace[tempY][x]->setLocation((x*23+20),(tempY*20+10));
						}
					}
					if ( x > 0 && x < 8 )
					{
						addBoardPiece(x,0,rand()%5+1);
					}
					else
					{
						addBoardPiece(x,1,rand()%5+1);
					}
				}
			}
		}
		boardState = BOARD_IDLE;
	}
}

// Two arrays we use as helpers for our explodepiece functions
int explodeXArray[6] = {-1,-1,0,0,1,1};
int explodeYArray[6][2] = {{-1,0}, {0,1}, {-1,-1}, {1,1}, {-1,0}, {0,1}};

int Board::explodePiece(unsigned int x, unsigned int y)
{
	boardState = BOARD_UPDATE;
	return explodePieceRecursive(x,y);
}

// Explode Piece
// The meat & potatoes of this entire game. The user clicks on a piece, which recursively
// goes through all the conncted pieces, looking for matches. When it finds matches,
// it marks the pieces as active, then removes them.
int Board::explodePieceRecursive(unsigned int x, unsigned int y)
{
	if ( this->checkValidBoardSpace(x,y) )
	{
		int blockCount = 1; // how many blocks we exploded
		int explodingColor = checkBoardColor(x,y);
		int isEven = x%2;
		
		boardSpaceState[y][x] = PIECE_STATE_ACTIVE;
		
		// Do some exploding logic here!
		for (int i = 0; i < 6; i++)
		{
			int bx = x+explodeXArray[i];
			int by = y+explodeYArray[i][isEven];
			if (this->checkValidBoardSpace(bx,by) && getPieceState(bx,by)==PIECE_STATE_INACTIVE)
			{
				if ( explodingColor == checkBoardColor(bx,by) )
				{
					// Recursive adding
					blockCount += explodePiece(bx,by);
				}
			}
		}
		return blockCount;
	}
	else
	{
		return -1;
	}
}
