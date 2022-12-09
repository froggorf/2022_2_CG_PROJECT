#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "cube.h"
#include "check_collision.h"

class Enemy : public Cube {
public:
	Cube boundingBox;
	GLuint VAO, VBO[3];
	GLuint frame;

	GLboolean dead;
	GLuint dir;

	Enemy();
	Enemy(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate);
	~Enemy();

	GLvoid Init();
	virtual GLvoid update();
	virtual GLvoid InitBuffer();
	virtual GLvoid draw();
};

#endif
