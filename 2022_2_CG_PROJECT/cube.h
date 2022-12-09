#ifndef __CUBE_H__
#define __CUBE_H__
#include "stdafx.h"
#include "MainGame.h"
#include "camera.h"
#include "ImageManager.h"
enum VBOType { POS = 0, NORMAL = 1, TEXTURE };

class Cube {
public:
    Cube();
    Cube(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate);
    //GLvoid Init();
    GLboolean CubeCollide(Cube);

    glm::vec3 trans;
    glm::vec3 rot;
    glm::vec3 scale;
    GLboolean isCanDelete;

    glm::vec3 color;

    virtual GLvoid Init();
    virtual GLvoid InitBuffer() {}
    virtual GLvoid draw() {}
    virtual GLvoid collision_handling(Cube* other) {}
};

glm::vec3* GetCubeVertices();
glm::vec3* GetCubeNormal();


#endif