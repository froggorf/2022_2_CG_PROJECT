#ifndef __CAMERA_H__
#define __CAMERA_H__
#include "stdafx.h"

#define CameraViewSize 300.0f

enum CameraType { D3_VIEW = 0, D2_VIEW = 1 };
class Camera {
public:
    glm::vec3 cameraPos;
    glm::vec3 cameraDirection;
    glm::vec3 cameraUp;

    GLvoid update(glm::vec3, GLuint cType);
};
#endif 
