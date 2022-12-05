#ifndef __CUBE_H__
#define __CUBE_H__
#include "stdafx.h"
#include "MainGame.h"
#include "camera.h"
enum VBOType { POS = 0, NORMAL = 1 };

class Cube {
public:
    glm::vec3 trans;
    glm::vec3 rot;
    glm::vec3 scale;

    glm::vec3 color;

    GLuint VAO, VBO[2];
    
    GLvoid InitBuffer();
    GLvoid init();
    GLvoid DelBuffer();
    GLvoid draw();
    GLboolean CubeCollide(Cube);
};



#endif