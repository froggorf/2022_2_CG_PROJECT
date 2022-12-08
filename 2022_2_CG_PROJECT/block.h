#ifndef __BLOCK_H__
#define __BLOCK_H__
#include "cube.h"

class Block : public Cube {
public:
	Cube boundingBox;
	GLuint VAO, VBO[3];

	Block();
	Block(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate);
	~Block();

	GLvoid Init();
	virtual GLvoid InitBuffer();
	virtual GLvoid draw();
};

#endif