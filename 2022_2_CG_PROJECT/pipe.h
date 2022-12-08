#ifndef __PIPE_H__
#define __PIPE_H__
#include "cube.h"

class Pipe : public Cube {
public:
	Cube boundingBox;
	GLuint VAO, VBO[3];

	Pipe();
	Pipe(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate);
	~Pipe();

	GLvoid Init();
	virtual GLvoid InitBuffer();
	virtual GLvoid draw();
};

#endif