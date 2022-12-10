#ifndef __SQUIGLET_H__
#define __SQUIGLET_H__
#include "mario_character.h"
#include "enemy.h"
#include <string>

class Squiglet : public Enemy {
public:
	Squiglet();
	Squiglet(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate);
	~Squiglet();

	GLboolean back;
	GLboolean isStepOn;
	GLfloat timer;

	GLvoid Init();
	GLvoid update();
	virtual GLvoid InitBuffer();
	virtual GLvoid draw();
	virtual GLvoid collision_handling(Cube* other);
};

#endif