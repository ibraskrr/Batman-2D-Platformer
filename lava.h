#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library

#include <math.h>

class lava {
public:
	float Xpos = 0;
	float Ypos = 0;
	GLuint myTexture = 0;
	GLuint Texture = 0;


	void display();
};

