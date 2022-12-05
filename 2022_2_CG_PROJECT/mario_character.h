#ifndef __MARIO_H__
#define __MARIO_H__

#include "stdafx.h"
#include "cube.h"
#include "key_events.h"
#include "check_collision.h"
#include "play_state.h"
#define GravityAcceleration 0.0098
#define MarioSpeed 0.1
class Mario {
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
	GLvoid handle_collision(int, std::vector<Cube*>&);
};

#endif