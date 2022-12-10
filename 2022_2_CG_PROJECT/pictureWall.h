#ifndef __PICTUREWALL_H__
#define __PICTUREWALL_H__
#include "wall.h"

class PictureWall : public Wall {
public:
	PictureWall();
	PictureWall(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate);
	PictureWall(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate, GLuint );
	~PictureWall();

	GLuint picSel;

	GLvoid InitBuffer();
	GLvoid Init();
	GLvoid draw();
};

#endif