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
	WALKING_RIGHT_UP,WALKING_LEFT_UP,
	JUMP_RIGHT,JUMP_LEFT,
	JUMP_RIGHT_UP,JUMP_LEFT_UP,
	HURT_RIGHT,HURT_LEFT,
	MARIOSTATEEND
};



class Mario{
public:
	Cube boundingBox;
	GLfloat speed;
	GLfloat gravity;
	GLboolean flag_jump;
	GLint cur_state;

	GLvoid InitBuffer();
	GLvoid init();
	GLvoid draw();
	GLvoid update();
	GLvoid handle_events(int);
	GLvoid falling_gravity();
	GLvoid move(int);
	GLvoid handle_collision(int, std::vector<Cube>&);
	glm::vec3 GetPos();

	GLfloat frame;
	GLuint VAO, VBO[3];

	GLuint texture[MARIOSTATEEND][MARIO_MAX_FRAME];
};

#endif