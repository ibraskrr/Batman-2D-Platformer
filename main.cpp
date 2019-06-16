#include "Image_Loading/nvImage.h"
#include <windows.h>		// Header file for Windows
#include <iostream>
#include <gl\gl.h>			// Header file for the OpenGL32 Library
#include <gl\glu.h>			// Header file for the GLu32 Library
#include "Character.h"
#include <windows.h>	
#include <math.h>
#include <ctime>

int jumpTimer = 0;
int pressedTimer = 0;
int gameOverTimer = 0;
int	mouse_x = 0, mouse_y = 0;
int state1 = 1;
int state2 = 1;
int state3 = 1;
bool startGame = false;
bool done = false;
int killCounter = 0;
bool isGameOver = false;
int endGameCounter = 0;
Platform gameOver;
Platform pointer;
Platform startScreen;
using namespace std;
bool LeftPressed = false;
int screenWidth = 1000, screenHeight = 600;
bool keys[256];
Base base;
Platform platform1;
Platform platform2;
Platform platform3;
Platform platform4;
Platform background;
Character player;
Enemy enemy;
Enemy enemy2;
vector<Enemy> enemies;
lava lava;
bool playerUp, playerDown, playerRight, playerLeft = false;

clock_t currentTicks = 0.0;
clock_t previousTicks = 1;
float delta;


//OPENGL FUNCTION PROTOTYPES
void display();				//called in winmain to draw everything to the screen
void reshape(int width, int height);				//called when the window is resized
void init();				//called in winmain when the program starts.
void processKeys();
//called in winmain to process keyboard input
//void update();				//called in winmain to update variables
GLuint loadPNG(char* name);

