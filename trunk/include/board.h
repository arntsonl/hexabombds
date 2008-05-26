#pragma once

#include "helper.h"
#include "piece.h"
#include "spriteMan.h"
#include "stateMan.h"

class Board
{
public:
	Board();
	Board(spriteMan*);
	~Board();
	void generateRandomBoard();
	void addBoardPiece(unsigned int,unsigned int,int);
	void removeBoardPiece(unsigned int, unsigned int);
	int explodePiece(unsigned int,unsigned int);
	bool checkValidBoardSpace(unsigned int, unsigned int);
	int checkBoardColor(unsigned int, unsigned int);
	void Update();
private:
	int explodePieceRecursive(unsigned int, unsigned int); //helper recursive func
	u8 getPieceState(unsigned int, unsigned int);
	Piece * boardSpace[9][9]; // 9 tall, 9 wide containing the color
	u8 boardSpaceState[9][9]; // 9 tall, 9 wide telling what the state of the piece is? (active, inactive)
	u8 boardState;
	spriteMan * spritePtr;
};
