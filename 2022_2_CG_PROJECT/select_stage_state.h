#ifndef __SELECT_STAGE_H__
#define __SELECT_STAGE_H__
#include "stdafx.h"
#include "ImageManager.h"
#include "game_framework.h"
#include "MainGame.h"

namespace SelectStage {
	GLvoid enter();
	GLvoid exit();
	GLvoid pause();
	GLvoid resume();
	GLvoid handle_events();
	GLvoid update();
	GLvoid draw();
	GLvoid key_down(unsigned char, int, int);
	GLvoid key_up(unsigned char, int, int);

	GLvoid InitValue();
	GLvoid InitBuffer();
	GLvoid DrawMainImage();
	GLvoid DrawStageImage();
	GLvoid DrawHand();

	GLint& GetSelectStageNum();
	GLint& GetPlayableStageNum();
	GLvoid ClearUpdate(GLboolean);
}

#endif // !__SELECT_STAGE_H__