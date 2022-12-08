#ifndef __TITLE_STATE_H__
#define __TITLE_STATE_H__

#include "stdafx.h"


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

}

#endif