#ifndef __MAINGAME_H__
#define __MAINGAME_H__
//헤더 파일 목록
#include "stdafx.h"
#include "game_framework.h"
#include "key_events.h"

//define 목록
#define WIDTH 1280
#define HEIGHT 1280

//glut 관련 함수
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char key, int x, int y);
GLvoid KeyBoardUp(unsigned char key, int x, int y);
GLvoid Mouse(int, int, int, int);
GLvoid MouseMove(int, int);
GLvoid SpecialKeyboard(int, int, int);
GLvoid SpecialKeyUp(int, int, int);

//셰이더 관련 함수 및 변수
char* filetobuf(const char* file);
void make_vertexShaders();
void make_fragmentShaders();
void checkCompileErrors(unsigned int shader, std::string type);
GLvoid InitShader();
GLuint Gets_program();
GLuint Gets_program_texture();
//메인 타이머 관련 변수 및 함수

GLvoid MainTimer(int value);




#endif