#ifndef __GAME_H_
#define __GAME_H_

#include "gfx.h"
#include "board.h"
#include "gui.h"
#include "player.h"

class Game
{
public:
	Game();
	~Game();
	void Run();
private:
	void Init();
	void handleInput();
	GraphicsEngine * gEngine;
	Gui * mainGUI;
	Board * gameBoard;
	touchPosition touchXY;
	Player * gPlayer;
};

#endif
