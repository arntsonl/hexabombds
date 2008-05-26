#include "physicsactor.h"

#include <stdio.h>

physicsActor::physicsActor()
{
	isPlatformActor = false;
	isXVelocityNegative = isYVelocityNegative = false;
	posX = posY = velX = velY = accX = accY = FIXED_16(0);
	accelPositiveX = accelPositiveY = false;
	xSpeed = maxXSpeed = ySpeed = maxYSpeed = FIXED_16(0);
	friction = (u32)FIXED_16(DEFAULT_FRICTION);
}

physicsActor::~physicsActor()
{
}

void physicsActor::setPosition(int newX, int newY)
{
	posX = FIXED_16(newX);
	posY = FIXED_16(newY);
}

void physicsActor::accelLeft()
{
	accX = xSpeed;
	accelPositiveX = false;
}

void physicsActor::accelRight()
{
	accX = xSpeed;
	accelPositiveX = true;
}

void physicsActor::update()
{
	if (accX > 0x0)
	{
		if ( accelPositiveX == true )
		{
			// Move our actor in a linear fashion
			if ( isPlatformActor )
			{
				velX = accX; // or = speed;
				isXVelocityNegative = false;
			}
			// Move our actor in a true accel/veloc fashion
			else
			{
				velX += accX;
			}
		}
		else
		{
			if ( isPlatformActor )
			{
				velX = accX; // or = -speed;
				isXVelocityNegative = true;
			}
			else
			{
				velX -= accX;
			}
		}
		accX = 0x0;
	}
	if (accY > 0x0)
	{
		accY = 0x0;
	}
	if (!isXVelocityNegative)
	{
		posX = posX + velX;
		if ( isPlatformActor )
		{
			velX = 0x0;
		}
		else
		{
			velX -= friction;
			if ( velX < 0x0)
			{
				velX = 0x0;
			}
		}
	}
	else if (isXVelocityNegative)
	{
		posX = posX - velX;
		if ( isPlatformActor )
		{
			velX = 0x0;
		}
		else
		{
			velX += friction;
			if ( velX > 0x0)
			{
				velX = 0x0;
			}
		}
	}
	if (velY > 0x0)
	{
	}
	else if (velY < 0x0)
	{
	}
}

bool physicsActor::getFlip()
{
	return !isXVelocityNegative;
}

int physicsActor::getPosX()
{ 
	return (int)UINT_16(posX);
}

int physicsActor::getPosY()
{
	return (int)UINT_16(posY); 
}