void movementEnemy();				//Object Movements 
void movementPlatform();
/*************    START OF OPENGL FUNCTIONS   ****************/
GLuint loadPNG(char* name)
{
	// Texture loading object
	nv::Image img;

	GLuint myTextureID;

	// Return true on success
	if (img.loadImageFromFile(name))
	{
		glGenTextures(1, &myTextureID);
		glBindTexture(GL_TEXTURE_2D, myTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}

	else
		MessageBox(NULL, "Failed to load texture", "End of the world", MB_OK | MB_ICONINFORMATION);

	return myTextureID;
}

void display()
{
	// GameOver when killCounter hits 2
	if (killCounter == 2 || player.isDead) {
		isGameOver = true;
	}
	//Set clocks
	float currentTicks = clock();
	float deltaTicks = (float)(currentTicks / previousTicks);
	//Draw objects on screen
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix;
	if (player.Xpos >= 35 && gameOverTimer < 1000) {
		glTranslatef(base.Xpos, base.Ypos, 0);
	}
	background.displayBackground();
	base.display();
	player.display();
	enemies[0].display();
	enemies[1].display();
	platform1.display();
	platform2.display();
	platform3.display();
	platform4.display();
	lava.display();


	//If GameOver Display GameOver Screen
	if (isGameOver) {
		gameOverTimer++;
		if (gameOverTimer > 2500) {
			gameOver.displayGameOver();
		}
	}
	glPopMatrix;
	glFlush();

	//Make the enemies stay still if they are dead
	if (enemies[0].isDead) {
		enemies[0].Xpos = enemies[0].deadX;
	}
	if (enemies[1].isDead) {
		enemies[1].Xpos = enemies[1].deadX;
	}
	//Display start screen
	if (!startGame) {
		startScreen.displayGameOver();
		pointer.displayPointer();
	}

	//Player Collisions with objects
	player.collision(platform1);
	player.collision(platform2);
	player.collision(platform3);
	player.collision(platform4);
	player.collision(lava, base);
	player.playerWalking = false;

	//face enemeies in correct direction when attacking
	//Kill player if player is within distance
	for (int i = 0; i < enemies.size(); i++) {
		player.distancePlayer(enemies[i]);
		if (player.distanceToPlayer < 6 && !player.isDead) {
			if (player.Xpos < enemies[i].Xpos) {
				enemies[i].facingLeft = true;
			}
			else {
				enemies[i].facingLeft = false;
			}
			enemies[i].attacking = true;
		}
		if (enemies[i].finishedAttack && player.distanceToPlayer < 6) {
			player.isDead = true;
		}
	}
	if (player.Xpos == -75) {
		base.Xpos = 0;
	}
	if (player.Xpos > 400) {
		base.Xpos = -365.297;
	}

	player.update();
	//Paltform and Enemy movement functions
	movementEnemy();
	movementPlatform();

	//Set Delta
	previousTicks = currentTicks;
	delta = deltaTicks / (float)CLOCKS_PER_SEC;

}

void movementEnemy() {
	//Make Enemy move within X postions 
	switch (state1)
	{
	case 1:
		if (enemies[0].Xpos < 130 && !enemies[0].attacking) {
			enemies[0].Xpos += 5.5f * 1;
			enemies[0].facingLeft = false;
		}
		else
			state1 = 2;
		break;
	case 2:
		if (enemies[0].Xpos > 62 && !enemies[0].attacking) {
			enemies[0].Xpos -= 5.5f * 1;
			enemies[0].facingLeft = true;
		}
		else
			state1 = 1;
		break;
	}

	//Enemy 2 movement
	switch (state3)
	{
	case 1:
		if (enemies[1].Xpos < 400 && !enemies[1].attacking) {
			enemies[1].Xpos += 5.5f * 1;
			enemies[1].facingLeft = false;
		}
		else
			state3 = 2;
		break;
	case 2:
		if (enemies[1].Xpos > 264 && !enemies[1].attacking) {
			enemies[1].Xpos -= 1.1f * 1;
			enemies[1].facingLeft = true;
		}
		else
			state3 = 1;
		break;
	}
}

void movementPlatform() {
	//Make Platform4 move
	//When Player is on top of platform4, make player move with platform4
	switch (state2)
	{
	case 1:
		if (platform4.Xpos < 250) {
			platform4.Xpos += 2.2f * 1;
			if (player.Ypos == platform4.Ypos + 10) {
				if (player.Xpos > platform4.Xpos - 38 && player.Xpos < platform4.Xpos + 10) {
					player.Xpos += 2.2f * 1;
					base.Xpos -= 2.2f * 1;
				}
			}
		}
		else {
			state2 = 2;
		}
		break;

	case 2:
		if (platform4.Xpos > 175) {
			platform4.Xpos -= 2.2f * 1;
			if (player.Ypos == platform4.Ypos + 10) {
				if (player.Xpos > platform4.Xpos - 38 && player.Xpos < platform4.Xpos + 10) {
					player.Xpos -= 2.2f * 1;
					base.Xpos += 2.2f * 1;
				}
			}
		}
		else {

			state2 = 1;
		}
		break;

	}
}


void reshape(int width, int height)		// Resize the OpenGL window
{
	screenWidth = width; screenHeight = height;           // to ensure the mouse coordinates match 
														  // we will use these values to set the coordinate system
	float left = player.yBottom - (screenWidth / 2.0); // in your case this would be x - 400
	float top = player.xLeft - (screenHeight / 2.0); // and this would be y - 300
	float right = left + screenWidth;
	float bottom = top + screenHeight;
	glViewport(left, right, bottom, top);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	gluOrtho2D(-100, 100, -100, 100);           // set the coordinate system for the window

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}
void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//Set Player X & Y
	player.Xpos = -75;
	player.Ypos = -100;

	//Push Enemy into enemies vector
	enemies.push_back(enemy);
	enemies.push_back(enemy2);

	//Set Enemy X & Y
	enemies[0].Ypos = -10;
	enemies[1].Ypos = -90;
	enemies[0].facingLeft = false;

	//Set Platforms X & Y
	platform1.Xpos = -10;
	platform2.Xpos = 95;
	platform3.Xpos = 133;
	platform4.Xpos = 175;

	platform1.Ypos = -50;
	platform2.Ypos = -20;
	platform3.Ypos = -20;
	platform4.Ypos = -50;

	//LOAD IN TEXTURES
	//platform texture
	base.myTexture = loadPNG("platform.png");

	//CHARACTER TEXTURES
	//Player idle 
	player.playerIdleTex[0] = loadPNG("idleCharacter/idle0.png");
	player.playerIdleTex[1] = loadPNG("idleCharacter/idle1.png");
	player.playerIdleTex[2] = loadPNG("idleCharacter/idle2.png");
	player.playerIdleTex[3] = loadPNG("idleCharacter/idle3.png");
	player.playerIdleTex[4] = loadPNG("idleCharacter/idle4.png");
	player.playerIdleTex[5] = loadPNG("idleCharacter/idle5.png");
	player.playerIdleTex[6] = loadPNG("idleCharacter/idle6.png");
	player.playerIdleTex[7] = loadPNG("idleCharacter/idle7.png");
	player.playerIdleTex[8] = loadPNG("idleCharacter/idle8.png");
	player.playerIdleTex[9] = loadPNG("idleCharacter/idle9.png");

	//character moving
	player.playerRunningTex[0] = loadPNG("runningCharacter/runningCharacter0.png");
	player.playerRunningTex[1] = loadPNG("runningCharacter/runningCharacter1.png");
	player.playerRunningTex[2] = loadPNG("runningCharacter/runningCharacter2.png");
	player.playerRunningTex[3] = loadPNG("runningCharacter/runningCharacter3.png");
	player.playerRunningTex[4] = loadPNG("runningCharacter/runningCharacter4.png");
	player.playerRunningTex[5] = loadPNG("runningCharacter/runningCharacter5.png");
	player.playerRunningTex[6] = loadPNG("runningCharacter/runningCharacter6.png");
	player.playerRunningTex[7] = loadPNG("runningCharacter/runningCharacter7.png");
	player.playerRunningTex[8] = loadPNG("runningCharacter/runningCharacter8.png");
	player.playerRunningTex[9] = loadPNG("runningCharacter/runningCharacter9.png");


	//player Jump
	player.playerJumpingTex[0] = loadPNG("jumpCharacter/jumpCharacter0.png");
	player.playerJumpingTex[1] = loadPNG("jumpCharacter/jumpCharacter1.png");
	player.playerJumpingTex[2] = loadPNG("jumpCharacter/jumpCharacter2.png");
	player.playerJumpingTex[3] = loadPNG("jumpCharacter/jumpCharacter3.png");
	player.playerJumpingTex[4] = loadPNG("jumpCharacter/jumpCharacter4.png");
	player.playerJumpingTex[5] = loadPNG("jumpCharacter/jumpCharacter5.png");
	player.playerJumpingTex[6] = loadPNG("jumpCharacter/jumpCharacter6.png");
	player.playerJumpingTex[7] = loadPNG("jumpCharacter/jumpCharacter7.png");



	//player attack 
	player.playerMeleeTex[0] = loadPNG("meleeCharacter/melee0.png");
	player.playerMeleeTex[1] = loadPNG("meleeCharacter/melee1.png");
	player.playerMeleeTex[2] = loadPNG("meleeCharacter/melee2.png");
	player.playerMeleeTex[3] = loadPNG("meleeCharacter/melee3.png");
	player.playerMeleeTex[4] = loadPNG("meleeCharacter/melee4.png");
	player.playerMeleeTex[5] = loadPNG("meleeCharacter/melee5.png");
	player.playerMeleeTex[6] = loadPNG("meleeCharacter/melee6.png");
	player.playerMeleeTex[7] = loadPNG("meleeCharacter/melee7.png");
	player.playerMeleeTex[8] = loadPNG("meleeCharacter/melee8.png");
	player.playerMeleeTex[9] = loadPNG("meleeCharacter/melee9.png");

	//player dying 
	player.deadCharacterTex[0] = loadPNG("deadCharacter/deadCharacter0.png");
	player.deadCharacterTex[1] = loadPNG("deadCharacter/deadCharacter1.png");
	player.deadCharacterTex[2] = loadPNG("deadCharacter/deadCharacter2.png");
	player.deadCharacterTex[3] = loadPNG("deadCharacter/deadCharacter3.png");


	//enemy TEXTURES
	//Enemy Texture
	enemies[0].idle = loadPNG("Enemy/Idle1.png");

	//enemy walking textures
	enemies[0].walking[0] = loadPNG("Enemy/Walking1.png");
	enemies[0].walking[1] = loadPNG("Enemy/Walking2.png");
	enemies[0].walking[2] = loadPNG("Enemy/Walking3.png");
	enemies[0].walking[3] = loadPNG("Enemy/Walking4.png");
	enemies[0].walking[4] = loadPNG("Enemy/Walking5.png");
	enemies[0].walking[5] = loadPNG("Enemy/Walking6.png");

	//enemy attack textures
	enemies[0].attack[0] = loadPNG("Enemy/Attack/attack1.png");
	enemies[0].attack[1] = loadPNG("Enemy/Attack/attack2.png");
	enemies[0].attack[2] = loadPNG("Enemy/Attack/attack3.png");
	enemies[0].attack[3] = loadPNG("Enemy/Attack/attack4.png");
	enemies[0].attack[4] = loadPNG("Enemy/Attack/attack5.png");
	enemies[0].attack[5] = loadPNG("Enemy/Attack/attack5.png");

	//enemy dying textures
	enemies[0].dead[0] = loadPNG("Enemy/Dead/dead1.png");
	enemies[0].dead[1] = loadPNG("Enemy/Dead/dead2.png");
	enemies[0].dead[2] = loadPNG("Enemy/Dead/dead3.png");
	enemies[0].dead[3] = loadPNG("Enemy/Dead/dead4.png");

	//Enemy2 Texture
	enemies[1].idle = loadPNG("Enemy/Idle1.png");

	//enemy walking textures
	enemies[1].walking[0] = loadPNG("Enemy/Walking1.png");
	enemies[1].walking[1] = loadPNG("Enemy/Walking2.png");
	enemies[1].walking[2] = loadPNG("Enemy/Walking3.png");
	enemies[1].walking[3] = loadPNG("Enemy/Walking4.png");
	enemies[1].walking[4] = loadPNG("Enemy/Walking5.png");
	enemies[1].walking[5] = loadPNG("Enemy/Walking6.png");

	//enemy attack textures
	enemies[1].attack[0] = loadPNG("Enemy/Attack/attack1.png");
	enemies[1].attack[1] = loadPNG("Enemy/Attack/attack2.png");
	enemies[1].attack[2] = loadPNG("Enemy/Attack/attack3.png");
	enemies[1].attack[3] = loadPNG("Enemy/Attack/attack4.png");
	enemies[1].attack[4] = loadPNG("Enemy/Attack/attack5.png");
	enemies[1].attack[5] = loadPNG("Enemy/Attack/attack5.png");

	//enemy dying textures
	enemies[1].dead[0] = loadPNG("Enemy/Dead/dead1.png");
	enemies[1].dead[1] = loadPNG("Enemy/Dead/dead2.png");
	enemies[1].dead[2] = loadPNG("Enemy/Dead/dead3.png");
	enemies[1].dead[3] = loadPNG("Enemy/Dead/dead4.png");

	//Background Texture
	background.myTexture = loadPNG("background.png");

	//Start menu texture
	pointer.gameOver = loadPNG("pointer.png");

	//gameOver Screen texture
	gameOver.gameOver = loadPNG("GameOver.png");

	//start Screen background texture
	startScreen.gameOver = loadPNG("startScreen.png");

	//lava Texture
	lava.myTexture = loadPNG("lava.png");

	//Set lava X & Y
	lava.Ypos = -90;
	lava.Xpos = 200;
}

