#pragma once

#include "helper.h"

#define DEFAULT_TILE_SIZE 1024 // 32*32

class TileManager
{
public:
	TileManager();
	~TileManager();
	void setCamera(u32,u32);
	void updateCamera(u32,u32);
	void loadTileSet(u8*,u32,u32);
private:
	// Used for changing the map data depending on the scroll & info
	void updateMapData();
	u8 * mapPointer;
	u8 mapData[DEFAULT_TILE_SIZE]; // default size
	u8 cameraX,cameraY;
	u8 currentX,currentY;
	u8 dataPtrX, dataPtrY;
};
