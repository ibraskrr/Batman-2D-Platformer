#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <math.h>
#include <iostream>
class Enemy
{
public:
	GLuint idle;
	GLuint walking[5];
	GLuint dead[3];
	GLuint attack[5];
	float Xpos;
	float Ypos = 0;
	int initX = 62;
	float deadX;
	int timerAttacking = 0;
	int attackingCounter = 0;
	int walkingCounter = 0;
	int timerWalking = 0;
	int deadCounter = 0;
	int timerDead = 0;
	float distancePlayer = 0;
	bool facingLeft = false;
	bool isDead = false;
	bool attacking = false;
	bool finishedAttack = false;

	float xMove = -10;
	float xMoveRight;
	float xMoveLeft;

	float right;
	float left;
	float x = 400;
	float dir = 0;

	void drawEnemy();
	void timer(int);
	void moveEnemy();
	int state = 1;



	void display();
};

