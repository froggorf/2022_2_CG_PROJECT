#ifndef __WALL_H__
#define __WALL_H__
#include "cube.h"

class Wall : public Cube {
public:
	Cube boundingBox;

	GLuint VAO, VBO[3];
	Wall();
	Wall(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate);
	~Wall();

	GLvoid InitBuffer();
	GLvoid Init();
	GLvoid draw();
};

#endif