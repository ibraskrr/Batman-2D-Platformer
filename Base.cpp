#include "Base.h"
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <iostream>
#include <math.h>


void Base::display() {


	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, myTexture);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glTranslatef(Xpos, Ypos, 0.0);
	glColor3f(0.0, 1.0, 0.0);

	glTexCoord2f(0.0, 0.0); glVertex2f(-500, -100);
	glTexCoord2f(0.0, 1.0); glVertex2f(-500, -90);
	glTexCoord2f(100.0, 1.0); glVertex2f(1000, -90);
	glTexCoord2f(100.0, 0.0); glVertex2f(1000, -100);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();
}