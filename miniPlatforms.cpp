//#include "header.h"
//
//
//miniPlatforms::miniPlatforms()
//{
//}
//
//
//miniPlatforms::~miniPlatforms()
//{
//}
//
//void miniPlatforms::drawminiPlatform1() {
//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, miniPlatformTex);
//	glPushMatrix();
//	glColor3f(1.0, 1.0, 1.0);
//	glBegin(GL_QUADS);
//	glTexCoord2f(0.0, 0.0); glVertex2f(250, 180.0); // A top left -
//	glTexCoord2f(0.5, 0.0); glVertex2f(250, 160.0); // B top right 
//	glTexCoord2f(0.5, 1.0); glVertex2f(450, 160.0); // C bottom right - 20 is the height off the the screen ( y axis +20)
//	glTexCoord2f(0.0, 1.0); glVertex2f(450, 180.0); // D bottom left
//	glEnd();
//	glPopMatrix();;
//	glDisable(GL_TEXTURE_2D);
//}
//
//void miniPlatforms::drawminiPlatform2() {
//	glPushMatrix();
//	glColor3f(1.0, 1.0, 1.0);
//	glBegin(GL_QUADS);
//	/*glTexCoord2f(0.0, 0.0);*/ glVertex2f(800, 270.0); // A top left -
//	/*glTexCoord2f(3.0, 0.0);*/ glVertex2f(800, 250.0); // B top right 
//	/*glTexCoord2f(3.0, 3.0);*/ glVertex2f(1150, 250.0); // C bottom right - 20 is the height off the the screen ( y axis +20)
//	/*glTexCoord2f(0.0, 3.0);*/ glVertex2f(1150, 270.0); // D bottom left
//	glEnd();
//	glPopMatrix();;
//}
//
//void miniPlatforms::drawminiPlatform3() {
//	glPushMatrix();
//	glColor3f(1.0, 1.0, 1.0);
//	glBegin(GL_QUADS);
//	/*glTexCoord2f(0.0, 0.0);*/ glVertex2f(1600, 180.0); // A top left -
//	/*glTexCoord2f(3.0, 0.0);*/ glVertex2f(1600, 160.0); // B top right 
//	/*glTexCoord2f(3.0, 3.0);*/ glVertex2f(1800, 160.0); // C bottom right - 20 is the height off the the screen ( y axis +20)
//	/*glTexCoord2f(0.0, 3.0);*/ glVertex2f(1800, 180.0); // D bottom left
//	glEnd();
//	glPopMatrix();;
//}
//
//void miniPlatforms::drawminiPlatform4() {
//	glPushMatrix();
//	glColor3f(1.0, 1.0, 1.0);
//	glBegin(GL_QUADS);
//	/*glTexCoord2f(0.0, 0.0);*/ glVertex2f(1650, 400.0); // A top left -
//	/*glTexCoord2f(3.0, 0.0);*/ glVertex2f(1650, 380.0); // B top right 
//	/*glTexCoord2f(3.0, 3.0);*/ glVertex2f(1800, 380.0); // C bottom right - 20 is the height off the the screen ( y axis +20)
//	/*glTexCoord2f(0.0, 3.0);*/ glVertex2f(1800, 400.0); // D bottom left
//	glEnd();
//	glPopMatrix();;
//}