void processKeys()
{
	if (keys[VK_LEFT] && !player.isDead)
	{
		if (startGame) {
			//Set player to walk and face left when left is pressed
			player.playerWalking = true;
			player.facingLeft = true;
			// Move player according to player X values
			if (base.Xpos >= 35 || player.Xpos > 35) {
				player.Xpos -= 5.0 * 1;
				base.Xpos += 5.0 * 1;
			}
			else
				player.Xpos -= 5.08f * 1;
		}
	}


	if (keys[VK_RIGHT] && !player.isDead)
	{
		if (startGame) {
			//Set Player to walk and face right when right is pressed
			player.playerWalking = true;
			player.facingLeft = false;
			// Move player according to player X
			if (base.Xpos > 35 || player.Xpos > 35) {
				player.Xpos += 5.08f * 1;
				base.Xpos -= 5.08f * 1;
			}
			else {
				player.Xpos += 5.08f * 1;
			}
		}
	}


	if (keys[VK_UP] && player.canJump && !player.isDead)
	{
		//Set menu pOINTER to move Pointer up
		if (!startGame && pointer.menuPointer) {
			pointer.menuPointer = false;
		}
		else if (startGame) {
			//Set player to jumping and move player upwards
			player.playerWalking = false;
			player.playerJumping = true;
			player.Ypos += 5.5f * 1;
			if (player.Ypos > 10) {
				player.canJump = false;
			}
		}

	}

	if (keys[VK_RETURN])
	{
		//Start Game when Pointer is over Start
		if (!startGame) {
			if (!pointer.menuPointer) {
				startGame = true;
			}
			// End Game is pointer is at exit
			else {
				done = true;
			}
		}
	}

	if (keys[VK_DOWN])
	{
		//Move pointer down
		if (!startGame && !pointer.menuPointer) {
			pointer.menuPointer = true;
			cout << pointer.menuPointer << endl;
		}
	}


	if (keys[VK_SPACE] && player.canJump && !player.isDead)
	{
		//Set menu pointer to move pointer up
		if (!startGame && pointer.menuPointer) {
			pointer.menuPointer = false;
		}
		else if (startGame) {
			//Set player to jumping and move player upwards
			player.playerWalking = false;
			player.playerJumping = true;
			player.Ypos += 20.0f*1;
			if (player.Ypos > 10) {
				player.canJump = false;
			}
		}
	}



	if (keys['A'] && !player.isDead)
	{

		if (!player.playerJumping && !player.playerWalking) {
			player.attacking = true;
			for (int i = 0; i < enemies.size(); i++)
				if (!enemies.at(i).isDead) {
					player.distance(enemies[i]);
					cout << player.distanceEnemy << " " << player.finishedAttack << endl;
					if (player.distanceEnemy < 9 && player.finishedAttack) {
						enemies[i].isDead = true;
						enemies[i].deadX = enemies[i].Xpos;
						killCounter++;
					}
				}
		}

	}
	//	cout << "walkingK: " << player.walking << endl;

	/*If yo're jumping, divide MaxJump by Gravity so it will slowly get smaller, and add MaxJump to y so the character moves up*/
	/*if (player.Jumping)
	{
		player.MaxJump /= player.Gravity;
		player.y += player.MaxJump;
	}
	//If MaxJump has run out, our character is no longer jumping, but falling
	if (player.MaxJump <= 0)
	{
		player.Falling = true;
		player.Jumping = false;
	}

	//Opposite of Jumping
	if (player.Falling)
	{
		player.MaxJump *= player.Gravity;
		player.y -= player.MaxJump;
	}
	//Keeps MaxJump from getting higher than 4, so the character doesn't fall at large intervals.
	if (player.Falling && player.MaxJump > 3)
		player.MaxJump = 4;

	//If the block is back to it's y origin, make both jumping and falling false, and assign MaxJump to constant SubMaxJump to restore it back to normal. It's not okay to jump again unless you release the UP key, and then press it again.
	if (player.y <= player.yOrigin)
	{
		player.Jumping = false;
		player.Falling = false;
		player.MaxJump = player.SubMaxJump;
		if (keys[VK_SPACE] == false)
			player.JumpOK = true;
	}*/

}
/**************** END OPENGL FUNCTIONS *************************/

