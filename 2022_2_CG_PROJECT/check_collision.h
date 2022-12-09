#ifndef __CHECK_COLLISION_H__
#define __CHECK_COLLISION_H__



#include "stdafx.h"
#include "cube.h"

GLboolean CheckAABB(Cube cube1, Cube cube2);
GLboolean CheckAABB_2D(Cube cube1, Cube cube2);

#endif // !__CHECK_COLLISION_H__