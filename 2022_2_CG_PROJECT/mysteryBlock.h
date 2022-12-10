#ifndef __MYSTERYBLOCK_H__
#define __MYSTERYBLOCK_H__
#include "cube.h"
#include "mario_character.h"
#include "play_state.h"

#include "item.h"
#include "coin.h"
#include "mushroom.h"

class MysteryBlock : public Cube {
public:
	Cube boundingBox;

	GLuint VAO, VBO[3];

	GLuint coins;
	GLboolean moving;
	GLboolean isMoveUp;
	GLfloat movingTransFigure;

	MysteryBlock();
	MysteryBlock(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate, GLuint coin);
	~MysteryBlock();

	GLvoid Init();
	virtual GLvoid InitBuffer();
	virtual GLvoid draw();
	GLvoid collision_handling(Cube* other);
	GLvoid update();
};

#endif

// 10번 Hp
// 12번 코인 1개
// 14번 코인 1개
// 37번 코인 1개