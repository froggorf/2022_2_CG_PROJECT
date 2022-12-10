#ifndef __MUSHROOM_H__
#define __MUSHROOM_H__
#include "item.h"
#include "ground.h"
#include "mario_character.h"
#include "check_collision.h"

class Mushroom : public Item {
public:
	Mushroom();
	Mushroom(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate);
	~Mushroom();

	GLuint frame;
	GLuint dir;
	GLfloat degree;
	GLboolean isAppear;
	GLfloat appearing;

	GLvoid Init();
	virtual GLvoid update();
	virtual GLvoid InitBuffer();
	virtual GLvoid draw(GLuint cType);
	virtual GLvoid collision_handling(Cube* other);
};

#endif#pragma once
