#include "gui.h"
#include <stdlib.h>

Gui::Gui()
{
}

Gui::Gui(int initialScore, int initialEnergy, spriteMan* spritePtr)
{
	score = initialScore;
	energy = initialEnergy;
	for(int i = 0; i < MAX_LIVES; i++)
	{
		lifePieces[i] = new Piece(187,46+i*28,rand()%5+1,spritePtr,false);
	}
}

Gui::~Gui()
{
	for(int i = 0; i < MAX_LIVES; i++)
	{
		if ( lifePieces[i] != 0 )
		{
			delete lifePieces[i];
		}
	}
}
