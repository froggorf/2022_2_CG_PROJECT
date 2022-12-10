#ifndef __LOGO_STATE_H__
#define __LOGO_STATE_H__

#include "stdafx.h"
#include "ImageManager.h"
#include "game_framework.h"
#include "MainGame.h"


namespace Logo {
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

#endif