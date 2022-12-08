#ifndef __CUBE_H__
#define __CUBE_H__
#include "stdafx.h"
#include "MainGame.h"
#include "camera.h"
#include "ImageManager.h"
enum VBOType { POS = 0, NORMAL = 1, TEXTURE };

class Cube {
public:
    glm::vec3 trans;
    glm::vec3 rot;
    glm::vec3 scale;

    glm::vec3 color;

    Cube();
    Cube(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate);
    GLvoid init();
    GLboolean CubeCollide(Cube);


};

glm::vec3* GetCubeVertices();
glm::vec3* GetCubeNormal();


#endif