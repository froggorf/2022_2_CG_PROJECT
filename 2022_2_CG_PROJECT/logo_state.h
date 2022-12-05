#ifndef __LOGO_STATE_H__
#define __LOGO_STATE_H__

#include "stdafx.h"




namespace Logo {
	GLvoid enter();
	GLvoid exit();
	GLvoid pause();
	GLvoid resume();
	GLvoid handle_events();
	GLvoid update();
	GLvoid draw();

}

#endif