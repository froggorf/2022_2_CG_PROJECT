#ifndef __DOOR_H__
#define __DOOR_H__
#include "cube.h"

class Door : public Cube {
public:
	Cube boundingBox;
	GLuint VAO, VBO[3];

	Door();
	Door(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate);
	~Door();

	GLvoid Init();
	virtual GLvoid InitBuffer();
	virtual GLvoid draw();
};

#endif