#ifndef __TITLE_STATE_H__
#define __TITLE_STATE_H__

#include "stdafx.h"
#include "MainGame.h"
#include "ImageManager.h"
#include "soundManager.h"

namespace Title {
	GLvoid enter();
	GLvoid exit();
	GLvoid pause();
	GLvoid resume();
	GLvoid handle_events();
	GLvoid update();
	GLvoid draw();
	GLvoid key_down(unsigned char, int, int);
	GLvoid key_up(unsigned char, int, int);

	GLvoid EarlyInitValue();
	GLvoid DrawMainImage();

	GLvoid DrawMountainImage();
	GLvoid UpdateMountainImage();

	GLvoid DrawGameNameImage();
	GLvoid UpdateGameNameImage();

	GLvoid DrawMarioImage();
	GLvoid UpdateMarioImage();

	GLvoid DrawSelect();
}

#endif