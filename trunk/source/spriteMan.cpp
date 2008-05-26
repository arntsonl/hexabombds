#include "spriteMan.h"

#include <stdio.h>
#include <string.h>

#include "highlightPiece.h"
#include "redPiece.h"
#include "bluePiece.h"
#include "orangePiece.h"
#include "greenPiece.h"
#include "yellowPiece.h"

spriteMan::spriteMan() : spriteCount(0)
{
	initSprites();
}

spriteMan::~spriteMan()
{
}

//turn off all the sprites
void spriteMan::initSprites(void)
{
	emptySprites();
	// setup palettes for balls
	for(int j=0;j<16; j++)
		SPRITE_PALETTE[j] = highlightPiecePal[j];
	for(int j=0;j<16; j++)
	{
		SPRITE_PALETTE[j+16] = redPiecePal[j];
		SPRITE_PALETTE_SUB[j+16] = redPiecePal[j];
	}
	for(int j=0;j<16; j++)
	{
		SPRITE_PALETTE[j+32] = bluePiecePal[j];
		SPRITE_PALETTE_SUB[j+32] = bluePiecePal[j];
	}
	for(int j=0;j<16; j++)
	{
		SPRITE_PALETTE[j+48] = orangePiecePal[j];
		SPRITE_PALETTE_SUB[j+48] = orangePiecePal[j];
	}
	for(int j=0;j<16; j++)
	{
		SPRITE_PALETTE[j+64] = greenPiecePal[j];
		SPRITE_PALETTE_SUB[j+64] = greenPiecePal[j];
	}
	for(int j=0;j<16; j++)
	{
		SPRITE_PALETTE[j+80] = yellowPiecePal[j];
		SPRITE_PALETTE_SUB[j+80] = yellowPiecePal[j];
	}
	for(int i = 0; i < 128; i++)
	{
		spriteID[i] = PIECE_INACTIVE;
		subspriteID[i] = PIECE_INACTIVE;
	}
}

int spriteMan::addSubSprite(int x, int y, int color)
{
	int curSprNum = 0;
	// search for open sprites
	for(int i = 0; i < 128; i++)
	{
		if ( subspriteID[i] == PIECE_INACTIVE )
		{
			curSprNum = i; // used for gfx offset
			subspriteID[i] = color; // just give us some arbitrary number
			subsprites[i].attribute[0] = ATTR0_COLOR_16 | y;
			subsprites[i].attribute[1] = ATTR1_SIZE_32 | x;
			subsprites[i].attribute[2] = ATTR2_PALETTE(color) | (((curSprNum) << 4)); // << 4 = * 16, tiles are now 8
			break;
		}
	}
	// Colors - 32x32=1024  Highlight - 64x64 = 4096
	if ( color == PIECE_RED )
	{
		for ( int i = 0; i < 256; i++)
		{
			SPRITE_GFX_SUB[i+(curSprNum*256)]=redPieceTiles[i];
		}
	}
	if ( color == PIECE_BLUE )
	{
		for ( int i = 0; i < 256; i++)
		{
			SPRITE_GFX_SUB[i+(curSprNum*256)]=bluePieceTiles[i];
		}
	}
	else if ( color == PIECE_ORANGE )
	{
		for ( int i = 0; i < 256; i++)
		{
			SPRITE_GFX_SUB[i+(curSprNum*256)]=orangePieceTiles[i];
		}
	}
	else if ( color == PIECE_GREEN )
	{
		for ( int i = 0; i < 256; i++)
		{
			SPRITE_GFX_SUB[i+(curSprNum*256)]=greenPieceTiles[i];
		}
	}
	else if ( color == PIECE_YELLOW )
	{
		for ( int i = 0; i < 256; i++)
		{
			SPRITE_GFX_SUB[i+(curSprNum*256)]=yellowPieceTiles[i];
		}
	}
	return curSprNum; // gives us an ID of the actual sprite
}

