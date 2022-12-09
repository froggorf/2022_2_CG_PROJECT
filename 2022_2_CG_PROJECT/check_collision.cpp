#include "check_collision.h"

GLboolean CheckAABB(Cube cube1, Cube cube2) {
	//x축 충돌 체크

	if (!(cube1.trans.x - 0.5 * cube1.scale.x < cube2.trans.x + 0.5 * cube2.scale.x
		&& cube1.trans.x + 0.5 * cube1.scale.x>cube2.trans.x - 0.5 * cube2.scale.x)) {
		return false;
	}

	if (!(cube1.trans.y - 0.5 * cube1.scale.y < cube2.trans.y + 0.5 * cube2.scale.y
		&& cube1.trans.y + 0.5 * cube1.scale.y>cube2.trans.y - 0.5 * cube2.scale.y)) {
		return false;
	}

	if (!(cube1.trans.z - 0.5 * cube1.scale.z < cube2.trans.z + 0.5 * cube2.scale.z
		&& cube1.trans.z + 0.5 * cube1.scale.z>cube2.trans.z - 0.5 * cube2.scale.z)) {
		return false;
	}

	return true;

}

GLboolean CheckAABB_2D(Cube cube1, Cube cube2) {
	//x축 충돌 체크
	if (!(cube1.trans.x - 0.5 * cube1.scale.x < cube2.trans.x + 0.5 * cube2.scale.x
		&& cube1.trans.x + 0.5 * cube1.scale.x>cube2.trans.x - 0.5 * cube2.scale.x)) {
		return false;
	}

	if (!(cube1.trans.y - 0.5 * cube1.scale.y < cube2.trans.y + 0.5 * cube2.scale.y
		&& cube1.trans.y + 0.5 * cube1.scale.y>cube2.trans.y - 0.5 * cube2.scale.y)) {
		return false;
	}

	return true;

}