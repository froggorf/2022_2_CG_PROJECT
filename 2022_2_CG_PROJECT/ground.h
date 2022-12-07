#ifndef __GROUND_H__
#define __GROUND_H__
#include "stdafx.h"
#include "cube.h"

class Ground {
public:
	Cube boundingBox;

	GLuint VAO, VBO[3];

	GLvoid Init();
	GLvoid InitBuffer();
	GLvoid draw();
};



#endif // !__GROUND_H__