// THIS ONLY WORKS FOR OUR 8x8 16-bit business.
int spriteMan::addSprite(int x, int y, int color)
{
	int curSprNum = 0;
	// search for open sprites
	for(int i = 0; i < 128; i++)
	{
		if ( spriteID[i] == PIECE_INACTIVE )
		{
			curSprNum = i-1; // used for gfx offset
			spriteID[i] = color; // just give us some arbitrary number
			sprites[i].attribute[0] = ATTR0_COLOR_16 | y;
			if ( color != PIECE_HIGHLIGHT )
			{
				sprites[i].attribute[1] = ATTR1_SIZE_32 | x;
				sprites[i].attribute[2] = ATTR2_PALETTE(color) | (((curSprNum) << 2) + 16); // << 2 = * 4, tiles are now 16
			}
			else
			{
				sprites[i].attribute[1] = ATTR1_SIZE_64 | x;
				sprites[i].attribute[2] = ATTR2_PALETTE(color) | 0;
			}
			break;
		}
	}
	if ( color == PIECE_HIGHLIGHT )
	{
		for( int j=0; j<1024; j++)
		{
			SPRITE_GFX[j] = highlightPieceTiles[j];
		}
	}
	// Colors - 32x32=1024  Highlight - 64x64 = 4096
	else if ( color == PIECE_RED )
	{
		for ( int i = 0; i < 256; i++)
		{
			SPRITE_GFX[i+(curSprNum*256)+1024]=redPieceTiles[i];
		}
	}
	else if ( color == PIECE_BLUE )
	{
		for ( int i = 0; i < 256; i++)
		{
			SPRITE_GFX[i+(curSprNum*256)+1024]=bluePieceTiles[i];
		}
	}
	else if ( color == PIECE_ORANGE )
	{
		for ( int i = 0; i < 256; i++)
		{
			SPRITE_GFX[i+(curSprNum*256)+1024]=orangePieceTiles[i];
		}
	}
	else if ( color == PIECE_GREEN )
	{
		for ( int i = 0; i < 256; i++)
		{
			SPRITE_GFX[i+(curSprNum*256)+1024]=greenPieceTiles[i];
		}
	}
	else if ( color == PIECE_YELLOW )
	{
		for ( int i = 0; i < 256; i++)
		{
			SPRITE_GFX[i+(curSprNum*256)+1024]=yellowPieceTiles[i];
		}
	}
	return (curSprNum+1); // gives us an ID of the actual sprite
}

void spriteMan::moveSprite(int x, int y, int ID, bool facing)
{
	sprites[ID].attribute[1] &= 0xFE00;
	sprites[ID].attribute[1] |= (x & 0x01FF);
	
	sprites[ID].attribute[0] &= 0xFF00;
	sprites[ID].attribute[0] |= (y & 0x00FF);
	/*
	if ( facing == 0 )
	{
		sprites[ID].attribute[1] |= ATTR1_FLIP_X;
	}
	else if ( facing == 1 )
	{
		sprites[ID].attribute[1] &= ~ATTR1_FLIP_X;
	}
*/
}

void spriteMan::moveSubSprite(int x, int y, int ID, bool facing)
{
	subsprites[ID].attribute[1] &= 0xFE00;
	subsprites[ID].attribute[1] |= (x & 0x01FF);
	
	subsprites[ID].attribute[0] &= 0xFF00;
	subsprites[ID].attribute[0] |= (y & 0x00FF);
	
	if ( facing == 0 )
	{
		subsprites[ID].attribute[1] |= ATTR1_FLIP_X;
	}
	else if ( facing == 1 )
	{
		subsprites[ID].attribute[1] &= ~ATTR1_FLIP_X;
	}
}

void spriteMan::eraseSpriteID(int ID)
{
	sprites[ID].attribute[0] = ATTR0_DISABLED;
	sprites[ID].attribute[1] = 0;
	sprites[ID].attribute[2] = 0;
	sprites[ID].attribute[3] = 0;
	spriteID[ID] = PIECE_INACTIVE;
}

void spriteMan::emptySprites(void)
{
	for(int i = 0; i < 128; i++)
	{
	   sprites[i].attribute[0] = ATTR0_DISABLED;
	   sprites[i].attribute[1] = 0;
	   sprites[i].attribute[2] = 0;
	   sprites[i].attribute[3] = 0;
	   subsprites[i].attribute[0] = ATTR0_DISABLED;
	   subsprites[i].attribute[1] = 0;
	   subsprites[i].attribute[2] = 0;
	   subsprites[i].attribute[3] = 0;
	   // custom
	   spriteID[i] = PIECE_INACTIVE;
	   subspriteID[i] = PIECE_INACTIVE;
    }
}

//copy our sprite to object attribute memory
void spriteMan::updateOAM(void)
{
	DC_FlushAll();
    dmaCopy(sprites, OAM, 128 * sizeof(SpriteEntry));
	dmaCopy(subsprites, OAM_SUB, 128 * sizeof(SpriteEntry));
}
