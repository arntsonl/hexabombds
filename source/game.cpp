#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <nds.h>
#include <time.h>

Game::Game()
{
	this->Init();
}

Game::~Game()
{
	delete gEngine;
	delete gameBoard;
	delete mainGUI;
	delete gPlayer;
}

void Game::Init()
{
	gEngine = new GraphicsEngine();
	// Set our graphics mode
	gEngine->SetMode(TITLE);
	// Set up some default console goodness
	
	srand ( time(NULL) );
	
	gameBoard = new Board(gEngine->getSpriteManager()); // x=0, y=0, color=2 (blue)
	gPlayer = new Player(gEngine->getSpriteManager(),gameBoard);	
	gameBoard->generateRandomBoard();
	
	mainGUI = new Gui(0,MAX_ENERGY,gEngine->getSpriteManager());

}

void Game::Run()
{
	while(1)
	{
		// check for the lid cover to close, if so we want to pause
		swiWaitForVBlank(); // Wait for VBlank
		gEngine->Update();  // swap buffers
		gameBoard->Update();
		// need a handle input debug function here!
		this->handleInput();
	}
}

void Game::handleInput()
{
	touchXY = touchReadXY();
	// Scan all the keys
	scanKeys();
	int pressed = keysDown();	// buttons pressed this loop
	int held = keysHeld();		// buttons currently held
	if ( pressed & KEY_LEFT )//|| held & KEY_LEFT)
	{
		gPlayer->moveLeft();
	}
	else if ( pressed & KEY_RIGHT )//|| held & KEY_RIGHT)
	{
		gPlayer->moveRight();
	}
	else if ( pressed & KEY_DOWN )//|| held & KEY_DOWN )
	{
		gPlayer->moveDown();
	}
	else if ( pressed & KEY_UP )//|| held & KEY_UP )
	{
		gPlayer->moveUp();
	}
	if ( pressed & KEY_TOUCH )
	{
		// User has just pushed down the DS screen
	}
	else if ( held & KEY_TOUCH )
	{
		// User is holding the DS screen stylus down 
	}
	
	if ( pressed & KEY_A )
	{
		gPlayer->explodeBlock();
	}
}
