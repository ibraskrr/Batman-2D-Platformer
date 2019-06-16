#include "lava.h"
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <iostream>
#include <math.h>


void lava::display() {
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, myTexture);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(Xpos, Ypos, 0.0);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex2f(-60, 0);
	glTexCoord2f(4.0, 0.0); glVertex2f(60, 0);
	glTexCoord2f(4.0, 1.0); glVertex2f(60, 10);
	glTexCoord2f(0.0, 1.0); glVertex2f(-60, 10);

	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);




}
