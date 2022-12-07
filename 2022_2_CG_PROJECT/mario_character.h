#ifndef __MARIO_H__
#define __MARIO_H__

#include "stdafx.h"
#include "cube.h"
#include "key_events.h"
#include "check_collision.h"
#include "play_state.h"
#include "ImageManager.h"
#include "ground.h"
#define GravityAcceleration 0.0098
#define MarioSpeed 0.3
#define MARIO_MAX_FRAME 7

enum MarioState {
	IDLE_RIGHT=0,IDLE_LEFT,
	WALKING_RIGHT,WALKING_LEFT,
	WALKING_UP_RIGHT,WARKING_UP_LEFT,
	JUMP_RIGHT,JUMP_LEFT,
	JUMP_UP_RIGHT,JUMP_UP_LEFT,
	MARIOSTATEEND
};

class Mario{
public:
	Cube boundingBox;
	GLfloat speed;
	GLfloat gravity;
	GLboolean flag_jump;
	GLvoid InitBuffer();
	GLvoid init();
	GLvoid draw();
	GLvoid update();
	GLvoid handle_events(int);
	GLvoid falling_gravity();
	GLvoid move(int);
	GLvoid handle_collision(int, std::vector<Ground>&);
	glm::vec3 GetPos();

	GLfloat frame;
	GLuint VAO, VBO[3];

	GLuint texture[MARIOSTATEEND][MARIO_MAX_FRAME];
};

#endif