//WIN32 functions
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
void KillGLWindow();									// releases and destroys the window
bool CreateGLWindow(char* title, int width, int height); //creates the window
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);  // Win32 main function

//win32 global variabless
HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Context
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application


/******************* WIN32 FUNCTIONS ***************************/
int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
								// Bool Variable To Exit Loop


	AllocConsole();
	FILE *stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);

	// Create Our OpenGL Window
	if (!CreateGLWindow("OpenGL Win32 Example", screenWidth, screenHeight))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while (!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
			{
				done = true;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			if (keys[VK_ESCAPE])
				done = true;

			processKeys();			//process keyboard

			display();					// Draw The Scene
			//update();					// update variables
			SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (int)(msg.wParam);						// Exit The Program
}

//WIN32 Processes function - useful for responding to user inputs or other events.
LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
	UINT	uMsg,			// Message For This Window
	WPARAM	wParam,			// Additional Message Information
	LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
	case WM_CLOSE:								// Did We Receive A Close Message?
	{
		PostQuitMessage(0);						// Send A Quit Message
		return 0;								// Jump Back
	}
	break;

	case WM_SIZE:								// Resize The OpenGL Window
	{
		reshape(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
		return 0;								// Jump Back
	}
	break;

	case WM_LBUTTONDOWN:
	{
		mouse_x = LOWORD(lParam);
		mouse_y = screenHeight - HIWORD(lParam);
		LeftPressed = true;
	}
	break;

	case WM_LBUTTONUP:
	{
		LeftPressed = false;
	}
	break;

	case WM_MOUSEMOVE:
	{
		mouse_x = LOWORD(lParam);
		mouse_y = screenHeight - HIWORD(lParam);
	}
	break;
	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
		keys[wParam] = true;					// If So, Mark It As TRUE
		return 0;								// Jump Back
	}
	break;
	case WM_KEYUP:								// Has A Key Been Released?
	{
		keys[wParam] = false;					// If So, Mark It As FALSE
		return 0;								// Jump Back
	}
	break;
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void KillGLWindow()								// Properly Kill The Window
{
	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*/

bool CreateGLWindow(char* title, int width, int height)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;											// Return FALSE
	}

	dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
	dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		24,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		24,											// 24Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	reshape(width, height);					// Set Up Our Perspective GL Screen

	init();

	return true;									// Success
}



