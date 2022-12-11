#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__
#include "stdafx.h"
#include <locale>
#include <codecvt>

GLvoid PlaySoundMP3(std::string str, GLboolean isLoop, MCI_OPEN_PARMS& openBgm);
GLvoid PlaySoundMP3(std::string str, GLboolean isLoop);
std::wstring s2ws(const std::string& s);

#endif // !__IMAGEMANAGER_H__