#ifndef __CHANGE_DIMENSION_STATE_H__
#define __CHANGE_DIMENSION_STATE_H__

#include "stdafx.h"
#include "play_state.h"
#include "camera.h"

namespace ChangeDimension {
	GLvoid enter();
	GLvoid exit();
	GLvoid pause();
	GLvoid resume();
	GLvoid handle_events();
	GLvoid update();
	GLvoid draw();
	GLvoid key_down(unsigned char, int, int);
	GLvoid key_up(unsigned char, int, int);

	GLvoid InitBuffer();
	GLvoid InitValue();
	GLvoid SetTransformationMatrix();

}

#endif#pragma once
