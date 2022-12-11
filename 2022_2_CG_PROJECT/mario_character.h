#ifndef __MARIO_H__
#define __MARIO_H__

#include "stdafx.h"
#include "cube.h"
#include "key_events.h"
#include "check_collision.h"
#include "play_state.h"
#include "ImageManager.h"
#include "camera.h"
#include "wall.h"
#include "door.h"
#include "enemy.h"
#include "brick.h"
#include "mysteryBlock.h"
#include "item.h"
#include "mushroom.h"
#include "coin.h"

#define GravityAcceleration 0.0098
#define MarioSpeed 0.1
#define MARIO_MAX_FRAME 7
#define RIGHT 0
#define LEFT 1
#define FLOAT_ERROR_FIGURE 0.0001
#define HURT_TIME 500
#define JumpPower 30
#define MarioMaxHp 10

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



class Mario: public Cube{
public:
	//Cube boundingBox;
	GLfloat speed;
	GLfloat gravity;
	GLboolean flag_jump;
	GLboolean can_jump;
	GLint cur_state;
	GLboolean face;
	GLint dir[3];
	GLint hurt_time;
	GLint coin_num;
	GLint hp;

	GLvoid InitBuffer();
	GLvoid Init();
	GLvoid draw(GLuint);
	GLvoid update();
	GLvoid handle_events(int, unsigned char);

	GLvoid falling_gravity();
	GLvoid CheckKillingEnemy();
	GLvoid CheckFallingCliff();

	GLvoid move(int);
	GLvoid DoJump();

	GLvoid SendMessageToDoor();
	
	GLvoid handle_collision(int, std::vector<Cube*>);
	GLvoid CheckHittingByEnemy();
	GLvoid CheckGetItem();
	glm::vec3 GetPos();
	GLint GetCoinNum();
	GLvoid GetCoin(int);
	GLint GetHp();

	GLfloat frame;
	GLuint VAO, VBO[3];

	GLuint texture[MARIOSTATEEND][MARIO_MAX_FRAME];
	
	GLvoid CheckNextState_3D(int type, unsigned char key);
	GLvoid MarioChangeState(int);
	GLvoid StateEnter_3D(int type = -1, unsigned char key = -1);
	GLvoid StateExit_3D(int type=-1,unsigned char key = -1);
	GLvoid StateDo_3D();

	GLvoid CheckNextState_2D(int type, unsigned char key);
	GLvoid StateEnter_2D(int type = -1, unsigned char key = -1);
	GLvoid StateExit_2D(int type = -1, unsigned char key = -1);
	GLvoid StateDo_2D();
};

GLvoid DrawPressFHud();

#endif