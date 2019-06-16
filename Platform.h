#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <iostream>
#include <math.h>

class Platform {
private:

public:
	float Xpos = 0;
	float Ypos = 0;
	float yTop;
	float yBottom;
	float xLeft;
	float xRight;
	bool menuPointer = false;
	GLuint myTexture = 0;
	GLuint gameOver = 0;
	void display();
	void displayBackground();
	void displayGameOver();
	void displayPointer();
};


