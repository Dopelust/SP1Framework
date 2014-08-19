// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
COORD charLocation;
COORD missileRLocation;
COORD missileLLocation;
COORD enemyLocation; 
COORD consoleSize;
bool createMissileL = 0;
bool createMissileR = 0;
bool createEnemy = 1 ;

void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set the character to be in the center of the screen.
    charLocation.X = 0;
    charLocation.Y = consoleSize.Y / 2;  

	enemyLocation.X = 72; 
	enemyLocation.Y = rand() % 20 ; 

    elapsedTime = 0.0;
}

void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
    keyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
}

void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    // Updating the location of the character based on the key press
    if (keyPressed[K_UP] && charLocation.Y > 0)
    {
        charLocation.Y--; 
    }

    if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 1)
    {
        charLocation.Y++; 
    }

	if (keyPressed[K_SPACE])
    {
		if (createMissileR == 0)
		{
			Beep(10,200);
			createMissileR = 1;
			missileRLocation.X = charLocation.X;
			missileRLocation.Y = charLocation.Y + 1;
		}

		else if (createMissileR == 1 && createMissileL == 0)
		{
			Beep(10,200);
			createMissileL = 1;
			missileLLocation.X = charLocation.X;
			missileLLocation.Y = charLocation.Y + 1;
		}
	}

	if (createMissileR == 1)
	{
		missileRLocation.X+=8;

		if (missileRLocation.X > consoleSize.X - 1)
		{
			createMissileR = 0;
			missileRLocation.X = charLocation.X + 8;
			missileRLocation.Y = charLocation.Y + 1;
		}
	}

	else
	{
		missileRLocation.X = charLocation.X + 8 ;
		missileRLocation.Y = charLocation.Y + 1 ;
	}

	if (createMissileL == 1)
	{
		missileLLocation.X+=8;

		if (missileLLocation.X > consoleSize.X - 1)
		{
			createMissileL = 0;
			missileLLocation.X = charLocation.X;
			missileLLocation.Y = charLocation.Y + 1;
		}
	}

	else
	{
		missileLLocation.X = charLocation.X;
		missileLLocation.Y = charLocation.Y + 1;
	}

	if (createEnemy == 1)
	{
		enemyLocation.X--;

		if ( (enemyLocation.X < missileRLocation.X && enemyLocation.Y == missileRLocation.Y) || (enemyLocation.X < missileLLocation.X && enemyLocation.Y == missileLLocation.Y)) 
		{ 
			enemyLocation.X = consoleSize.X - 5;
			enemyLocation.Y = rand() % 20;
		} 

		if (enemyLocation.X < 5 )
		{
			createEnemy = 1;
			enemyLocation.X = consoleSize.X - 5;
			enemyLocation.Y = rand() % 20;
		}
	}


    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
	{
        g_quitGame = true;    
	}
}

void render()
{
    // clear previous screen
    colour(0x0F);
    cls();

    //render the game

    //render test screen code (not efficient at all)
    const WORD colors[] =   {
	                        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
	                        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6,
							0xFA, 0xFB, 0xFC, 0xFD
	                        };
	/*
	for (int i = 0; i < 16; ++i)
	{
		gotoXY(3*i,i+1);
		colour(colors[i]);
		std::cout << "Fuck";
	}
	*/

    // render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x0A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;

	/*
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;
	*/

    // render character

	gotoXY(enemyLocation); 
	colour(0x0C); 
	std::cout << "Enemy" ; 

    gotoXY(charLocation);
    colour(0x09);
    std::cout << "     |\_________________,_" << std::endl;
	std::cout << "     |     ==== _______)__)"  << std::endl;
	std::cout << "   __/___  ====_/" << std::endl;

	gotoXY(missileRLocation);
	colour(0x0C);  
	std::cout << "--====>>"; 

	gotoXY(missileLLocation);
	colour(0x0C);
	std::cout << "--====>>";




}
