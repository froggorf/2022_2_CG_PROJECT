#ifndef __GAMEOVER_STAGE_H__
#define __GAMEOVER_STAGE_H__
#include "stdafx.h"
#include "ImageManager.h"
#include "game_framework.h"
#include "MainGame.h"

namespace GameOver {
	GLvoid enter();
	GLvoid exit();
	GLvoid pause();
	GLvoid resume();
	GLvoid handle_events();
	GLvoid update();
	GLvoid draw();
	GLvoid key_down(unsigned char, int, int);
	GLvoid key_up(unsigned char, int, int);
}

#endif // !__SELECT_STAGE_H__