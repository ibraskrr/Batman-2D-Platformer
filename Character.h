#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include "Platform.h"
#include <math.h>
#include "lava.h"
#include "Base.h"
#include "Enemy.h"
#include <iostream>
//#include "Image_Loading/nvImage.h"

class Character {
private:

public:
	float Xpos = 0;
	float Ypos = 0;
	float yBottom = 0;
	float xLeft = 0;
	bool playerWalking = false;
	bool playerJumping = false;
	bool playerFalling = false;
	bool facingLeft = false;
	bool isDead = false;
	bool attacking = false;
	bool canJump = true;
	int walkingCounter = 0;
	int jumpingCounter = 0;
	int attackingCounter = 0;
	int timerWalking = 0;
	int timerJumping = 0;
	int timerAttacking = 0;
	int idleTextureTimer = 0; 
	int	idleTextureCounter = 0;
	GLuint playerIdleTex[10];
	GLuint playerJumpingTex[8];
	GLuint playerRunningTex[10];
	GLuint deadCharacterTex[4];
	GLuint playerMeleeTex[10];
	float distanceEnemy = 0;
	float distanceToPlayer = 0;
	int deadCounter = 0;
	int timerDead = 0;
	bool finishedAttack = false;

	void display();

	void distance(Enemy enemy);
	void distancePlayer(Enemy enemy);
	void update();
	void collision(Platform platform);
	void collision(lava lava, Base base);
};
