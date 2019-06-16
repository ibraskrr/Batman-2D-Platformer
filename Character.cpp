#include "Character.h"
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <iostream>
#include <math.h>
using namespace std;




void Character::display() {
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);

	if (isDead) {
		if (timerDead % 80 == 0) {
			glBindTexture(GL_TEXTURE_2D, deadCharacterTex[deadCounter]);
			deadCounter++;
		}
		else {
			glBindTexture(GL_TEXTURE_2D, deadCharacterTex[deadCounter]);
		}
		timerDead++;
		if (deadCounter > 3) {
			deadCounter = 3;
			timerDead = 0;
		}
	}
	else {
		if (playerWalking && !playerJumping) {
			if (timerWalking % 50 == 0) {
				glBindTexture(GL_TEXTURE_2D, playerRunningTex[walkingCounter]);
				walkingCounter++;
			}
			else {
				glBindTexture(GL_TEXTURE_2D, playerRunningTex[walkingCounter]);
			}
			timerWalking++;
			if (walkingCounter > 6) {
				walkingCounter = 0;
				timerWalking = 0;
			}
		}

		else if (!playerWalking && playerJumping) {
			if (timerWalking % 50 == 0) {
				glBindTexture(GL_TEXTURE_2D, playerJumpingTex[8]);
				jumpingCounter++;
			}
			else {
				glBindTexture(GL_TEXTURE_2D, playerJumpingTex[8]);
			}
			timerWalking++;
			if (jumpingCounter > 8) {
				jumpingCounter = 0;
				timerJumping = 0;
			}
		}
		else if (attacking) {
			if (timerAttacking % 80 == 0) {
				finishedAttack = false;
				glBindTexture(GL_TEXTURE_2D, playerMeleeTex[attackingCounter]);
				attackingCounter++;
			}
			else {
				finishedAttack = false;
				glBindTexture(GL_TEXTURE_2D, playerMeleeTex[attackingCounter]);
			}
			timerAttacking++;
			if (attackingCounter > 5) {
				attackingCounter = 0;
				timerAttacking = 0;
				attacking = false;
				finishedAttack = true;
			}

		}
		else {
			if (idleTextureTimer % 1 == 0) {
				glBindTexture(GL_TEXTURE_2D, playerIdleTex[idleTextureCounter]);
				idleTextureCounter++;
			}
			else
				glBindTexture(GL_TEXTURE_2D, playerIdleTex[idleTextureCounter]);
			idleTextureCounter++;
			if (idleTextureCounter > 9) {
				idleTextureCounter = 0;
				idleTextureTimer = 0;
			}
		}
	}

	glTranslatef(Xpos, Ypos, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	float temp = 0;
	if (isDead) {
		temp = -10.0;
	}
	float xtemp = 0.0;
	if (attackingCounter >= 4) {
		xtemp = 5.0;
	}
	if (facingLeft) {
		glTexCoord2f(1.0, 0.0); glVertex2f(-4 - xtemp, 0); //bottom left
		glTexCoord2f(0.0, 0.0); glVertex2f(8, 0); //bottom right
		glTexCoord2f(0.0, 1.0); glVertex2f(8, 25); //top right
		glTexCoord2f(1.0, 1.0); glVertex2f(-4 - xtemp, 25); //top left
		glEnd();
	}
	else {
		glTexCoord2f(0.0, 0.0); glVertex2f(-4, 0); //bottom left
		glTexCoord2f(1.0, 0.0); glVertex2f(8 + xtemp, 0); //bottom right
		glTexCoord2f(1.0, 1.0); glVertex2f(8 + xtemp, 25 + temp); //top right
		glTexCoord2f(0.0, 1.0); glVertex2f(-4, 25 + temp); //top left
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();

	if (Ypos > -90) {
		Ypos -= 0.003;
		cout << Ypos << endl;
	}
	if (Ypos <= -90) {
		Ypos = -90;
		playerJumping = false;
		canJump = true;
	}
}
void Character::distance(Enemy enemy) {
	float temp = 0;
	if (facingLeft) {
		temp = 6;
	}
	else
		temp = -6;
	distanceEnemy = sqrt(pow((enemy.Xpos - Xpos + temp), 2) + pow((enemy.Ypos - Ypos), 2));
}
void Character::distancePlayer(Enemy enemy) {
	float temp = 0;
	if (facingLeft) {
		temp = 6;
	}
	else
		temp = -6;
	distanceToPlayer = sqrt(pow((enemy.Xpos - Xpos + temp), 2) + pow((enemy.Ypos - Ypos), 2));
}
void Character::update() {
	if (Ypos > 13)
		this->playerFalling=true;
	if (playerFalling) {
		Ypos -= 5.0;
	}
	if (Ypos < -90) {
		playerFalling = false;
	}


	if (Xpos < -100) {
		Xpos = -100;
	}
	if (Xpos > 400) {
		Xpos = 400;
	}

}

void Character::collision(Platform platform) {


	//Head colliding with Bottom of platform collision
	if (Ypos > platform.Ypos - 25 && Ypos < platform.Ypos + 3) {
		if (Xpos > platform.Xpos - 38 && Xpos < platform.Xpos + 10) {
			Ypos = platform.Ypos - 25;
		}
	}
	//Bottom of character colliding with the top of platfrom collision
	if (Ypos > platform.Ypos + 3.5 && Ypos < platform.Ypos + 10)
		if (Xpos > platform.Xpos - 38 && Xpos < platform.Xpos + 12) {
			Ypos = platform.Ypos + 10;
			playerJumping = false;
			canJump = true;
		}

	/*	if (xLeft > platform.xLeft && xLeft < platform.xRight) {
			Ypos = platform.yBottom;

		}
		else if (xRight > platform.xLeft && xRight < platform.xRight) {
			yTop = platform.yBottom;
		}
	}*/


}

void Character::collision(lava lava, Base base) {
	if (Ypos > lava.Ypos - 5 && Ypos < lava.Ypos + 8) {
		if (Xpos > lava.Xpos - 64 && Xpos < lava.Xpos + 64) {
			Ypos = -90;
			Xpos = -75;
		}
	}
}



