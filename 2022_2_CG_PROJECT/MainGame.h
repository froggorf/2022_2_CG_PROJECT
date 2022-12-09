#ifndef __MAINGAME_H__
#define __MAINGAME_H__
//��� ���� ���
#include "stdafx.h"
#include "game_framework.h"
#include "key_events.h"

//define ���
#define WIDTH 1280
#define HEIGHT 1280

//glut ���� �Լ�
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid KeyBoard(unsigned char key, int x, int y);
GLvoid KeyBoardUp(unsigned char key, int x, int y);
GLvoid Mouse(int, int, int, int);
GLvoid MouseMove(int, int);
GLvoid SpecialKeyboard(int, int, int);
GLvoid SpecialKeyUp(int, int, int);

//���̴� ���� �Լ� �� ����
char* filetobuf(const char* file);
void make_vertexShaders();
void make_fragmentShaders();
void checkCompileErrors(unsigned int shader, std::string type);
GLvoid InitShader();
GLuint Gets_program();
GLuint Gets_program_texture();
//���� Ÿ�̸� ���� ���� �� �Լ�

GLvoid MainTimer(int value);




#endif