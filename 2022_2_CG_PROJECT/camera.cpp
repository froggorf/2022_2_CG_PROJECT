#include "camera.h"

GLvoid Camera::update(glm::vec3 marioPos) {
	switch (cType) {
	case D3_VIEW:
		cameraPos.x = marioPos.x-5.0f;
		cameraPos.y = marioPos.y+ 1.5f;
		cameraPos.z = marioPos.z;
		break;
	case D2_VIEW:
		break;
	}

}