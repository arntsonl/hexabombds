#ifndef __GFX_H_
#define __GFX_H_

#include <nds.h>

#include "spriteMan.h"
#include "tileMan.h"

// TODO: Replace this with a state machine!! booyah
enum GraphicTypes {TITLE=0, MENU, IN_GAME};

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	void SetMode(int);
	int GetMode() { return currentMode; }
	void SetDefaultConsole();
	void SetDefaultScene();
	void Update(); // do our buffer swapping here yo
	spriteMan * getSpriteManager() { return sManager; }
private:
	void Init();
	int currentMode;
	spriteMan * sManager;
	TileManager * tManager;
};

#endif  // __GFX_H_
