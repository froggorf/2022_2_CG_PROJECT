#include "stdafx.h"

#include "cube.h"

#include "ground.h"
#include "brick.h"
#include "mysteryBlock.h"
#include "pipe.h"
#include "block.h"
#include "door.h"
#include "wall.h"

#include "item.h"
#include "coin.h"

enum BLOCKKIND {
	BLOCK, BRICK, DOOR, GROUND, MYSTERYBLOCK, PIPE, WALL, PICTUREWALL
};
void loadStage1(std::vector<Cube*> &vec);
void loadStage2(std::vector<Cube*> &vec);