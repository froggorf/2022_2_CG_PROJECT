#ifndef __COIN_H__
#define __COIN_H__
#include "item.h"
#include "mario_character.h"
#include "check_collision.h"

#define GETCOINSOUND "resource/Sound/getCoin.mp3"

class Coin : public Item {
public:
	Coin();
	Coin(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate);
	Coin(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate, GLboolean);
	~Coin();

	GLuint frame;
	GLfloat appearMoveFigure;
	GLboolean isOnGround;
	GLboolean isMovingUp;
	MCI_OPEN_PARMS coinSound;

	GLvoid Init();
	virtual GLvoid update();
	virtual GLvoid InitBuffer();
	virtual GLvoid draw(GLuint cType);
	GLvoid collision_handling(Cube* other);

};

#endif