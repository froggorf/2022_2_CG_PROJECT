#ifndef __GAME_FRAMEWORK_H__
#define __GAME_FRAMEWORK_H__

#include "stdafx.h"

enum GameStateType {
	LOGO = 0,
	TITLE,
	PLAY,
	//TODO: ITEM,
};

class GameState {
public:
	int state_type;
	void(*enter)();
	void(*exit)();
	void(*pause)();
	void(*resume)();
	void(*handle_events)();
	void(*update)();
	void(*draw)();

	void init();
	void setting(int);
};

void change_state(int);
void push_state(int);
void pop_state();
void quit();
void game_framework_running(int);
GameState* GetGameState();
GLboolean GetRunning();
GLint GetNow();



#endif