#ifndef __GROUND_H__
#define __GROUND_H__
#include "stdafx.h"
#include "cube.h"

class Ground : public Cube {
public:
	Cube boundingBox;

	GLuint VAO, VBO[3];

	Ground();
	Ground(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate);
	~Ground();
	GLvoid Init();
	virtual GLvoid InitBuffer();
	virtual GLvoid draw();
};



#endif // !__GROUND_H__
