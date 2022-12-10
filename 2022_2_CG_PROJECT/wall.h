#ifndef __WALL_H__
#define __WALL_H__
#include "cube.h"

class Wall : public Cube {
public:
	Wall();
	Wall(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate);
	Wall(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate, GLboolean is2DCollide);
	~Wall();

	Cube boundingBox;
	GLuint VAO, VBO[3];
	GLboolean is2DCollide;
	GLboolean isLikeGround;

	GLvoid InitBuffer();
	GLvoid Init();
	GLvoid draw();
};

#endif