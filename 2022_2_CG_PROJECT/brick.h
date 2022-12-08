#ifndef __BRICK_H__
#define __BRICK_H__
#include "cube.h"

class Brick : public Cube{
public:
	Cube boundingBox;

	GLuint VAO, VBO[3];
	Brick();
	Brick(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate);
	~Brick();

	GLvoid InitBuffer();
	GLvoid Init();
	GLvoid draw();
};

#endif