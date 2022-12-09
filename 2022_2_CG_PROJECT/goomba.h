#ifndef __GOOMBA_H__
#define __GOOMBA_H__
#include "enemy.h"
#include <string>

class Goomba: public Enemy {
public:
	Goomba();
	Goomba(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate);
	~Goomba();

	GLboolean back;

	GLvoid Init();
	GLvoid update();
	virtual GLvoid InitBuffer();
	virtual GLvoid draw();
};

#endif