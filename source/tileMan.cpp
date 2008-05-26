#include "tileMan.h"

#include <stdio.h>

#include <nds.h>
#define POS2IDX(x, y)    (x + (y*32))

// from eKid
// Extend the background to 512x256, then use this for finding the position
// POS2EXTENDIDX ((x & 31) + (y*32) + (x/32)*1024

#define TILE_FLIP_NONE    (0<<10)
#define TILE_FLIP_X       (1<<10)
#define TILE_FLIP_Y       (2<<10)
#define TILE_FLIP_XY      (TILE_FLIP_X | TILE_FLIP_Y)

TileManager::TileManager()
{
	cameraX = cameraY = 0;
	currentX = currentY = 1; // should never equal this?
	dataPtrX = dataPtrY = 0x0;
}
	
TileManager::~TileManager()
{
}

void TileManager::setCamera(u32 newX, u32 newY)
{
	cameraX = newX;
	cameraY = newY;
}
	
void TileManager::updateCamera(u32 newX, u32 newY)
{
	cameraX = newX;
	cameraY = newY;
	this->updateMapData();
}

void TileManager::loadTileSet(u8* newTileSet, u32 maxX, u32 maxY)
{
	if ( newTileSet != 0)
	{
		mapPointer = newTileSet;
	}
}

void TileManager::updateMapData()
{
/*
	if ( this->cameraX != this->currentX )
	{
		if ( this->cameraY != this->currentY )
		{
			u16* main_map = (u16*)SCREEN_BASE_BLOCK(1);
			// x & y are different
			this->currentX = cameraX;
			this->currentY = cameraY;
			int scrollX = (currentX % 8);
			BG0_X0 = scrollX;
			int scrollY = (currentY % 8);
			BG0_Y0 = scrollY;
			if ( scrollX == 0 || scrollY == 0 )
			{
				int tileNum;
				int xOffset = cameraX/8;
				int yOffset = cameraY/8;
				for(int y = 0; y < 24; y++) // 192  = 24 x 8 // write each tile
				{
					for(int x = 0; x < 32; x++) // 256 = 32 x 8 // write each tile
					{
						int currentXMap = (x + xOffset) / 4;
						int currentYMap = (y + yOffset) / 4;
						tileNum = testMap_map0[(currentXMap)+((currentYMap)*testMap_maxWidth)];
						main_map[POS2IDX(x,y)] = tileNum*4+(x+xOffset)%4+((y+yOffset)%4*32); // 32 = 32x32 meta tile
					}
				}
			}
		}
		else
		{
			u16* main_map = (u16*)SCREEN_BASE_BLOCK(1);
			// x is different, y is the same
			this->currentX = cameraX;
			int scrollX = (currentX % 8);
			BG0_X0 = scrollX;
			if ( scrollX == 0 )
			{
				int tileNum;
				int xOffset = cameraX/8;
				int yOffset = cameraY/8;
				for(int y = 0; y < 24; y++) // 192  = 24 x 8 // write each tile
				{
					for(int x = 0; x < 32; x++) // 256 = 32 x 8 // write each tile
					{
						int currentXMap = (x + xOffset) / 4;
						int currentYMap = (y + yOffset) / 4;
						tileNum = testMap_map0[(currentXMap)+((currentYMap)*testMap_maxWidth)];
						main_map[POS2IDX(x,y)] = tileNum*4+(x+xOffset)%4+((y+yOffset)%4*32); // 32 = 32x32 meta tile
					}
				}
			}
		}
	}
	else if ( this->cameraY != this->currentY )
	{
		u16* main_map = (u16*)SCREEN_BASE_BLOCK(1);
		// y is different, x is the same
		this->currentY = cameraY;
		int scrollY = (currentY % 8);
		BG0_Y0 = scrollY;

		if ( scrollY == 0 )
		{
			int tileNum;
			int xOffset = cameraX/8;
			int yOffset = cameraY/8;
			for(int y = 0; y < 24; y++) // 192  = 24 x 8 // write each tile
			{
				for(int x = 0; x < 32; x++) // 256 = 32 x 8 // write each tile
				{
					int currentXMap = (x + xOffset) / 4;
					int currentYMap = (y + yOffset) / 4;
					tileNum = testMap_map0[(currentXMap)+((currentYMap)*testMap_maxWidth)];
					main_map[POS2IDX(x,y)] = tileNum*4+(x+xOffset)%4+((y+yOffset)%4*32); // 32 = 32x32 meta tile
				}
			}
		}
	}
	*/
}
