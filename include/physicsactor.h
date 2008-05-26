#pragma once

#include "helper.h"

class physicsActor
{
public:
	physicsActor();
	~physicsActor();
	
	void setPlatformer() { isPlatformActor = true; } // tell physics that our actor has constant velocity
	
	void setXSpeed(u32 inSpeed) { xSpeed = inSpeed; }
	u32 getXSpeed() { return xSpeed; }
	
	void setXMaxSpeed(u32 newMax) { maxXSpeed = newMax; }
	u32 getXMaxSpeed() { return maxXSpeed; }

	void setYSpeed(u32 inSpeed) { ySpeed = inSpeed; }
	u32 getYSpeed() { return ySpeed; }
	
	void setYMaxSpeed(u32 newMax) { maxYSpeed = newMax; }
	u32 getYMaxSpeed() { return maxYSpeed; }

	
	void setPosition(int, int); // set position of our physics actor
	void setFriction(u32);
	
	int getPosX();
	int getPosY();
	
	bool getFlip();
	
	void accelLeft(); // move left by speed
	void accelRight(); // move right by speed
	
	void update(); // update our actor
private:

// This actor is designed to move left right & jump up and down

// Other actors might use an angle & velocity vector, we're going
// to stick with polar coordinates for now.

	u32 posX,posY;
	u32 velX,velY;
	u32 accX,accY;
	bool isXVelocityNegative, isYVelocityNegative;
	bool accelPositiveX, accelPositiveY; // cheat used to make negative Fixed_16s
	bool isPlatformActor;
	u32 xSpeed, ySpeed;
	u32 maxXSpeed, maxYSpeed;
	u32 friction;
};
