#include "gfx.h"

#include "font.h"
#include <string.h>
#include <stdio.h>
/*
#include "boardImage_bin.h"
#include "boardImagePal_bin.h"
#include "boardImageMap_bin.h"*/
#include "boardChaos_bin.h"
#include "boardChaosPal_bin.h"
#include "boardChaosMap_bin.h"
#include "topScreen_bin.h"
#include "topScreenPal_bin.h"
#include "topScreenMap_bin.h"

GraphicsEngine::GraphicsEngine()
{
	this->Init();
}

GraphicsEngine::~GraphicsEngine()
{
	delete sManager;
	delete tManager;
}

void GraphicsEngine::Init()
{
	//turn everything on
    powerON(POWER_ALL_2D);

	// irqs are nice
	irqInit();
	irqEnable(IRQ_VBLANK);
	
	sManager = new spriteMan();
	tManager = new TileManager();
}

void GraphicsEngine::SetMode(int screenType)
{
	currentMode = screenType;
	if ( screenType == TITLE )
	{	
		this->SetDefaultConsole();
	}
	else if ( screenType == MENU )
	{
	}
	else if ( screenType == IN_GAME )
	{
	}
}

void GraphicsEngine::SetDefaultConsole( )
{
	videoSetModeSub(MODE_0_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE | DISPLAY_SPR_ACTIVE |
		DISPLAY_BG_EXT_PALETTE | DISPLAY_SPR_1D);

	videoSetMode(MODE_5_2D | DISPLAY_SPR_ACTIVE | DISPLAY_BG0_ACTIVE | 
		DISPLAY_BG_EXT_PALETTE | DISPLAY_SPR_1D |
		DISPLAY_SPR_1D_SIZE_128 | DISPLAY_SPR_1D_BMP);

	vramSetBankA(VRAM_A_MAIN_SPRITE);
	vramSetBankB(VRAM_B_MAIN_BG_0x06000000);
	vramSetBankC(VRAM_C_SUB_BG_0x06200000);
	vramSetBankD(VRAM_D_SUB_SPRITE);

	unsigned int i;
	const int tile_base = 1;
	const int map_base = 0;
	const int bg_tile_base = 2;
	const int bg_map_base = 1;

	const int sub_main_tile_base = 5;
	const int sub_main_map_base = 6;

	BG0_CR = BG_256_COLOR | BG_TILE_BASE(bg_tile_base) | BG_MAP_BASE(bg_map_base);
	
	SUB_BG0_CR = BG_256_COLOR | BG_TILE_BASE(sub_main_tile_base) | BG_MAP_BASE(sub_main_map_base) | BG_PRIORITY(1);
	SUB_BG1_CR = BG_256_COLOR | BG_TILE_BASE(tile_base) | BG_MAP_BASE(map_base) | BG_PRIORITY(0);

	u16* main_tile = (u16*)CHAR_BASE_BLOCK_SUB(tile_base);
	u16* main_map = (u16*)SCREEN_BASE_BLOCK_SUB(map_base);

	//95 and 32 show how many characters there are and 32 shows which ASCII character to start, respectively
	//95 is the smaller set of ACSII characters. It usually will start with 32
	consoleInit((u16*)fontData, main_tile, 95, 32, main_map, CONSOLE_USE_COLOR255, 8);
    
	//Load the Font Data and Palette stuff here
	for(i = 0; i < fontDataSize; ++i) {
		main_tile[i] = fontData[i];
	}
	
	DC_FlushAll();
	
	dmaCopy(boardChaos_bin,(void*)BG_TILE_RAM(bg_tile_base),boardChaos_bin_size);

	dmaCopy(boardChaosMap_bin,(void*)SCREEN_BASE_BLOCK(bg_map_base), boardChaosMap_bin_size);

	dmaCopy(topScreen_bin,(void*)BG_TILE_RAM_SUB(sub_main_tile_base), topScreen_bin_size);

	dmaCopy(topScreenMap_bin, (void*)SCREEN_BASE_BLOCK_SUB(sub_main_map_base), topScreenMap_bin_size);
	
	// Set our Vram E to Main Screen's Palette
	vramSetBankE(VRAM_E_LCD);
	dmaCopy(boardChaosPal_bin, VRAM_E_EXT_PALETTE[0][0], boardChaosPal_bin_size);
	vramSetBankE(VRAM_E_BG_EXT_PALETTE);
	
	// Set our Vram H to Sub Screen's Palette
	vramSetBankH(VRAM_H_LCD);
	dmaCopy(fontPalette, VRAM_H_EXT_PALETTE[1][0], fontPaletteSize);
	dmaCopy(topScreenPal_bin, VRAM_H_EXT_PALETTE[0][0], topScreenPal_bin_size);
	vramSetBankH(VRAM_H_SUB_BG_EXT_PALETTE);
	
}

void GraphicsEngine::SetDefaultScene()
{
}

void GraphicsEngine::Update()
{
	sManager->updateOAM();
}

