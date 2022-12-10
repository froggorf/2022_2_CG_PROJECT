#ifndef __BRICKPARTICLE_H__
#define __BRICKPARTICLE_H__
#include "particle.h"
#include "play_state.h"

class BrickParticle : public Particle {
public:
	BrickParticle();
	BrickParticle(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate);
	BrickParticle(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate, int i);
	~BrickParticle();

	GLfloat gravity;
	GLfloat speed;
	GLuint particleNum;
	glm::vec3 rotateAxis;

	GLvoid Init();
	virtual GLvoid update();
	virtual GLvoid InitBuffer();
	virtual GLvoid draw();
	virtual GLvoid collision_handling(Cube* other);

};

GLvoid spawnBrickParticle(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate);

#endif