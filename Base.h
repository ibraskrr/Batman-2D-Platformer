#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library

#include <math.h>

class Base {
public:
	GLuint myTexture = 0;
	float Xpos = 0;
	float Ypos = 0;

	void display();
};

