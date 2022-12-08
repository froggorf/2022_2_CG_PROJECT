#ifndef __MYSTERYBLOCK_H__
#define __MYSTERYBLOCK_H__
#include "cube.h"

class MysteryBlock : public Cube {
public:
	Cube boundingBox;

	GLuint VAO, VBO[3];

	GLuint coins;

	MysteryBlock();
	MysteryBlock(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate, GLuint coin);
	~MysteryBlock();

	GLvoid Init();
	virtual GLvoid InitBuffer();
	virtual GLvoid draw();
};

#endif

// 10�� Hp
// 12�� ���� 1��
// 14�� ���� 1��
// 37�� ���� 1��