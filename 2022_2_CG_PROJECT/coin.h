#ifndef __COIN_H__
#define __COIN_H__
#include "item.h"
#include "check_collision.h"

class Coin : public Item {
public:
	Coin();
	Coin(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate);
	~Coin();

	GLvoid Init();
	virtual GLvoid update();
	virtual GLvoid InitBuffer();
	virtual GLvoid draw();
};

#endif