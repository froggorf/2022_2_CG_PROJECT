#ifndef __DOOR_H__
#define __DOOR_H__
#include "cube.h"
#include <string>

class Door : public Cube {
public:
	Cube boundingBox;
	GLuint VAO, VBO[3];
	GLuint frame;
	GLboolean isOpen;

	Door();
	Door(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate);
	~Door();

	GLvoid Init();
	GLvoid update();
	virtual GLvoid InitBuffer();
	virtual GLvoid draw();
};

#endif