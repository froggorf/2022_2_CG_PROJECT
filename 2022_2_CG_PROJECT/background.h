#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "stdafx.h"
#include "ImageManager.h"
#include "MainGame.h"
class BackGround {
public:
	GLuint VAO, VBO[2];
	GLuint texture;

	GLvoid InitBuffer();
	GLvoid Draw();
};


#endif // !__BACKGROUND_H__
