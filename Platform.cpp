#include "Platform.h"
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <iostream>
#include <math.h>


void Platform::display() {
	glPushMatrix();
	glTranslatef(Xpos, Ypos, 0.0);
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-30, 0);
	glVertex2f(-30, 10);
	glVertex2f(10, 10);
	glVertex2f(10, 0);
	glEnd();
	glPopMatrix();

	xLeft = -50;
	xRight = 50;
	yTop = -35;
	yBottom = -40;
}

void Platform::displayBackground() {
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, myTexture);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex2f(-100, -100);
	glTexCoord2f(1.0, 0.0); glVertex2f(-100, 100);
	glTexCoord2f(1.0, 2.0); glVertex2f(410, 100);
	glTexCoord2f(0.0, 2.0); glVertex2f(410, -100);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();

}
void Platform::displayGameOver() {
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, gameOver);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex2f(-100, -100);
	glTexCoord2f(1.0, 0.0); glVertex2f(100, -100);
	glTexCoord2f(1.0, 1.0); glVertex2f(100, 100);
	glTexCoord2f(0.0, 1.0); glVertex2f(-100, 100);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();
}

void Platform::displayPointer() {
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, gameOver);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	float temp = 0;
	if (menuPointer) {
		temp = -25;
	}
	else {
		temp = 0;
	}
	glTexCoord2f(0.0, 0.0); glVertex2f(-40, -22 + temp);
	glTexCoord2f(1.0, 0.0); glVertex2f(-20, -22 + temp);
	glTexCoord2f(1.0, 1.0); glVertex2f(-20, -32 + temp);
	glTexCoord2f(0.0, 1.0); glVertex2f(-40, -32 + temp);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();
}



