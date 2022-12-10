#ifndef __HUD_H__
#define __HUD_H__

#include "stdafx.h"
#include "MainGame.h"
#include "ImageManager.h"
class Hud {
public:
	Hud();
	GLvoid InitBuffer();
	GLvoid Draw(int hp, int coin_num);

	GLuint hp_bar_texture;
	GLuint coin_bar_texture;
	GLuint number_texture[10];
	GLuint VAO, VBO[2];
};



#endif // !__HUD_H__
