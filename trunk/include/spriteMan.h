#pragma once

#include <nds.h>

typedef enum {
	PIECE_HIGHLIGHT = 0,
	PIECE_RED,
	PIECE_BLUE,
	PIECE_ORANGE,
	PIECE_GREEN,
	PIECE_YELLOW,
	PIECE_INACTIVE
};

class spriteMan
{
public:
	spriteMan();
	~spriteMan();
	int addSubSprite(int, int, int);
	int addSprite(int, int, int);  // x, y, color
	void moveSprite(int, int, int, bool); // move to x, move to y, ID, flip x?
	void moveSubSprite(int, int, int, bool);
	//void eraseSprite(pill*);	// erase sprite at ID
	void eraseSpriteID(int);
	void emptySprites();
	void updateOAM(void);
	void setSpritePalette(int,int);
private:
	void initSprites(void);
	int spriteID[128];
	int subspriteID[128];
	SpriteEntry sprites[128];
	SpriteEntry subsprites[128];
	int spriteCount;
};
