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
#define MarioSpeed 0.1
#define MARIO_MAX_FRAME 7
#define RIGHT 0
#define LEFT 1

enum MarioState {
	IDLE_RIGHT=0,IDLE_LEFT,
	IDLE_RIGHT_UP,IDLE_LEFT_UP,
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
	GLboolean face;
	GLint dir[3];

	GLvoid InitBuffer();
	GLvoid init();
	GLvoid draw(GLuint);
	GLvoid update();
	GLvoid handle_events(int, unsigned char);
	GLvoid falling_gravity();
	GLvoid move(int);
	GLvoid DoJump();
	GLvoid handle_collision(int, std::vector<Cube*>);
	glm::vec3 GetPos();

	GLfloat frame;
	GLuint VAO, VBO[3];

	GLuint texture[MARIOSTATEEND][MARIO_MAX_FRAME];
	
	GLvoid CheckNextState(int type, unsigned char key);
	GLvoid Mario_Change_State(int);
	GLvoid StateEnter(int type = -1, unsigned char key = -1);
	GLvoid StateExit(int type=-1,unsigned char key = -1);
	

	//TODO: Áö¿ï°Å
	GLvoid PLEASEDELETELATER_PRINTCURSTATEFUNCTION();
};

#endif