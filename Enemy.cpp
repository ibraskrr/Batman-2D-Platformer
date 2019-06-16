#include "Enemy.h"
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <iostream>
#include <math.h>


void Enemy::display() {

	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	finishedAttack = false;
	if (isDead) {
		if (timerDead % 80 == 0) {
			glBindTexture(GL_TEXTURE_2D, dead[deadCounter]);
			deadCounter++;
		}
		else {
			glBindTexture(GL_TEXTURE_2D, dead[deadCounter]);
		}
		timerDead++;
		if (deadCounter > 3) {
			deadCounter = 3;
			timerDead = 0;
		}
	}
	else {
		if (attacking) {
			if (timerAttacking % 50 == 0) {
				glBindTexture(GL_TEXTURE_2D, attack[attackingCounter]);
				attackingCounter++;
			}
			else {
				glBindTexture(GL_TEXTURE_2D, attack[attackingCounter]);
			}
			timerAttacking++;
			if (attackingCounter > 4) {
				attackingCounter = 0;
				timerAttacking = 0;
				attacking = false;
				finishedAttack = true;
			}
		}
		else {
			if (timerWalking % 50 == 0) {
				glBindTexture(GL_TEXTURE_2D, walking[walkingCounter]);
				walkingCounter++;
			}
			else {
				glBindTexture(GL_TEXTURE_2D, walking[walkingCounter]);
			}
			timerWalking++;
			if (walkingCounter > 5) {
				walkingCounter = 0;
				timerWalking = 0;
			}
		}
	}
	glTranslatef(Xpos, Ypos, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	float xtemp = 0.0;
	if (isDead) {
		xtemp = -10.0;
	}
	float temp = 0;
	if (attackingCounter >= 5) {
		temp = 5.0;
	}
	if (facingLeft) {
		glTexCoord2f(1.0, 0.0); glVertex2f(-4, 0); //bottom left
		glTexCoord2f(0.0, 0.0); glVertex2f(8 + temp, 0); //bottom right
		glTexCoord2f(0.0, 1.0); glVertex2f(8 + temp, 25 + xtemp); //top right
		glTexCoord2f(1.0, 1.0); glVertex2f(-4, 25 + xtemp); //top left
		glEnd();
	}
	else {
		glTexCoord2f(0.0, 0.0); glVertex2f(-4, 0); //bottom left
		glTexCoord2f(1.0, 0.0); glVertex2f(8, 0); //bottom right
		glTexCoord2f(1.0, 1.0); glVertex2f(8, 25 + xtemp); //top right
		glTexCoord2f(0.0, 1.0); glVertex2f(-4, 25 + xtemp); //top left
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();
}
//void Enemy::drawEnemy() {
//	glTranslatef(xMove, 1.0, 0.0);
//	glPushMatrix();
//	glColor3f(1.0, 1.0, 1.0);
//	glBegin(GL_QUADS);
//	glTexCoord2f(0.0, 0.0); glVertex2f(400.0, 20.0);
//	glTexCoord2f(0.0, 1.0); glVertex2f(400.0, 80.0);
//	glTexCoord2f(1.0, 1.0); glVertex2f(430.0, 80.0);
//	glTexCoord2f(1.0, 0.0); glVertex2f(430.0, 20.0);
//	glEnd();
//	glFlush();
//	glPopMatrix();
//
//	moveEnemy();
//
//}
//
//
//
//
//
//void Enemy::moveEnemy(void)
//{
//	switch (state)
//	{
//	case 1:
//		if (xMove < 190.0f)xMove += 2.0f;
//		else
//			state = -1;
//		break;
//	case -1:
//		if (xMove >= 8.0f)xMove -= 2.0f;
//		else
//			state = 1;
//		break;
//	}
//
//
//	//else if (xMove <= 0.0f)xMove -= 3.0f;
//
//	//if (xMove <= 190.0f)xMove -= 2.0f; //lessthan
//
//	//else if (xMove <= 0.0f)xMove -= 3.0f;
//
//	/*(xMove = 190.0f);
//
//	{
//		xMove -= 2.0;
//	}
//*/
////cout << "-" <<xMove;
//}
