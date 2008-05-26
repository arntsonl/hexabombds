#pragma once

#include "helper.h"
#include "piece.h"
#include "spriteMan.h"

#define MAX_LIVES 	4
#define MAX_ENERGY 	5

class Gui
{
public:
	Gui();
	Gui(int,int,spriteMan*); // score, energy, and sprite manager
	~Gui();
private:
	Piece * lifePieces[MAX_LIVES];
	int score;
	int energy;
};
