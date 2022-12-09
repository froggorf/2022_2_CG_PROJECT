#ifndef __ITEM_H__
#define __ITEM_H__
#include "cube.h"
#include "check_collision.h"

class Item : public Cube {
public:
	Cube boundingBox;
	GLuint VAO, VBO[3];
	GLuint frame;

	GLboolean dead;
	GLuint dir;

	Item();
	Item(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate);
	~Item();

	GLvoid Init();
	virtual GLvoid update();
	virtual GLvoid InitBuffer();
	virtual GLvoid draw(GLuint cType);
};

#endif
