#ifndef __PARTICLE_H__
#define __PARTICLE_H__
#include "cube.h"

class Particle : public Cube {
public:
	Particle();
	Particle(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate);
	Particle(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate, GLboolean);
	~Particle();

	GLuint VAO, VBO[3];
	GLuint frame;
	GLfloat rotateDegree[3];

	GLvoid Init();
	virtual GLvoid update();
	virtual GLvoid InitBuffer();
	virtual GLvoid draw();
	virtual GLvoid collision_handling(Cube* other);

};

#endif