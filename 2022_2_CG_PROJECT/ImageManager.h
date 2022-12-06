#ifndef __IMAGEMANAGER_H__
#define __IMAGEMANAGER_H__
#include "stdafx.h"

void LoadTexture(GLuint& texture, const char* img_name);
//
//void InitTexture()
//{
//	//stbi_set_flip_vertically_on_load(true); //이미지 뒤집히면 넣기
//	LoadTexture(box_texture, "aaaa.png");
//	//stbi_set_flip_vertically_on_load(true); //이미지 뒤집히면 넣기
//	LoadTexture(sky_texture[0], "skymap_0.png");
//	LoadTexture(sky_texture[1], "skymap_1.png");
//	LoadTexture(sky_texture[2], "skymap_2.png");
//	LoadTexture(sky_texture[3], "skymap_3.png");
//}

#endif // !__IMAGEMANAGER_H__