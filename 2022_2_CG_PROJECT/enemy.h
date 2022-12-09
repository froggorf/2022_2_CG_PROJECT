#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "cube.h"

class Enemy : public Cube {
public:
	Cube boundingBox;
	GLuint VAO, VBO[3];
	GLuint frame;

	Enemy();
	Enemy(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate);
	~Enemy();

	GLvoid Init();
	GLvoid update();
	virtual GLvoid InitBuffer();
	virtual GLvoid draw();
};

#endif
